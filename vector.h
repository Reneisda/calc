
#ifndef CALC_VECTOR_H
#define CALC_VECTOR_H
#include <time.h>
#include <string.h>
#include <stdio.h>


typedef struct vector {
    double* values;
    int dimensions;
    double length;
} vector_t;

void setvec(vector_t* v, double* values);
void setrandvec(vector_t* v, int dimensions);
void printvec(vector_t* v);
#endif //CALC_VECTOR_H
