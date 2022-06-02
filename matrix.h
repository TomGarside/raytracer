#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matrix {
  int height;
  int width ;
  float * rows[]; 
}matrix;

matrix * createMatrix();

void setCell(matrix *,int,int, float);

float getCell(matrix *, int,int);

int  test_matrix();

#endif //MATRIX_H
