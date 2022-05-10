// test runner for ray tracer challenge
#include <stdio.h>
#include "tuple.h"
#include "canvas.h"

int main(int argc, char *argv[]) {
  printf("running tests...\n");
  if(test_tuple()){ printf("Tuple tests passed\n");}
  if(test_Canvas()){ printf("Canvas tests Passed\n");}
}
