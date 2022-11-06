#include "radix2.h"

void complex_add(t_complex *dst, t_complex src0, t_complex src1)
{
    dst->r = src0.r+src1.r;
    dst->i = src0.i+src1.i;
}

void complex_sub(t_complex *dst, t_complex src0, t_complex src1)
{
    dst->r = src0.r-src1.r;
    dst->i = src0.i-src1.i;
}

void complex_mul(t_complex *dst, t_complex src0, t_complex src1)
{
    dst->r = src0.r*src1.r-src0.i*src1.i;
    dst->i = src0.r*src1.i+src0.i*src1.r;
}

void complex_mag(t_complex *dst, double *xmag, int N)
{
    for(int i=0;i<=N/2;i++)
    {
        xmag[i] = dst[i].r * dst[i].r + dst[i].i * dst[i].i;
        xmag[i] = sqrt(xmag[i]);
    }
}

void twiddle_mul(t_complex *dst, int k, int N)
{
    t_complex twiddle_factor;
    const double pi = acos(-1.0);
    twiddle_factor.r = cos(-2*pi*k/N);
    twiddle_factor.i = sin(-2*pi*k/N);
    complex_mul(dst, *dst, twiddle_factor);
}

// Radix2 DIF and return Magnitude Real Values
void radix2(double *in, t_complex *out, int N)
{
    int p;
    p = N;
    for(int i=0;i<N;i++)
    {
        out[i].r = in[i];
        out[i].i = 0;
    }
    for(int i=0;i<log2((double)N);i++, p/=2)
    {
       for(int j=0; j<N/p;j++)
       {
           for(int k=0; k<p/2;k++)
           {
               t_complex bf0, bf1;
               complex_add(&bf0, out[j*p+k], out[j*p+k+p/2]);
               complex_sub(&bf1, out[j*p+k], out[j*p+k+p/2]);
               twiddle_mul(&bf1,k,p);
               out[j*p+k] = bf0;
               out[j*p+k+p/2] = bf1;
           }
       }
    }
    bit_reverse(out,N);
}

void bit_reverse(t_complex *in, int N)
{
    t_complex *bf = new t_complex[N];
    for(int i=0; i<N; i++)
    {
        bf[i].r = in[i].r;
        bf[i].i = in[i].i;
    }
    for(int i=0;i<N;i++)
    {
        int j=i;
        int res = 0;
        int it_cnt = 0;
        while(1)
        {
            if(j%2==1) res = 2*res+1;
            else res *= 2;
            it_cnt++;
            if(it_cnt == log2(double(N)))
            {
                in[i].r = bf[res].r;
                in[i].i = bf[res].i;
                break;
            }
            j/=2;
        }
    }
    delete [] bf;
}

void STFT(double **X, double *IN, int N, int H, int M)
{
    t_complex* bf = new t_complex[N];
    double *temp = new double[N];
    double *xmag = new double[N/2+1];

    for(int m=0;m<=M;m++)
    {
        for(int j=0;j<N;j++)
            temp[j] = IN[m*H+j];

        radix2(temp,bf,N);
        complex_mag(bf,xmag,N);

        for(int i=0;i<=N/2;i++)
            X[m][i] = xmag[i];
    }
    delete []bf;
    delete []temp;
    delete []xmag;
}

void STFT_dB(double **X, int M, int N)
{
    for(int m=0;m<=M;m++)
        for(int j=0;j<=N/2;j++)
            X[m][j] = (double)20*log10(X[m][j]);
}

double min2(double **X, int N, int M)
{
    double bf = X[0][0];
    for(int m=0;m<=M;m++)
        for(int t=0;t<=N/2;t++)
        {
            if(bf > X[m][t])
                bf = X[m][t];
        }
    return bf;
}

double max2(double **X, int N, int M)
{
    double bf = X[0][0];
    for(int m=0;m<=M;m++)
        for(int t=0;t<=N/2;t++)
        {
            if(bf < X[m][t])
                bf = X[m][t];
        }
    return bf;
}

void Power_sort(double **X, int M, int N)
{
    double min;
    for(int m=0;m<=M;m++)
        for(int t=0;t<=N/2;t++)
        {
            min = X[m][t];
            for(int k=t;k<=N/2;k++)
            {
                if(min > X[m][k])
                {
                    min = X[m][k];
                    X[m][k] = X[m][t];
                    X[m][t] = min;
                }
            }
        }
}

void mean(double **X, double *mu, int M, int N)
{
    double sum;
    for(int m=0;m<=M;m++)
    {
        sum = 0.0;
        for(int t=0;t<=N/2;t++)
        {
            sum += X[m][t];
        }
        mu[m] = sum/((double)N/2+1);
    }
}

void sigma(double **X, double *sig, int M, int N)
{
    double *mu = new double[M+1];
    double *mu2 = new double[M+1];
    double **temp = new double*[M+1];
    for(int m=0;m<=M;m++)
        temp[m] = new double[N/2+1];

    // square of mean
    mean(X,mu,M,N);
    for(int m=0;m<=M;m++)
        mu[m] = pow(mu[m],2);

    // mean of square
    for(int m=0;m<=M;m++)
        for(int t=0;t<=N/2;t++)
            temp[m][t] = pow(X[m][t],2);
    mean(temp,mu2,M,N);

    for(int m=0;m<=M;m++)
        delete []temp[m];
    delete []temp;

    // standard deviation
    for(int m=0;m<=M;m++)
    {
        sig[m] = mu2[m] - mu[m];
        sig[m] = sqrt(sig[m]);
    }

    delete []mu;
    delete []mu2;
}

void Power_dist(double **X, int M, int N)
{
    double *mu = new double[M+1];
    double *sig = new double[M+1];
    Power_sort(X,M,N);
    mean(X,mu,M,N);
    sigma(X,sig,M,N);
    for(int m=0;m<=M;m++)
        for(int t=0;t<=N/2;t++)
        {
            X[m][t] = exp(-1*(pow(X[m][t]-mu[m],2))/(2*pow(sig[m],2))) / (sig[m]*sqrt(2*acos(-1.0)));
            X[m][t] = (double)100*X[m][t];
        }
    delete[]mu;
    delete[]sig;
}