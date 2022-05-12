#include "canvas.h"


colour* createColour(float r, float g, float b){
  colour *newCol;
  newCol = malloc(sizeof(colour));
  newCol->r = r;
  newCol->g = g;
  newCol->b = b;
  return  newCol; 
}

canvas * createCanvas(int width, int height){
  canvas *newCanvas = malloc(sizeof *newCanvas+sizeof*(newCanvas->canv)*width);
  newCanvas->height = height;
  newCanvas->width = width;
  for(int x=0;x<width;x++){
    newCanvas->canv[x] = malloc(sizeof*(newCanvas->canv[x])*height);
    for(int y=0; y<height; y++){
      newCanvas->canv[x][y].r = 0.0f;
      newCanvas->canv[x][y].g = 0.0f;
      newCanvas->canv[x][y].b = 0.0f;
    }}
  return newCanvas;
}

void freeCanvas(canvas* toFree){
  if(toFree){
    for(int e=0; e<toFree->width;e++)
      free(toFree->canv[e]);
  }
  free(toFree);
     
}

void writePixel(canvas * pixCanv, int x, int y, colour*pix){
  pixCanv->canv[x][y].r = pix->r;
  pixCanv->canv[x][y].g = pix->g;
  pixCanv->canv[x][y].b = pix->b;
  
}


char* canvasToPpm(canvas * ppmCanv){
  // calculate actual bytes based on height width etc 
  int buflen = (ppmCanv->height*ppmCanv->width)*13+16;
  char * retbuff  = (char*) malloc(sizeof(char)*buflen);
  printf("%d\n",buflen);
  char linebuff[13];
  int count = 0;
  
  snprintf(retbuff,buflen,"P3\n%d %d\n255\n",ppmCanv->width, ppmCanv->height);
  for(int x=0; x<ppmCanv->width; x++){
    for(int y=0; y<ppmCanv->height; y++){
      snprintf(linebuff,13,"%d %d %d ",
	       mapColour(ppmCanv->canv[x][y].r),
	       mapColour(ppmCanv->canv[x][y].g),
	       mapColour(ppmCanv->canv[x][y].b)
	      );
      strcat(retbuff,linebuff);
      if(y%3==0){
	strcat(retbuff,"\n");
        }
	
      
    }}
  strcat(retbuff,"\n");
  return(retbuff);
  
    
}

int mapColour(float num ){
  return (int)fmax(0,fmin(255,255*(num)));
}

colour* addColour(colour* x, colour*y){
  float r = x->r + y->r;
  float g = x->g + y->g;
  float b = x->b + y->b;
  
  return createColour(r,g,b);
}

colour* subColour(colour* x, colour*y ){
  float r = x->r - y->r;
  float g = x->g - y->g;
  float b = x->b - y->b;

  return createColour(r,g,b);
}

colour* scalarMultiplyColour(float s, colour*x){
   float r = x->r * s;
   float g = x->g * s;
   float b = x->b * s;

   return createColour(r,g,b);
}

colour* multiplyColour( colour* x, colour*y ){
   float r = x->r * y->r;
   float g = x->g * y->g;
   float b = x->b * y->b;

   return createColour(r,g,b);
}

int test_Canvas(){
  // test colour
  colour* newColour = createColour(-0.5f,0.4f,1.7f);
  assert(newColour->r == -0.5f);
  assert(newColour->g == 0.4f);
  assert(newColour->b == 1.7f);
  free(newColour);

  colour* c1 = createColour(0.5f,0.1f,0.75f);
  colour* c2 = createColour(0.5f,0.1f,0.25f);

  //test Add colour
  colour* addCol = addColour(c1,c2);
  assert(addCol->r == 1.0f);
  assert(addCol->g == 0.2f);
  assert(addCol->b == 1.0f);
  free(addCol);

  //test sub colour
  colour* subCol = subColour(c1,c2);
  assert(subCol->r == 0.0f);
  assert(subCol->g == 0.0f);
  assert(subCol->b == 0.5f);
  free(subCol);
  free(c1);
  free(c2);
  
  //test scalar multiply
  colour* m1 = createColour(0.2f,0.3f,0.4f);
  colour* mulCol = scalarMultiplyColour(2,m1);
  assert(mulCol->r == 0.4f);
  assert(mulCol->g == 0.6f);
  assert(mulCol->b == 0.8f);
  free(mulCol);
  free(m1);

  // test multiply
  colour* m2 = createColour(1.0f,0.2f,4.0f);
  colour* m3 = createColour(0.9f,1.0f,0.01f);
  colour* mulCol2 = multiplyColour(m2,m3);
  assert(mulCol2->r == 0.9f);
  assert(mulCol2->g == 0.2f);
  assert(mulCol2->b == 0.04f);
  free(mulCol2);
  free(m2);


  //create canvas
  canvas * testCanv = createCanvas(10,20);
  assert(testCanv->width == 10);
  assert(testCanv->height == 20);
  for(int x=0; x<10; x++){
    for(int y=0; y<20;y++){
      //fix this int means that it will always be true 
      //assert((int)testCanv->canv[x][y].r == 0);
      //assert((int)testCanv->canv[x][y].g == 0);
      //assert((int)testCanv->canv[x][y].b == 0);
          
      }
  }
  freeCanvas(testCanv);

  // set a pixel
  canvas * testPixCanv = createCanvas(10,20);
  colour * red = createColour(1,0,0);
  writePixel(testPixCanv, 2,3,red);
  assert(testPixCanv->canv[2][3].r == 1.0f);
  assert(testPixCanv->canv[2][3].g == 0.0f);
  assert(testPixCanv->canv[2][3].b == 0.0f);
  freeCanvas(testPixCanv);
  free(red);
  
  //build ppm header
  canvas * testPpmCanv = createCanvas(10,20);
  char* ppm = canvasToPpm(testPpmCanv);
  assert(strcmp(strtok(ppm,"\n"),"P3\n"));
  assert(strcmp(strtok(NULL,"\n"),"10 20\n"));
  assert(strcmp(strtok(NULL,"\n"),"255\n"));
  freeCanvas(testPpmCanv);
  free(ppm);

  //build ppm body 
  canvas * testPpmCanvPix = createCanvas(5,3);
  colour * c1pix = createColour(1.5f,0.0f,0.0f);
  colour * c2pix = createColour(0.0f,0.5f,0.0f);
  colour * c3pix = createColour(-0.5f,0.0f,1.0f);
  writePixel(testPpmCanvPix,0,0,c1pix);
  writePixel(testPpmCanvPix,2,1,c2pix);
  writePixel(testPpmCanvPix,4,2,c3pix);
  char* ppmPix = canvasToPpm(testPpmCanvPix);
  printf("%s\n",ppmPix);
  freeCanvas(testPpmCanvPix);
  free(ppmPix);
  		
  return 1;
}
