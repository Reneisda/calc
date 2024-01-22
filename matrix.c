#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdint.h>

void
mat_init(matrix_t* m, double* table, int rows, int cols) {
    m->table = (double*) malloc(sizeof(double) * rows * cols);
    m->rows = rows;
    m->columns = cols;
    memcpy(m->table, table, rows * cols * sizeof(double));
}

void
mat_init_rand(matrix_t* m, int size) {
    m->rows = size;
    m->columns = size;
    srand(time(NULL));                                          // NOLINT (pseudo-rand)
    m->table = (double*) malloc(sizeof(double) * size * size);
    for (int i = 0; i < size * size; ++i) {
            m->table[i] = (rand() - (double)(RAND_MAX) / 2) / 10000000;       // NOLINT (pseudo-rand)
    }
}

void
mat_2_init(matrix_2_t *m, double** table, int rows, int cols) {
    m->columns = cols;
    m->rows = rows;
    m->table = (double**) malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; ++i) {
        m->table[i] = (double*) malloc(cols * sizeof(double));
        for (int j = 0; j < cols; ++j) {
            m->table[i][j] = table[i][j];
        }
    }
}

void
mat_2_init_rand(matrix_2_t *m, int size) {
    m->columns = size;
    m->rows = size;
    //srand(time(NULL));                                           // NOLINT (pseudo-rand)
    srand(727); // NOLINT (pseudo-rand)
    m->table = (double**) malloc(size * sizeof(double*));
    for (int i = 0; i < size; ++i) {
        m->table[i] = (double*) malloc(size * sizeof(double));
        for (int j = 0; j < size; ++j) {
            m->table[i][j] = (rand() - (double)(RAND_MAX) / 2) / 10000000;      // NOLINT (pseudo-rand)
        }
    }
}

void
mat_2_init_ascending_values(matrix_2_t *m, int size) {
    m->columns = size;
    m->rows = size;
    m->table = (double**) malloc(size * sizeof(double*));
    int val = 0;
    for (int i = 0; i < size; ++i) {
        m->table[i] = (double*) malloc(size * sizeof(double));
        for (int j = 0; j < size; ++j) {
            m->table[i][j] = ++val;
        }
    }
}

void
mat_2_init_unit(matrix_2_t *m, int size) {
    m->columns = size;
    m->rows = size;
    m->table = (double**) malloc(size * sizeof(double*));
    for (int i = 0; i < size; ++i) {
        m->table[i] = (double*) malloc(size * sizeof(double));
        for (int j = 0; j < size; ++j) {
            m->table[i][i] = 1;
        }
    }
}

void
convert_m2_to_m(matrix_2_t* m2, matrix_t* m) {
    m->rows = m2->rows;
    m->columns = m2->columns;
    for (int i = 0; i < m2->rows; ++i) {
        for (int j = 0; j < m2->columns; ++j) {
            m2->table[i][j] = m->table[i * m->rows + j];
        }
    }
}

/*
void
mat_init_vec(matrix_t m, vector_t* v) {
    int count = sizeof(*v) / sizeof(v[0]);
    for (int i = 0; i < count; ++i) {
        m.table[i] = v[i].values;
    }
    m.rows = sizeof(*v) / sizeof(v[0]);
    m.columns = sizeof(v[0]) / sizeof(v[0].values[0]);
    m.quadratic = mat_is_quad(m);
}
*/

u_int8_t mat_is_quad(matrix_t m) {
    return m.rows == m.columns;

}

double mat_det(matrix_t* m) {       //NOLINT (recursion)
    double det = 0;
    int n = m->rows;
    if (n == 2) {
        return m->table[0] * m->table[m->columns + 1] - m->table[m->columns] * m->table[1];
    }
    matrix_t minor;
    for (int i = 0; i < n; ++i) {
        if(m->table[i * m->columns] == 0) {
            continue;
        }
        mat_del_row(m, &minor, i, 0);
        det += pow(-1, i) * m->table[i * m->columns] * mat_det(&minor);
        free(minor.table);
    }

    return det;
}

void
swap(double* value_1, double* value_2) {
    double tmp = *value_1;
    *value_1 = *value_2;
    *value_2 = tmp;
}

void
align(matrix_t* dest, matrix_t* source) {
    dest->table = (double *) malloc(2 * source->rows * source->columns * sizeof(double));
    size_t index = 0;
    for (int i = 0; i < source->rows; ++i) {
        for (int j = 0; j < source->columns; ++j) {
            dest->table[index] = (source->table[i * source->columns + j]);
        }
    }
}

void add_rows(matrix_t* m, int row1, int row2, double factor) {
    register int a = row1 * m->columns;
    register int b = row2 * m->columns;
    for (int i = 0; i < m->columns; ++i) {
        m->table[a + i] += m->table[b + i] * factor;
    }
}

double mat_2_det_gauss(matrix_2_t *m) {
    register int n = m->rows;
    double det = 1;
    for (int i = 0; i < n; ++i) { //O(n)
        double pivot = m->table[i][i];
        //#pragma omp parallel for
        for (int j = i + 1; j < n; ++j) { //O(n/2)
            double factor = -m->table[j][i] / pivot;
            for (int k = 0; k < m->columns; ++k) { //O(n)
                m->table[j][k] += m->table[i][k] * factor;
            }
        }
        det *= pivot;
    }
    // --> O(n * n * (n/2))
    return det;
}

double mat_det_gauss(matrix_t* m) {
    register int n = m->rows;
    double det = 1;
    for (int i = 0; i < n; ++i) {
        //pivot Element festlegen:
        double pivot = m->table[i * m->columns + i];
        for (int j = i + 1; j < n; ++j) {
            //unter dem pivot Element aufräumen:
            add_rows(m, j, i, -m->table[j * m->columns + i] / pivot);
        }
        det *= pivot;
    }
    return det;
}

double mat_det_gauss2(matrix_t* m) {
    register int n = m->rows;
    double det = 1;
    for (int i = 0; i < n; ++i) { //O(n)
        //pivot Element festlegen:
        double pivot = m->table[i * m->columns + i];
        for (int j = i + 1; j < n; ++j) { //O(n/2)
            //unter dem pivot Element aufräumen:
            register int a = j * m->columns;
            register int b = i * m->columns;
            double factor = -m->table[j * m->columns + i] / pivot;
            for (int k = 0; k < m->columns; ++k) { //O(n)
                m->table[a + k] += m->table[b + k] * factor;
            }
        }
        det *= pivot;
    }
    // --> O(n * n * (n/2))
    return det;
}

void mat_del_row(matrix_t* m, matrix_t* m2, int row, int col) {
    double* newTable = (double*) malloc((m->rows - 1) * (m->columns - 1) * sizeof(double));

    for (int i = 0, k = 0; i < m->rows; i++) {
        if (i != row) {
            for (int j = 0, l = 0; j < m->columns; ++j) {
                if (j != col) {
                    newTable[k * (m->columns - 1) + l] = m->table[i * m->columns + j];
                    l++;
                }
            }
            k++;
        }
    }
    mat_init(m2, newTable, m->rows - 1, m->columns - 1);
    free(newTable);
}

void mat_del_col(matrix_t* m, matrix_t* m2, int col){
    double* newTable = (double*) malloc(m->rows * m->columns * sizeof(double));
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0, l = 0; j < m->columns; ++j){
            if(j != col) {
                newTable[i * m->columns + l] = m->table[i * m->columns + l];
                ++l;
            }
        }
    }
    mat_init(m2, newTable, m->rows, m->columns - 1);
    free(newTable);
}


void
print_form(const double* d, uint8_t size) {
    char* str = (char*) malloc(sizeof(char) * 9);
    snprintf(str, sizeof(char) * 9, "%f", *d);
    str[size] = 0;
    printf("%s  ", str);
    free(str);
}

void
mat_print(matrix_t* m) {
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            print_form(&m->table[i * m->columns + j], 8);
        }
        printf("\n");
    }
}

void
mat_2_print(matrix_2_t* m) {
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            print_form(&m->table[i][j], 4);
        }
        printf("\n");
    }
}

