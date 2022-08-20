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
  //test matrix values match 
  for(int x=0; x<matA->width; x++){
    for(int y=0; y<matA->height; y++){
      if(getCell(matA,x,y) != getCell(matB,x,y))
	 return 0; 
    }
  }
    return 1; 
}

matrix* matMultiply(matrix* matA, matrix* matB){
  assert((matA->height == matB->height) && (matA->width == matB->width));
  matrix* newMat = createMatrix(matA->width,matA->height);

  for(int x=0; x<matA->width; x++){
    for(int y=0; y<matA->height; y++){
      float val =0; 
      for(int e=0; e<matA->height; e++){
	val = val + getCell(matA,x,e) * getCell(matB,e,y);
	
      }
      setCell(newMat,x,y,val);
    }
  }
  return newMat;
}

matrix* identityMatrix(int width,int height){
  matrix* newMat = createMatrix(width,height);
  for( int x=0; x<width; x++){
    for(int y=0; y<height;y++){
      if(x==y){
        setCell(newMat,x,y,1.0f);
      }
    }
  }
  return newMat; 
}

matrix* transposeMatrix(matrix* mat){
   matrix* newMat = createMatrix(mat->width,mat->height);
   for(int x=0; x<mat->width;x++){
     for(int y=0; y<mat->height;y++){
       setCell(newMat,x,y,getCell(mat,y,x));
     }
   }

   return newMat;
}


void printMatrix(matrix* mat){
  for( int x=0; x<mat->width; x++){
    printf("| ");
    for ( int y=0; y<mat->height; y++){
      printf("%0.2f |",getCell(mat,x,y));
    }
    printf("\n");	
  }
}

float matrixDeterminat(matrix* mat){
  return (getCell(mat,0,0)*getCell(mat,1,1))-(getCell(mat,0,1)*getCell(mat,1,0));
}

// only works for 4x4
tuple* matTupleMultiply(matrix* mat, tuple* tup){
    float newX=0.0f;
    newX += getCell(mat,0,0)*tup->x;
    newX += getCell(mat,0,1)*tup->y;
    newX += getCell(mat,0,2)*tup->z;
    newX += getCell(mat,0,3)*tup->w;

    float newY=0.0f;
    newY += getCell(mat,1,0)*tup->x;	
    newY += getCell(mat,1,1)*tup->y;
    newY += getCell(mat,1,2)*tup->z;
    newY += getCell(mat,1,3)*tup->w;

    float newZ=0.0f;
    newZ += getCell(mat,2,0)*tup->x;	
    newZ += getCell(mat,2,1)*tup->y;
    newZ += getCell(mat,2,2)*tup->z;
    newZ += getCell(mat,2,3)*tup->w;

    float newW=0.0f;
    newW += getCell(mat,3,0)*tup->x;	
    newW += getCell(mat,3,1)*tup->y;
    newW += getCell(mat,3,2)*tup->z;
    newW += getCell(mat,3,3)*tup->w;

    return createTuple(newX, newY, newZ, newW);
    
}
		       

matrix* subMatrix(matrix* mat, int xCut, int yCut){
  matrix* newMat = createMatrix(mat->width-1, mat->height-1);
  int newX=0;
  int newY=0;
  
  for(int x=0; x<mat->width;x++){
    if(x != xCut){
    for(int y=0; y<mat->height;y++){
      if (x != xCut && y != yCut){
	setCell(newMat,newX,newY,getCell(mat,x,y));
	newY++;
	}
    }
    newY=0;
    newX++;
    }
  }
  return newMat;
}

float matrixMinors(matrix* mat, int xCut, int yCut){
  float retVal = 0; 
  assert(xCut<mat->width && yCut<mat->height);
  retVal=matrixDeterminat(subMatrix(mat,xCut,yCut));
  return retVal;
}

float matrixCofactor(matrix* mat, int xCut, int yCut){
  float minor = matrixMinors(mat,xCut,yCut);
  if(! ((xCut+yCut) % 2 == 0))
     minor = minor * -1.0f;
  return minor;
}

float matrixDeterminant(matrix* mat){
  float retVal = 0.0f;
  
  if(mat->width>2){
    for(int e=0; e<mat->width; e++){
      retVal += matrixCofactor(mat,0,e) * getCell(mat,0,e);
    }
  }
  return retVal; 

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
  matrix* testMat7 = createMatrix(4,4);
  setCell(testMat7,0,0,1.0f);
  setCell(testMat7,0,1,2.0f);
  setCell(testMat7,0,2,3.0f);
  setCell(testMat7,0,3,4.0f);

  setCell(testMat7,1,0,5.0f);
  setCell(testMat7,1,1,6.0f);
  setCell(testMat7,1,2,7.0f);
  setCell(testMat7,1,3,8.0f);

  setCell(testMat7,2,0,9.0f);
  setCell(testMat7,2,1,8.0f);
  setCell(testMat7,2,2,7.0f);
  setCell(testMat7,2,3,6.0f);

  setCell(testMat7,3,0,5.0f);
  setCell(testMat7,3,1,4.0f);
  setCell(testMat7,3,2,3.0f);
  setCell(testMat7,3,3,2.0f);

  
  matrix* testMat8 = createMatrix(4,4);
  setCell(testMat8,0,0,-2.0f);
  setCell(testMat8,0,1,1.0f);
  setCell(testMat8,0,2,2.0f);
  setCell(testMat8,0,3,3.0f);

  setCell(testMat8,1,0,3.0f);
  setCell(testMat8,1,1,2.0f);
  setCell(testMat8,1,2,1.0f);
  setCell(testMat8,1,3,-1.0f);

  setCell(testMat8,2,0,4.0f);
  setCell(testMat8,2,1,3.0f);
  setCell(testMat8,2,2,6.0f);
  setCell(testMat8,2,3,5.0f);

  setCell(testMat8,3,0,1.0f);
  setCell(testMat8,3,1,2.0f);
  setCell(testMat8,3,2,7.0f);
  setCell(testMat8,3,3,8.0f);

  
  matrix* testMat9 = createMatrix(4,4);
  setCell(testMat9,0,0,20.0f);
  setCell(testMat9,0,1,22.0f);
  setCell(testMat9,0,2,50.0f);
  setCell(testMat9,0,3,48.0f);

  setCell(testMat9,1,0,44.0f);
  setCell(testMat9,1,1,54.0f);
  setCell(testMat9,1,2,114.0f);
  setCell(testMat9,1,3,108.0f);

  setCell(testMat9,2,0,40.0f);
  setCell(testMat9,2,1,58.0f);
  setCell(testMat9,2,2,110.0f);
  setCell(testMat9,2,3,102.0f);

  setCell(testMat9,3,0,16.0f);
  setCell(testMat9,3,1,26.0f);
  setCell(testMat9,3,2,46.0f);
  setCell(testMat9,3,3,42.0f);

  matrix* testMat10 = matMultiply(testMat7,testMat8); 
  assert(matrixEquals(testMat9,testMat10));

  // multiply a matrix by tuple 
  tuple* testTup1 = createTuple(1.0f,2.0f,3.0f,1.0f);
  tuple* testTup2 = createTuple(18.0f,24.0f,33.0f,1.0f);
  matrix* testMat11 = createMatrix(4,4);
  setCell(testMat11,0,0,1.0f);
  setCell(testMat11,0,1,2.0f);
  setCell(testMat11,0,2,3.0f);
  setCell(testMat11,0,3,4.0f);

  setCell(testMat11,1,0,2.0f);
  setCell(testMat11,1,1,4.0f);
  setCell(testMat11,1,2,4.0f);
  setCell(testMat11,1,3,2.0f);

  setCell(testMat11,2,0,8.0f);
  setCell(testMat11,2,1,6.0f);
  setCell(testMat11,2,2,4.0f);
  setCell(testMat11,2,3,1.0f);

  setCell(testMat11,3,0,0.0f);
  setCell(testMat11,3,1,0.0f);
  setCell(testMat11,3,2,0.0f);
  setCell(testMat11,3,3,1.0f);

  tuple* testTup3 = matTupleMultiply(testMat11,testTup1);
 
  assert(testTup3->x == 18.0f);
  assert(testTup3->y == 24.0f);
  assert(testTup3->z == 33.0f);
  assert(testTup3->w == 1.0f);

  // transpose matrix
  matrix* testMat12 = createMatrix(4,4);
  setCell(testMat12,0,0,0.0f);
  setCell(testMat12,0,1,9.0f);
  setCell(testMat12,0,2,3.0f);
  setCell(testMat12,0,3,0.0f);

  setCell(testMat12,1,0,9.0f);
  setCell(testMat12,1,1,8.0f);
  setCell(testMat12,1,2,0.0f);
  setCell(testMat12,1,3,8.0f);

  setCell(testMat12,2,0,1.0f);
  setCell(testMat12,2,1,8.0f);
  setCell(testMat12,2,2,5.0f);
  setCell(testMat12,2,3,3.0f);

  setCell(testMat12,3,0,0.0f);
  setCell(testMat12,3,1,0.0f);
  setCell(testMat12,3,2,5.0f);
  setCell(testMat12,3,3,8.0f);


  matrix* testMat13 = createMatrix(4,4);
  setCell(testMat13,0,0,0.0f);
  setCell(testMat13,0,1,9.0f);
  setCell(testMat13,0,2,1.0f);
  setCell(testMat13,0,3,0.0f);

  setCell(testMat13,1,0,9.0f);
  setCell(testMat13,1,1,8.0f);
  setCell(testMat13,1,2,8.0f);
  setCell(testMat13,1,3,0.0f);

  setCell(testMat13,2,0,3.0f);
  setCell(testMat13,2,1,0.0f);
  setCell(testMat13,2,2,5.0f);
  setCell(testMat13,2,3,5.0f);

  setCell(testMat13,3,0,0.0f);
  setCell(testMat13,3,1,8.0f);
  setCell(testMat13,3,2,3.0f);
  setCell(testMat13,3,3,8.0f);
  
  assert(matrixEquals(transposeMatrix(testMat12),testMat13));

  assert(matrixEquals(identityMatrix(4,4), transposeMatrix(identityMatrix(4,4))));

  // 2x2 determinant
  matrix* testMat14 = createMatrix(2,2);

  setCell(testMat14,0,0,1.0f);
  setCell(testMat14,0,1,5.0f);
  setCell(testMat14,1,0,-3.0f);
  setCell(testMat14,1,1,2.0f);

  assert(matrixDeterminat(testMat14) == 17.0f);

  // submatrix

  matrix* testMat15 = createMatrix(3,3);
  setCell(testMat15,0,0,1.0f);
  setCell(testMat15,0,1,5.0f);
  setCell(testMat15,0,2,0.0f);
  
  setCell(testMat15,1,0,-3.0f);
  setCell(testMat15,1,1,2.0f);
  setCell(testMat15,1,2,7.0f);
  
  setCell(testMat15,2,0,0.0f);
  setCell(testMat15,2,1,6.0f);
  setCell(testMat15,2,2,-3.0f);

  matrix* testMat16 = createMatrix(2,2);
  setCell(testMat16,0,0,-3.0f);
  setCell(testMat16,0,1,2.0f);
  setCell(testMat16,1,0,0.0f);
  setCell(testMat16,1,1,6.0f);

  assert(matrixEquals(testMat16,subMatrix(testMat15,0,2)));
  
  matrix* testMat17 = createMatrix(4,4);
  setCell(testMat17,0,0,-6.0f);
  setCell(testMat17,0,1,1.0f);
  setCell(testMat17,0,2,1.0f);
  setCell(testMat17,0,3,6.0f);

  setCell(testMat17,1,0,-8.0f);
  setCell(testMat17,1,1,5.0f);
  setCell(testMat17,1,2,8.0f);
  setCell(testMat17,1,3,6.0f);

  setCell(testMat17,2,0,-1.0f);
  setCell(testMat17,2,1,0.0f);
  setCell(testMat17,2,2,8.0f);
  setCell(testMat17,2,3,2.0f);

  setCell(testMat17,3,0,-7.0f);
  setCell(testMat17,3,1,1.0f);
  setCell(testMat17,3,2,-1.0f);
  setCell(testMat17,3,3,1.0f);

  matrix* testMat18 = createMatrix(3,3);
  setCell(testMat18,0,0,-6.0f);
  setCell(testMat18,0,1,1.0f);
  setCell(testMat18,0,2,6.0f);

  setCell(testMat18,1,0,-8.0f);
  setCell(testMat18,1,1,8.0f);
  setCell(testMat18,1,2,6.0f);

  setCell(testMat18,2,0,-7.0f);
  setCell(testMat18,2,1,-1.0f);
  setCell(testMat18,2,2,1.0f);

  assert(matrixEquals(testMat18,subMatrix(testMat17,2,1)));

  matrix* testMat19 = createMatrix(3,3);
  setCell(testMat19,0,0,3.0f);
  setCell(testMat19,0,1,5.0f);
  setCell(testMat19,0,2,0.0f);

  setCell(testMat19,1,0,2.0f);
  setCell(testMat19,1,1,-1.0f);
  setCell(testMat19,1,2,-7.0f);

  setCell(testMat19,2,0,6.0f);
  setCell(testMat19,2,1,-1.0f);
  setCell(testMat19,2,2,5.0f);

  assert(matrixMinors(testMat19,1,0) == 25.0f);

  matrix* testMat20 = createMatrix(3,3);
  setCell(testMat20,0,0,3.0f);
  setCell(testMat20,0,1,5.0f);
  setCell(testMat20,0,2,0.0f);

  setCell(testMat20,1,0,2.0f);
  setCell(testMat20,1,1,-1.0f);
  setCell(testMat20,1,2,-7.0f);

  setCell(testMat20,2,0,6.0f);
  setCell(testMat20,2,1,-1.0f);
  setCell(testMat20,2,2,5.0f);

  assert(matrixCofactor(testMat20,0,0) == -12.0f);
  assert(matrixCofactor(testMat20,1,0) == -25.0f);

  //Matrix determinant
  matrix* testMat21 = createMatrix(3,3);
  setCell(testMat21,0,0,1.0f);
  setCell(testMat21,0,1,2.0f);
  setCell(testMat21,0,2,6.0f);

  setCell(testMat21,1,0,-5.0f);
  setCell(testMat21,1,1,8.0f);
  setCell(testMat21,1,2,-4.0f);

  setCell(testMat21,2,0,2.0f);
  setCell(testMat21,2,1,6.0f);
  setCell(testMat21,2,2,4.0f);

  assert(matrixCofactor(testMat21,0,0) == 56);
  assert(matrixCofactor(testMat21,0,1) == 12);
  assert(matrixCofactor(testMat21,0,2) == -46);
  assert(matrixDeterminant(testMat21) == -196);
  
  return 1; 
}
