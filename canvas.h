#ifndef CANVAS_H
#define CANVAS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
typedef struct{
  float r;
  float g;
  float b;

}colour;

typedef struct {
  int height;
  int width;
  colour * canv[] ;
  
}canvas; 


canvas * createCanvas(int width, int height);

void freeCanvas(canvas * canv); 

colour* createColour(float r, float g, float b);

colour* addColour(colour* x, colour*y );

colour* subColour(colour* x, colour*y );

colour* scalarMultiplyColour(float s, colour* x); 

colour* multiplyColour( colour* x, colour*y );

void writePixel(canvas* canv, int x,  int y, colour * pix); 

char* canvasToPpm(canvas* saveCanv);

int test_Canvas();

#endif //CANVAS_H
