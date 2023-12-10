#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>


#ifndef CALC_CALCULATIONS_H
#define CALC_CALCULATIONS_H
#endif //CALC_CALCULATIONS_H
void pq(double* answer, double p, double q);
void fac(mpz_t x);
void ncr(mpz_t x, u_long n, u_long k);
void bin_pdf(mpf_t x, u_long n, mpf_t p, u_long k);
void bin_cdf(mpf_t x, u_long n, mpf_t p, u_long k);
