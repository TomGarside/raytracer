#ifndef TUPLE_H
#define TUPLE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tuple {
  float x;
  float y;
  float z;
  float w;
 
}tuple;

tuple * createTuple(float x, float y, float z, float w);

void writeTuple(float x, float y, float z, float w, tuple* newTup);

int isPoint(tuple * );

int isVector(tuple *);

tuple * point(float x, float y, float z);

tuple * vector(float x, float y, float z);

tuple * zeroVector();

tuple * add(tuple* a, tuple* b);

tuple * subtract(tuple* a, tuple* b);

tuple * negate( tuple* a);

tuple * scalarMultiply(float scalar, tuple * a);

tuple * scalarDivide(float scalar, tuple * a);

tuple * normalize(tuple * a);

tuple * crossProduct(tuple * a, tuple *b);

float dotProduct(tuple * a, tuple * b); 

float magnitude(tuple * a);

void printTuple(tuple* t);

int test_tuple();

#endif //TUPLE_H
