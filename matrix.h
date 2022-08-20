#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tuple.h"
typedef struct matrix {
  int height;
  int width ;
  float * rows[]; 
}matrix;

matrix * createMatrix(int, int);

void setCell(matrix* ,int, int, float);

float getCell(matrix* , int, int);

int matEquals(matrix*, matrix*);

matrix* matMultiply(matrix*, matrix*);

tuple* matTupleMultiply(matrix*, tuple*);

matrix* identityMatrix(int, int);

matrix* transposeMatrix(matrix*);

float matrixDeterminat(matrix*);

matrix* subMATRIX(matrix*,int,int);

float matrixMinors(matrix*, int, int);

float matrixCofactor(matrix*, int, int);

float matrixDeterminants(matrix*);

int isMatrixInvertable(matrix*);

void printMatrix(matrix*);

int  test_matrix();



#endif //MATRIX_H
