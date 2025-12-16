#ifndef __MATRIX_H
#define __MATRIX_H

#include "data.h"

typedef struct matrix Matrix;

struct matrix {
    int rows;
    int cols;
    __data_t *data;
};

#endif