#include "matrix.h"


matrix *createMatrix(int width, int height ){
  matrix* newMat = malloc(sizeof *newMat+sizeof*(newMat->rows)*width);
  newMat->width = width;
  newMat->height = height; 
  for(int x=0;x<width;x++){
    newMat->rows[x] = malloc(sizeof*(newMat->rows[x])*height);
    for(int y=0; y<height; y++){
      newMat->rows[x][y] = 0.0f;
    }}
  
  return newMat;

}


void setCell(matrix* mat, int x, int y, float val){
  mat->rows[x][y] = val;
}

float getCell(matrix* mat, int x , int y ){
  return mat->rows[x][y];
}

int matrixEquals(matrix* matA, matrix* matB){
  // test matrixes are the same size 
  if (matA->height != matB->height){
    return 0; 
  }
  if (matA->width != matB->width){
    return 0; 
  }

  for(int x=0; x<matA->width; x++){
    for(int y=0; y<matA->height; y++){
      if(getCell(matA,x,y) != getCell(matB,x,y))
	 return 0; 
    }
  }
    return 1; 
}


int test_matrix(){
  //4x4 matrix test
  matrix* testMat1 = createMatrix(4,4);
  setCell(testMat1,0,0,1.0f);
  setCell(testMat1,0,1,2.0f);
  setCell(testMat1,0,2,3.0f);
  setCell(testMat1,0,3,4.0f);

  setCell(testMat1,1,0,5.5f);
  setCell(testMat1,1,1,6.5f);
  setCell(testMat1,1,2,7.5f);
  setCell(testMat1,1,3,8.5f);

  setCell(testMat1,2,0,9.0f);
  setCell(testMat1,2,1,10.0f);
  setCell(testMat1,2,2,11.0f);
  setCell(testMat1,2,3,12.0f);

  setCell(testMat1,3,0,13.5f);
  setCell(testMat1,3,1,14.5f);
  setCell(testMat1,3,2,15.5f);
  setCell(testMat1,3,3,16.5f);

  assert(getCell(testMat1,0,0) == 1.0f);
  assert(getCell(testMat1,0,3) == 4.0f);
  assert(getCell(testMat1,1,0) == 5.5f);
  assert(getCell(testMat1,1,2) == 7.5f);
  assert(getCell(testMat1,2,2) == 11.0f);
  assert(getCell(testMat1,3,0) == 13.5f);
  assert(getCell(testMat1,3,2) == 15.5f);

  //2x2 matrix test
  matrix* testMat2 = createMatrix(2,2);
  setCell(testMat2,0,0,-3.0f);
  setCell(testMat2,0,1,5.0f);
  setCell(testMat2,1,0,1.0f);
  setCell(testMat2,1,1,-2.0f);

  assert(getCell(testMat2,0,0) == -3.0f);
  assert(getCell(testMat2,0,1) == 5.0f);
  assert(getCell(testMat2,1,0) == 1.0f);
  assert(getCell(testMat2,1,1) == -2.0f);

  //3x3 matrix test
  matrix* testMat3 = createMatrix(3,3);
  setCell(testMat3,0,0,-3.0f);
  setCell(testMat3,0,1,5.0f);
  setCell(testMat3,0,2,0.0f);

  setCell(testMat3,1,0,1.0f);
  setCell(testMat3,1,1,-2.0f);
  setCell(testMat3,1,2,-7.0f);

  setCell(testMat3,2,0,0.0f);
  setCell(testMat3,2,1,1.0f);
  setCell(testMat3,2,2,1.0f);

  assert(getCell(testMat3,0,0) == -3.0f);
  assert(getCell(testMat3,1,1) == -2.0f);
  assert(getCell(testMat3,2,2) == 1.0f);


  //Matrix equality test 
  matrix* testMat4 = createMatrix(4,4);
  matrix* testMat5 = createMatrix(4,4);
  matrix* testMat6 = createMatrix(4,4);
  int counter = 1;
  for(int x=0; x<4; x++){
    for(int y=0; y<4; y++){
      setCell(testMat4,x,y,(float)counter);
      setCell(testMat5,x,y,(float) counter);
      counter++;
    }
  }

  counter = 2; 
  for(int x=0; x<4; x++){
    for(int y=0; y<4; y++){
      setCell(testMat6,x,y,(float)counter);
      counter++;
    }
  }

  
  assert(matrixEquals(testMat4,testMat5));
  assert(!matrixEquals(testMat4,testMat6));

  //Multiply matrix 
  
  return 1; 
}
