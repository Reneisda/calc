#include "vector.h"
#include "matrix.h"
#include <math.h>
#include <stdlib.h>



void
setvec(vector_t* v, double* values) {
    v->dimensions = sizeof(values);
    v->values = (double*) malloc(sizeof(values) * sizeof(double));
    memcpy(values, v->values, sizeof(values) * sizeof(double));
}

void
setrandvec(vector_t* v, int dimensions) {
    srand(time(NULL));
    v->dimensions = dimensions;
    v->values = (double*) malloc(sizeof(double) * dimensions);
    for (int i = 0; i < dimensions; ++i) {
        v->values[i] = rand() / 1000000.0f * ((rand() % 2) ? -1 : 1);
    }
}


double callen(vector_t v) {
    double sumofsq = 0;
    for (int i = 0; i < v.dimensions; ++i) {
        sumofsq += v.values[i] * v.values[i];
    }
    return sqrt(sumofsq);
}

double dotp(vector_t v, vector_t u) {
    double dotp = 0;
    for (int i = 0; i < v.dimensions; ++i) {
        dotp += v.values[i] * u.values[i];
    }
    return dotp;
}

void normalizevec(vector_t v) {
    double factor = 1 / callen(v);
    for (int i = 0; i < v.dimensions; ++i) {
        v.values[i] = v.values[i] * factor;
    }
    v.length = 1;
}

u_int8_t isnulvec(vector_t v) {
    for (int i = 0; i < v.dimensions; ++i) {
        if (v.values[i] != 0)
            return 0;
    }
    return 1;
}

void addvec(vector_t v, vector_t u) {
    for (int i = 0; i < v.dimensions; ++i) {
        v.values[i] += u.values[i];
    }
}

void subvec(vector_t v, vector_t u) {
    for (int i = 0; i < v.dimensions; ++i) {
        v.values[i] -= u.values[i];
    }
}

void mulvec(vector_t v, double scalar) {
    for (int i = 0; i < v.dimensions; ++i) {
        v.values[i] *= scalar;
    }
}

void printvec(vector_t* v) {
    for (int i = 0; i < v->dimensions; ++i) {
        printf("%d: %f\n", i, v->values[i]);
    }
}
/*
vector_t crossp(vector_t* v) {
    int count = sizeof(*v) / sizeof(v[0]);
    vector_t cross;
    setvec(&cross, v[0].values);
    cross.dimensions = v[0].dimensions;
    matrix_t calmat;
    mat_init_vec(calmat, v);
    for (int i = 0; i < count; ++i) {
        cross.values[i] = pow(-1, i) * mat_det(mat_del_col(calmat,i));
    }
    callen(cross);
    return cross;

}

 */