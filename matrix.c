#include "matrix.h"


matrix *createMatrix(int width, int height ){
  matrix* newMat = malloc(sizeof *newMat+sizeof*(newMat->rows)*width);
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

int test_matrix(){

  return 1; 
}
