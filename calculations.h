#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "func.h"


#ifdef __linux__
    #include <gmp.h>

#elif _WIN32
    #include "ggmp/include/gmp.h"
    #define u_long unsigned long

#endif


#define bool uint8_t

void    pq(double* answer, double p, double q);
void    fac(mpz_t x);
void    ncr(mpz_t x, u_long n, u_long k);
void    npr(mpz_t x, u_long n, u_long k);
void    bin_pdf(mpf_t x, u_long n, mpf_t p, u_long k);
void    bin_cdf(mpf_t x, u_long n, mpf_t p, u_long k);
double  bisection(func* f, double a, double b);
double  newton_zero(func* f, double a);
