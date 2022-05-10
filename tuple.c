#include "tuple.h"

tuple* createTuple(float x, float y, float z, float w){
  tuple *newTup;
  newTup = malloc(sizeof(tuple));
  newTup->x = x;
  newTup->y = y;
  newTup->z = z;
  newTup->w = w;
 
  return  newTup; 
}
//overwrites a tuple 
void writeTuple(float x, float y, float z, float w,tuple* newTup){
  newTup->x = x;
  newTup->y = y;
  newTup->z = z;
  newTup->w = w;
}

tuple* zeroVector(){
  return createTuple(0,0,0,0);
}

tuple * point(float x, float y, float z){
  return createTuple(x,y,z,1.0);
}

tuple * vector(float x, float y, float z){
  return createTuple(x,y,z,0.0);
}

int isPoint(tuple* tp){
  if(tp->w == 1.0)
    return 1;
  return 0; 
}

int isVect(tuple* tp){
  if(tp->w == 0)
    return 1;
  return 0;
}

tuple* add( tuple* a, tuple*b){
  float x = a->x + b->x;
  float y = a->y + b->y;
  float z = a->z + b->z;
  float w = a->w + b->w;
  return createTuple(x, y, z, w);
}

tuple* subtract(tuple* a, tuple*b){
  float x = a->x - b->x;
  float y = a->y - b->y;
  float z = a->z - b->z;
  float w = a->w - b->w;
  return createTuple(x, y, z, w);
}

tuple * negate( tuple*a){
  return subtract(zeroVector(),a);
}

tuple * scalarMultiply(float scalar, tuple *a){
  float x = a->x * scalar;
  float y = a->y * scalar;
  float z = a->z * scalar;
  float w = a->w * scalar;
  return createTuple(x, y, z, w);

}

tuple * scalarDivide(float scalar, tuple *a){
  float x = a->x / scalar;
  float y = a->y / scalar;
  float z = a->z / scalar;
  float w = a->w / scalar;
  return createTuple(x, y, z, w);
}

// magnitude
float magnitude(tuple *a){
  return sqrt (pow(a->x, 2.0f)+
	       pow(a->y, 2.0f)+
	       pow(a->z, 2.0f)+
	       pow(a->w, 2.0f));
}

// normalize
tuple * normalize(tuple * a){
  float mag = magnitude(a);
  return createTuple(a->x/mag, a->y/mag, a->z/mag, a->w/mag);
}

// dot Product
float dotProduct(tuple*a, tuple *b){
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);

}

// cross product
tuple * crossProduct(tuple *a, tuple*b){
  float x = (a->y * b->z) - (a->z * b->y);
  float y = (a->z * b->x) - (a->x * b->z);
  float z = (a->x * b->y) - (a->y * b->x);
  return vector(x, y, z);
  
}


// helper functions 
void printTuple(tuple* t){
   printf("x:%f y:%f x:%f w:%f\n", t->x, t->y, t->z, t->w);
}




// unit testing function 
int test_tuple(){

  // test point
  tuple * testPoint = createTuple(4.3,-4.2,3.1,1.0);
  tuple * otherPoint = point(4.3,-4.2,3.1);
  // points are points not vects 
  assert(isPoint(testPoint));
  assert(!isVect(testPoint));
  // points are created 
  assert(testPoint->x == 4.3f);
  assert(testPoint->y == -4.2f);
  assert(testPoint->z == 3.1f);
  // test point function 
  assert(testPoint->x == otherPoint->x && testPoint->y == otherPoint->y && testPoint->z == otherPoint->z);
  free(testPoint);
  free(otherPoint);
  
  // test vect
  tuple * vect = createTuple(4.3,-4.2,3.1,0);
  tuple * otherVect = vector(4.3,-4.2,3.1);
  // vectors are vectors not points
  assert(!isPoint(vect));
  assert(isVect(vect));
  // values are created successfully 
  assert(vect->x == 4.3f);
  assert(vect->y == -4.2f);
  assert(vect->z == 3.1f);
  // vector creates vectors not points 
  assert( vect->x == otherVect->x && vect->y == otherVect->y && vect->z == otherPoint->z);
  free(vect);
  free(otherVect); 

  //test zero vector
  tuple * zVect = zeroVector();
  assert(!isPoint(zVect));
  assert(isVect(zVect));
  assert(zVect->x == 0.0f);
  assert(zVect->y == 0.0f);
  assert(zVect->z == 0.0f);
  free(zVect);
  
  // Add 
  // add creates a sum of vectors
  tuple * sumVect = createTuple(4.3,-4.2,3.1,0);
  tuple * sumOtherVect = vector(4.3,-4.2,3.1);
  tuple * summ = add(sumVect,sumOtherVect);
  assert(summ->x == 8.6f);
  assert(summ->y == -8.4f);
  assert(summ->z == 6.2f);
  assert(summ->w == 0.0f);
  free(summ);
  free(sumVect);
  free(sumOtherVect); 
  
  // subtract 
  // creates a new vector
  tuple * subPointA = point(3.0f,2.0f,1.0f);
  tuple * subPointB = point(5.0f,6.0f,7.0f);
  tuple * subVectA = vector(3.0f,2.0f,1.0f);
  tuple * subVectB = vector(5.0f,6.0f,7.0f);
  tuple* subProduct = subtract(subPointA, subPointB);

  assert(subProduct->x == -2.0f);
  assert(subProduct->y == -4.0f);
  assert(subProduct->z == -6.0f);
  assert(isVect(subProduct));

  subProduct = subtract(subPointA,subVectB);
  assert(subProduct->x == -2.0f);
  assert(subProduct->y == -4.0f);
  assert(subProduct->z == -6.0f);
  assert(isPoint(subProduct));

  subProduct = subtract(subVectA, subVectB);
  assert(subProduct->x == -2.0f);
  assert(subProduct->y == -4.0f);
  assert(subProduct->z == -6.0f);
  assert(isVect(subProduct));

  free(subPointA);
  free(subPointB);
  free(subVectA);
  free(subVectB);
  free(subProduct);
  
  
  // negate
  tuple * negVectA = createTuple(1.0f,-2.0f,3.0f,-4.0f);
  tuple * negVectB = negate(negVectA);
  assert(negVectB->x == -1.0f);
  assert(negVectB->y == 2.0f);
  assert(negVectB->z == -3.0f);
  assert(negVectB->w == 4.0f);
  free(negVectA);
  free(negVectB);

  
  // scalar multiply
  tuple * mulVectA = createTuple(1.0f,-2.0f,3.0f,-4.0f);
  tuple * mulVectB = scalarMultiply(3.5f, mulVectA);
  assert(mulVectB->x = 3.5f);
  assert(mulVectB->y = -7.0f);
  assert(mulVectB->z = 10.5f);
  assert(mulVectB->w = -14.0f);
  free(mulVectA);
  free(mulVectB);

  //scalar division
  tuple * divVectA = createTuple(1.0f,-2.0f,3.0f,-4.0f);
  tuple * divVectB = scalarDivide(2.0f, divVectA);
  assert(divVectB->x = 0.5f);
  assert(divVectB->y = -1.0f);
  assert(divVectB->z = 1.5f);
  assert(divVectB->w = -2.0f);
  free(divVectA);
  free(divVectB);
  
  //magnitude
  tuple * magVectA = vector(1.0f,0.0f,0.0f);
  assert(magnitude(magVectA) == 1.0f);
  free(magVectA);
  
  tuple *magVectB = vector(0.0f,0.0f,1.0f);
  assert(magnitude(magVectB) == 1.0f);
  free(magVectB);
  
  tuple * magVectC = vector(1.0f,2.0f,3.0f);
  assert(magnitude(magVectC) == sqrtf(14.0f));
  free(magVectC);
  
  tuple * magVectD = vector(-1.0f,-2.0f,-3.0f);
  assert(magnitude(magVectD) == sqrtf(14.0f));
  free(magVectD);
  
  //normalize
  tuple * normVectA = vector(4.0f,0.0f,0.0f);
  tuple * normalizedA = normalize(normVectA);
  assert(normalizedA->x == 1.0f);
  assert(normalizedA->y == 0.0f);
  assert(normalizedA->z == 0.0f);
  assert(normalizedA->w == 0.0f);
  free(normVectA);
  free(normalizedA);
  
  tuple * normVectB = vector(1.0f,2.0f,3.0f);
  tuple * normalizedB = normalize(normVectB);
  assert(normalizedB->x == 1.0f/sqrtf(14.0f));
  assert(normalizedB->y == 2.0f/sqrtf(14.0f));
  assert(normalizedB->z == 3.0f/sqrtf(14.0f));
  free(normVectB);
  free(normalizedB);
  
  //Dot product
  tuple* dotVectA = vector(1.0f,2.0f,3.0f);
  tuple* dotVectB = vector(2.0f,3.0f,4.0f);
  assert(dotProduct(dotVectA, dotVectB) == 20.0f);
  free(dotVectA);
  free(dotVectB);  
  
  //Cross product
  tuple* crossVectA = vector(1.0f,2.0f,3.0f);
  tuple* crossVectB = vector(2.0f,3.0f,4.0f);
  tuple* crossProdA = crossProduct(crossVectA, crossVectB);
  assert(crossProdA->x == -1.0f);
  assert(crossProdA->y == 2.0f);
  assert(crossProdA->z == -1.0f);
  tuple* crossProdB = crossProduct(crossVectB, crossVectA);
  assert(crossProdB->x == 1.0f);
  assert(crossProdB->y == -2.0f);
  assert(crossProdB->z == 1.0f);
  free(crossVectA);
  free(crossVectB);
  free(crossProdA);
  free(crossProdB);
 
  
  
  return 1; 
}
