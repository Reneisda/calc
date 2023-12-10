#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>


#ifndef CALC_CALCULATIONS_H
#define CALC_CALCULATIONS_H
#endif //CALC_CALCULATIONS_H
void bin_pdf(mpf_t x, long n, mpf_t p, long k);
void pq(double* answer, double p, double q);
void fac(mpz_t x);
void ncr(mpz_t x, long n, long k);
void bin_pdf(mpf_t x, long n, mpf_t p, long k);
void bin_cdf(mpf_t x, long n, mpf_t p, long k);
