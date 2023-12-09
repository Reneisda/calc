#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <gmp.h>

int p_out = 10;
void binPdf(mpf_t x, long n, mpf_t p, long k);

void pq(double *answer, double p, double q) {
    double pHalf = p / 2;
    double a = (pHalf) * -1;
    double inSqr = pHalf * pHalf - q;
    if (inSqr < 0) { fprintf(stderr, "Can't calculate sqrt of negative number: %f\n", inSqr); return; }
    double b = sqrt(inSqr);
    answer[0] = a + b;
    answer[1] = a - b;
}

void fac(mpz_t x) {
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set_ui(tmp, 1);
    u_long fak = mpz_get_ui(x);
    mpz_set_ui(x, 1);
    for (fak; fak > 0; fak--) {
        mpz_mul_ui(x, tmp, fak);
        mpz_set(tmp, x);
    }
}
void ncr(mpz_t x, long n, long k) {
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

double binCdf(mpf_t x, long n, mpf_t p, long k) {
    mpf_t tmp1; mpf_t tmp2; mpf_init(tmp1);  mpf_init(tmp2);
    mpf_set_ui(tmp1, 0); mpf_set_ui(tmp2, 0); mpf_set_ui(x, 0);
    for (long i = 0; i < k + 1; i++) {
        binPdf(tmp1, n, p, i);
        mpf_add(x, tmp1, tmp2);
        mpf_set(tmp2, x);
    }
}

void binPdf(mpf_t x, long n, mpf_t p, long k) {
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

int main(int argc, char *argv[]) {
    int opt;
    enum { PQ_MODE, FAK_MODE, DEFAULT } mode = DEFAULT;
    while ((opt = getopt(argc, argv, "pfb")) != -1) {
        switch (opt) {
            case 'p': mode = PQ_MODE; break;
            case 'f': mode = FAK_MODE; break;
            case 'b': mode = DEFAULT; break;
            default:
                fprintf(stdout, "calc 1.2\nTry -h or --help\n");
        }
    }
    double answer[2];
    mpz_t a_ui; mpz_init(a_ui);

    switch (mode) {
        case PQ_MODE:
            pq(answer, strtod(argv[optind], NULL),
               strtod(argv[optind + 1], NULL));
            printf("x1: %f\nx2: %f\n", answer[0], answer[1]);
            break;
        case FAK_MODE:
            printf("%s\n", argv[optind + 1]);               //FIXME
            mpz_init_set_str(a_ui, argv[optind + 1], 10);
            fac(a_ui);
            mpz_out_str(stdout, 10, a_ui);
            printf("\n");
            break;
        default:
            fprintf(stderr, "Something went wrong\n"); break;
    }
    // Now optind (declared extern int by <unistd.h>) is the index of the first non-option argument.
    // If it is >= argc, there were no non-option arguments.

    // ...
    return 0;
}