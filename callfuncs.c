#include <stdio.h>
#include <string.h>
#include "callfuncs.h"
#include "vector.h"
#include "matrix.h"

static int base, precision;

void
init(int base_, int precision_) {
    base = base_;
    precision = precision_;
}

char*
get_val(char* str) {
    size_t size = strlen(str);
    char* values = (char*) malloc(size);
    memcpy(values, str, sizeof(char) * size);
    for (int i = 0; values[i] != '\0'; i++) {
        if (values[i] == ',') {
            values[i] = ' ';
        }
    }
    return values;
}

void
out_pq(char* str) {
    char* parsed_values = get_val(str);
    double p, q;
    char* end = NULL;
    double answer[2];
    p = strtod(parsed_values, &end);
    q = strtod(end, NULL);
    pq(answer, p, q);
    fprintf(stdout, "%f\n%f\n", answer[0], answer[1]);

}

void
out_fac(char* str) {
    u_long in = strtol(str, NULL, 10);
    mpz_t faculty;
    mpz_init_set_ui(faculty, in);
    fac(faculty);
    mpz_out_str(stdout, base, faculty);
    printf("\n");
}

void
out_npr(char* str) {
    u_long n, k;
    mpz_t answer;
    mpz_init(answer);
    char* end;
    char* parsed_values = get_val(str);
    n = strtoul(parsed_values, &end, 10);
    k = strtoul(end, NULL, 10);
    npr(answer, n, k);
    mpz_out_str(stdout, base, answer);
    printf("\n");
}

void
out_ncr(char* str) {
    u_long n, k;
    mpz_t answer;
    mpz_init(answer);
    char* end;
    char* parsed_values = get_val(str);
    n = strtoul(parsed_values, &end, 10);
    k = strtoul(end, NULL, 10);
    ncr(answer, n, k);
    mpz_out_str(stdout, base, answer);
    printf("\n");
}

void
out_bin_pdf(char* str) {
    u_long n, k;
    double p;
    char* end;
    mpf_t prob, answer;
    char* parsed_values = get_val(str);
    n = strtoul(parsed_values, &end, 10);
    p = strtod(end, &end);
    k = strtoul(end, NULL, 10);
    mpf_init_set_d(prob, p);
    mpf_init(answer);
    bin_pdf(answer, n, prob, k);
    mpf_out_str(stdout, base, precision, answer);
    printf("\n");
}

void
out_bin_cdf(char* str) {
    u_long n, k;
    double p;
    char* end;
    mpf_t prob, answer;
    char* parsed_values = get_val(str);
    n = strtoul(parsed_values, &end, 10);
    p = strtod(end, &end);
    k = strtoul(end, NULL, 10);
    mpf_init_set_d(prob, p);
    mpf_init(answer);
    bin_cdf(answer, n, prob, k);
    mpf_out_str(stdout, base, precision, answer);
    printf("\n");
}

void
out_bisection(char* str, double x, double y) {
    func f = func_get(str);
    printf("%f\n", bisection(&f, x, y));
    func_free(&f);
}

void out_newton_zero(char* str, double x) {
    func f = func_get(str);
    printf("%f\n", newton_zero(&f, x));
    func_free(&f);
}

void out_rand_matrix_determinant(char* str) {
    size_t size = strtoul(str, NULL, 10);
    //matrix_t m1;
    matrix_2_t m2;
    //mat_init_rand(&m1, (int) size);
    mat_2_init_rand(&m2, (int) size);
    //convert_m2_to_m(&m2, &m1);
    //mat_print(&m1);
    //mat_2_print(&m2);
    //printf("Determinante %f\n", mat_det_gauss2(&m1));
    printf("Determinante %f\n", mat_2_det_gauss(&m2));
    //printf("\n");
    //mat_print(&m);
}

