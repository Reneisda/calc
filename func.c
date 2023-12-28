#include "func.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define val_endptr struct val_end_pos

struct val_end_pos {
    double value;
    char* end_pos;
};

void
func_free(func* f) {
    free(f->coefficient);
    free(f->exp);
    free(f);
}


double
get_y(func* f, double x) {
    double value = 0;
    for (int i = 0; i <= f->size; i++) {
        value += pow(x, f->exp[i]) * f->coefficient[i];
    }
    return value;
}

void
func_print(func* f) {
    for (size_t i = 0; i < f->size; ++i) {
        if (f->coefficient[i] >= 0) {
            printf("+");
        }
        printf("%.2f", f->coefficient[i]);
        printf("%c", 'x');
        printf("^%.2f", f->exp[i]);
    }
    printf("\n");
}

void
func_print_raw(func* f) {
    printf("Size: %lu\n", f->size);
    for (int i = 0; i < f->size; i++) {
        printf("%f ", f->coefficient[i]);
    }
    printf("\n");
    for (int i = 0; i < f->size; i++) {
        printf("%f ", f->exp[i]);
    }
    printf("\n");
}
/*
 * Input-scheme:
 * ax^b+cx^d-ex^4
 */
void
get_coefficient(char* pos, val_endptr* v) {
    if (pos[0] == 'x') {
        v->value = 1.F;
        v->end_pos = pos + 1;
        return;
    }

    v->value = strtod(pos, &v->end_pos);
    ++v->end_pos;
}

void
get_exp(char* pos, val_endptr* v) {
    if (pos[0] != '^') {
        if (*(pos - 1) == 'x') {
            v->value = 1.F;
            v->end_pos = pos;
        }
        else {
            v->value = 0;
            v->end_pos = pos;
        }
        return;
    }

    v->value = strtod(pos + 1, &v->end_pos);
}

func
func_get(char* str) {
    func f;
    f.size = 0;
    size_t len = strlen(str);
    char* init_pos = str;

    if (strchr(str, 'x') == NULL) {                 // eg. 20, -69
        f.size = 0;
        f.coefficient = NULL;
        f.exp = NULL;
        return f;
    }

    f.coefficient = (double*) malloc(sizeof(double) * 20);
    f.exp = (double*) malloc(sizeof(double) * 20);
    val_endptr coeff;
    val_endptr expon;

    while (init_pos + len > str) {
        if (str[0] == 0) {
            break;
        }
        get_coefficient(str, &coeff);
        get_exp(coeff.end_pos, &expon);
        f.coefficient[f.size] = coeff.value;
        f.exp[f.size] = expon.value;
        str = expon.end_pos;
        ++f.size;
    }
    return f;
}
