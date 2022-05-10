#include "projectile.h"

void tick(struct environment * env , struct projectile * proj){
  proj->position = add(proj->position,proj->velocity);
  proj->velocity = add(proj->velocity, add(env->gravity,env->wind));
  
}


int main(int argc, char * argv[]){
    struct environment *env;
    env = malloc(sizeof(struct environment));
    env->gravity = vector(0.0f,-0.1f,0.0f);
    env->wind = vector(-0.01f,0.0f,0.0f);

    struct projectile *proj;
    proj = malloc(sizeof(struct projectile));
    proj->position = point(0.0f,1.0f,0.0f);
    proj->velocity = normalize(vector(1.0f,1.0f,0.0f));

    while(proj->position->y > 0){
      tick(env, proj);
      printTuple(proj->position);

    }
    free(env);
    free(proj);
}
