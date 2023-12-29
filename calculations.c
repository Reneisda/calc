#include <math.h>
#include <gmp.h>
#include "calculations.h"


void
pq(double* answer, double p, double q) {
    double pHalf = p / 2;
    double a = (pHalf) * (-1);
    double inSqr = (pHalf * pHalf) - q;
    if (inSqr < 0) {
        answer =  NULL;
        return;
    }
    double b = sqrt(inSqr);
    answer[0] = a + b;
    answer[1] = a - b;
}

void                        //TODO threaded version of func
fac(mpz_t x) {
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set_ui(tmp, 1);
    u_long fak = mpz_get_ui(x);
    mpz_set_ui(x, 1);
    for (; fak > 0; fak--) {
        mpz_mul_ui(x, tmp, fak);
        mpz_set(tmp, x);
    }
}

void
ncr(mpz_t x, u_long n, u_long k) {
    mpz_t n_, k_, c, ans;
    mpz_init(n_); mpz_init(k_); mpz_init(c); mpz_init(ans);
    mpz_set_ui(n_, n); mpz_set_ui(k_, k); mpz_set_ui(c, n - k);
    fac(n_);
    fac(k_);
    fac(c);
    mpz_mul(ans, k_, c);
    mpz_div(k_, n_, ans);
    mpz_set(x, k_);
    // free
    mpz_clear(n_); mpz_clear(k_); mpz_clear(c); mpz_clear(ans);
}

void
bin_cdf(mpf_t x, u_long n, mpf_t p, u_long k) {
    mpf_t tmp1; mpf_t tmp2; mpf_init(tmp1);  mpf_init(tmp2);
    mpf_set_ui(tmp1, 0); mpf_set_ui(tmp2, 0); mpf_set_ui(x, 0);
    for (long i = 0; i < k + 1; i++) {
        bin_pdf(tmp1, n, p, i);
        mpf_add(x, tmp1, tmp2);
        mpf_set(tmp2, x);
    }
}

void
bin_pdf(mpf_t x, u_long n, mpf_t p, u_long k) {
    mpf_t a, pMin, c, bin, nOverKF;
    mpz_t nOverKRes;
    mpf_init(a); mpf_init(pMin); mpf_init(c); mpf_init(bin); mpz_init(nOverKRes); mpf_init(nOverKF);
    mpf_pow_ui(a, p, k);               // p^k
    mpf_ui_sub(pMin, 1L, p);           // p - 1
    mpf_pow_ui(c, pMin, (n - k));      // (p - 1)^(n-k)
    mpf_mul(x, a, c);
    ncr(nOverKRes, n, k);
    mpf_set_z(nOverKF, nOverKRes);
    mpf_mul(a, x, nOverKF);
    mpf_set(x, a);
    mpf_clear(a); mpf_clear(pMin); mpf_clear(c); mpf_clear(bin); mpz_clear(nOverKRes); mpf_clear(nOverKF);
}

double
bisection(func* f, double a, double b) {
    double m;                            // left, right border

    while ((b - a) > 0.0001) {
        m = (a + b) / 2;
        if (get_y(f, a) * get_y(f, m) <= 0) {          // Zero between a and m
            b = m;
        }
        else {
            a = m;
        }
    }
    func_free(f);
    return m;
}
