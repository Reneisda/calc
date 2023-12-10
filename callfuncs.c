#include <stdio.h>
#include "callfuncs.h"
#include <string.h>
#include <math.h>
static int base, precision;

void
init(int base_, int precision_) {
    base = base_;
    precision = precision_;
}

char*
get_val(char* str) {
    size_t size = strlen(str);
    char* values = malloc(size);
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
    fprintf(stdout, "%f\n%f", answer[0], answer[1]);

}


/*
void out_fac(char* str);
void out_ncr(char* str);
void out_bin_pdf(char* str);
void out_bin_cdf(char* str);
*/