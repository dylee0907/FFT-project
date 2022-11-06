// DATE : 2022-07-06               
// DESCRIPTION : Radix2 DIT FFT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define input_point 8
int main(void)
{
    // you should input the Real number and Imaginary number
    double x[input_point] = {1,-1,-1,-1,1,1,1,-1};
    double y[input_point] = {0,0,0,0,0,0,0,0};
    // x : real number, y : imaginary number
    double pi = 3.14159265358979;
    int num;
    int N;
    int check_N;
    int num_stage;
    int pre_stage;
    int stride;
    int iteration;
Re:
    num_stage = 0;
    printf("Input the number of point(num=2^n): ");
    scanf_s("%d",&num);
    N = num;
    while(1)
    {
    check_N = N%2;
    if(check_N == 1)
    {
        printf("Error: Re-input number(num=2^n)\n");
        goto Re;
    }
    else {
        if (N != 2) N = N / 2;
        else N = N - 2;
    num_stage += 1;
    if(N==0) break;
    }
    }
    pre_stage = num_stage - 1;
    printf("***********************************************\n");
    printf("number of total stage:\t%d\n", num_stage);
    printf("number of pre stage:\t%d\n", pre_stage);
    printf("***********************************************\n");
    printf("Re(Inputs): ");
    for (int i = 0; i < input_point; i++)
    {
            printf("%lf ", x[i]);
    }
    printf("\n");
    printf("Im(Inputs): ");
    for (int i = 0; i < input_point; i++)
    {
            printf("%lf ", y[i]);
    }
    printf("\n");

    // zero padding
    double* rx = (double*)malloc(sizeof(double) * num);
    double* ry = (double*)malloc(sizeof(double) * num);
    double* tx = (double*)malloc(sizeof(double) * num);
    double* ty = (double*)malloc(sizeof(double) * num);
    for (int i = 0; i < num; i++)
    {
        if (i < input_point) {
            rx[i] = x[i];
            ry[i] = y[i];
            tx[i] = x[i];
            ty[i] = y[i];
        }
        else {
            rx[i] = 0;
            ry[i] = 0;
            tx[i] = 0;
            ty[i] = 0;
        }
    }

    // bit reverse
    for(int i=0;i<num;i++)
    {
        int j=i;
        int res = 0;
        int it_cnt = 0;
        while(1)
        {
            if(j%2==1) res = 2*res+1;
            else res = 2*res;
            it_cnt+=1;
            if(it_cnt==num_stage)
            {
                rx[i] = tx[res];
                ry[i] = ty[res];
                break;
            }
            j=j/2;
        }
    }
    printf("***********************************************\n");
    printf("Re(reverse): ");
    for (int i = 0; i < num; i++)
    {
            printf("%lf", rx[i]);
    }
    printf("\n");
    printf("Im(reverse): ");
    for (int i = 0; i < num; i++)
    {
            printf("%lf", ry[i]);
    }
    printf("\n");
    printf("***********************************************\n");

    // fft before last stage
    double* c = (double*)malloc(sizeof(double) * (num/2));
    double* s = (double*)malloc(sizeof(double) * (num/2));
    double* twiddle_c = (double*)malloc(sizeof(double) * (num / 4));
    double* twiddle_s = (double*)malloc(sizeof(double) * (num / 4));
    int coef_twiddle = num / 2;
    for (int i = 0; i < num/2; i++)
    {
        c[i] = cos(2 * pi / num * i);
        s[i] = sin(2 * pi / num * i);
    }
    for (int i = 0; i < pre_stage; i++)
    {
        stride = (int)pow(2, (i + 1));
        for (int k = 0; k < 1+num-stride; k += stride)
        {
            iteration = stride / 2;
            for (int j = 0; j < iteration; j++)
            {
                twiddle_c[j] = c[j * coef_twiddle];
                twiddle_s[j] = s[j * coef_twiddle];
                tx[k+j] = rx[k+j]+rx[k+j+iteration]*twiddle_c[j]+ry[k+j+iteration]*twiddle_s[j];
                ty[k+j] = ry[k+j]+ry[k+j+iteration]*twiddle_c[j]-rx[k+j+iteration]*twiddle_s[j];
                tx[k+j+iteration] = rx[k+j]-rx[k+j+iteration]*twiddle_c[j]-ry[k+j+iteration]*twiddle_s[j];
                ty[k+j+iteration] = ry[k+j]-ry[k+j+iteration]*twiddle_c[j]+rx[k+j+iteration]*twiddle_s[j];
            }
        }
        for (int m = 0; m < num; m++)
        {
            rx[m] = tx[m];
            ry[m] = ty[m];
        }
        coef_twiddle /= 2;
    }
    free(twiddle_c);
    free(twiddle_s);
    // fft for last one stage
    for (int i = 0; i < num / 2; i++)
    {
        tx[i] = rx[i]+rx[i+num/2]*c[i]+ry[i+num/2]*s[i];
        ty[i] = ry[i]+ry[i+num/2]*c[i]-rx[i+num/2]*s[i];
        tx[i+num/2] = rx[i]-rx[i+num/2]*c[i]-ry[i+num/2]*s[i];
        ty[i+num/2] = ry[i]-ry[i+num/2]*c[i]+rx[i+num/2]*s[i];
    }
    free(c);
    free(s);
    for (int m = 0; m < num; m++)
    {
        rx[m] = tx[m];
        ry[m] = ty[m];
    }
    free(tx);
    free(ty);
    printf("Re(output): ");
    for (int i = 0; i < num; i++)
    {
            printf("%lf ", rx[i]);   
    }
    printf("\n");
    printf("Im(output): ");
    for (int i = 0; i < num; i++)
    {
            printf("%lf ", ry[i]);
    }
    free(rx);
    free(ry);
    printf("\n");
    return 0;
}
