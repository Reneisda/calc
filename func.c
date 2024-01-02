#include "func.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define val_endptr struct val_end_pos

struct val_end_pos {
    double value;
    char* end_pos;
};

void func_free(func* f) {
    free(f->coefficient);
    free(f->exp);
}

double
func_y(func* f, double x) {
    double value = 0;
    for (int i = 0; i <= f->size; ++i) {
        value += pow(x, f->exp[i]) * f->coefficient[i];
    }
    return value;
}

void
cleanup(func* f) {
    for (int i = 0; i < f->size; ++i) {
        if (f->coefficient[i] == 0) {
            for (int j = i; j < f->size; j++) {
                f->coefficient[j] = f->coefficient[j + 1];
                --f->size;
            }
        }
    }
}

void
func_derive(func* f) {
    for (int i = 0; i < f->size; ++i) {
        if (f->exp[i] == 0) {
            f->coefficient[i] = 0;
            continue;
        }
        f->coefficient[i] *= f->exp[i];
        --f->exp[i];
    }
    cleanup(f);
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
    printf("Size: %zu\n", f->size);
    for (int i = 0; i < f->size; ++i) {
        printf("%f\t", f->exp[i]);
    }
    printf("\n");
    for (int i = 0; i < f->size; ++i) {
        printf("%f\t", f->coefficient[i]);
    }
    printf("\n");
}

void
func_copy(func* dest, func* src) {
    dest->coefficient = (double*) malloc(sizeof(double) * src->size);
    dest->exp = (double*) malloc(sizeof(double) * src->size);
    dest->size = src->size;

    memcpy(dest->coefficient, src->coefficient, src->size * sizeof(double));
    memcpy(dest->exp, src->exp, src->size * sizeof(double));
}

void
get_coefficient(char* pos, val_endptr* v) {
    if (pos[0] == 'x') {
        v->value = 1.F;
        v->end_pos = pos + 1;
        return;
    }
    if (pos[0] == '+' && pos[1] == 'x') {
        v->value = 1.F;
        v->end_pos = pos + 2;
        return;
    }
    if (pos[0] == '-' && pos[1] == 'x') {
        v->value = -1.F;
        v->end_pos = pos + 2;
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
    size_t mem_size = 8;
    func f;
    f.size = 0;
    size_t len = strlen(str);
    char* init_pos = str;

    if (strchr(str, 'x') == NULL) {                 // eg. 20, -69
        f.coefficient = (double*) malloc(sizeof(double));
        f.exp = (double*) malloc(sizeof(double));
        f.size = 1;
        f.coefficient[0] = strtod(str, NULL);
        f.exp[0] = 0;
        return f;
    }

    f.coefficient = (double*) malloc(sizeof(double) * mem_size);
    f.exp = (double*) malloc(sizeof(double) * mem_size);
    val_endptr coeff;
    val_endptr expon;

    while (init_pos + len > str) {
        if (str[0] == 0) {
            break;
        }
        if (f.size > mem_size - 1) {                // resize
            mem_size *= 2;
            f.coefficient = realloc((f.coefficient), (mem_size) * sizeof(double));
            f.exp = realloc((f.exp), (mem_size) * sizeof(double));
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
