
#include "tuple.h"


struct projectile {

  struct tuple * position;
  struct tuple * velocity; 
};

struct environment{
  struct tuple * gravity;
  struct tuple * wind; 
};


void tick(struct environment * env , struct projectile * proj); 
