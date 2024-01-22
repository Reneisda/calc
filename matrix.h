#include "vector.h"
#include <stdlib.h>
#include <time.h>

#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H


typedef struct matrix {
    double* table;
    int rows;
    int columns;
    double determinant;
    u_int8_t quadratic;
} matrix_t;

typedef struct matrix_2 {
    double** table;
    int rows;
    int columns;
    double determinant;
    u_int8_t quadratic;
} matrix_2_t;

void        mat_init(matrix_t* m, double* table, int rows, int cols);
void        mat_2_init(matrix_2_t* m, double** table, int rows, int cols);
void        mat_init_rand(matrix_t* m, int size);
void        mat_2_init_rand(matrix_2_t *m, int size);
void        mat_2_init_ascending_values(matrix_2_t *m, int size);
void        mat_2_init_unit(matrix_2_t *m, int size);
void        convert_m2_to_m(matrix_2_t* m2, matrix_t* m);
void        mat_del_row(matrix_t* m, matrix_t* m2, int row, int col);
void        mat_del_col(matrix_t* m, matrix_t* m2, int col);
void        mat_init_vec(matrix_t m, vector_t* v);
double      mat_det(matrix_t* m);
u_int8_t    mat_is_quad(matrix_t m);
void        mat_print(matrix_t* m);
void        mat_2_print(matrix_2_t* m);
double      mat_det_gauss(matrix_t* m);
double      mat_det_gauss2(matrix_t* m);
double      mat_2_det_gauss(matrix_2_t* m);
void        align(matrix_t* dest, matrix_t* source);
#endif //CALC_MATRIX_H
