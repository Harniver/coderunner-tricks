#include <stdio.h>

#include "matrix.h"
#include "data.c"

typedef Matrix __matrix_type;
typedef const Matrix __matrix_const;

void __matrix_free(__matrix_type a) {
    free(a.data);

    return;
}

// Prints a Matrix
void __matrix_print(__matrix_const a) {
    printf("(%d,%d)\n", a.rows, a.cols);
    printf("[");
    for (int i=0; i<a.rows; i++) {
        printf("[");
        for (int j=0; j<a.cols; j++) {
            if (j>0) printf(",");
            printf(__data_f, a.data[i*a.cols+j]);
        }
        printf("]");
        if ((i+1)<a.rows) printf("\n");
        
    }
    printf("]\n");

    return;
}

// Builds a Matrix from a string
__matrix_type __matrix_build(const char *s) {
    Matrix mat;

    mat.rows = (s[0]-'0')*10 + (s[1]-'0');
    mat.cols = (s[2]-'0')*10 + (s[3]-'0');

    mat.data = malloc(sizeof(__data_t)*mat.rows*mat.cols);

    for (int i=0; i<mat.rows; i++)
        for (int j=0; j<mat.cols; j++)
            mat.data[i*mat.cols+j] = __data_r(s[4+i*mat.cols+j]);

    return mat;
}

