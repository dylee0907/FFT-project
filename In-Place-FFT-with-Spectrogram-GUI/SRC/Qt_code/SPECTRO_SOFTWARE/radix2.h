#include <cmath>
typedef struct {
    double r, i;
} t_complex;

void complex_add(t_complex *dst, t_complex src0, t_complex src1);
void complex_sub(t_complex *dst, t_complex src0, t_complex src1);
void complex_mul(t_complex *dst, t_complex src0, t_complex src1);
void complex_mag(t_complex *dst, double *xmag, int N);
void twiddle_mul(t_complex *dst, int k, int N);
void radix2(double *in, t_complex *out, int N);
void bit_reverse(t_complex *in, int N);
double min2(double **X, int N, int M);
double max2(double **X, int N, int M);
void STFT(double **X, double *IN, int N, int H, int M);
void STFT_dB(double **X, int M, int N);
void Power_sort(double **X, int M, int N);
void mean(double **X, double* mu, int M, int N);
void sigma(double **X, double* sig, int M, int N);
void Power_dist(double **X, int M, int N);
