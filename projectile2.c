#include "projectile2.h"

void tick(struct environment * env , struct projectile * proj, canvas* canv){
  colour * red = createColour(1.0f,0.0f,0.0f);
  proj->position = add(proj->position,proj->velocity);
  proj->velocity = add(proj->velocity, add(env->gravity,env->wind));
  if(canv->width >= proj->position->x && canv->height>= proj->position->y)
    writePixel(canv,(int)((canv->height-1)-proj->position->y),(int)proj->position->x,red);

 
  
}


int main(int argc, char * argv[]){
    struct environment *env;
    env = malloc(sizeof(struct environment));
    env->gravity = vector(0.0f,-0.01f,0.0f);
    env->wind = vector(0.0f,0.0f,0.0f);

    struct projectile *proj;
    proj = malloc(sizeof(struct projectile));
    proj->position = point(0.0f,1.0f,0.0f);
    proj->velocity = normalize(vector(10.0f,20.0f,0.0f));

    canvas* canv = createCanvas(200,200);

    while(proj->position->y > 0){
      tick(env, proj, canv);      //printTuple(proj->position);

    }
    printf("\n%s\n",canvasToPpm(canv));
    free(env);
    free(proj);
    //freeCanvas(canv);
}
