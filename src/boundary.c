#include "boundary.h"
#include <stdio.h>
#include <stdlib.h>

struct _Boundary
{
    Vector* a;
    Vector* b;
};

Vector* boundary_getA(const Boundary* self){
    return self->a;
}

Vector* boundary_getB(const Boundary* self){
    return self->b;
}

void boundary_init(Boundary* self, Vector* a, Vector* b){
    self->a = a;
    self->b = b;
}

Boundary* boundary_create(Vector* a, Vector* b){
    Boundary* result = (Boundary*) malloc(sizeof(Boundary));
    boundary_init(result, a, b);
    return result;
}

void boundary_draw(Boundary* self, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    float a_x = vector_getX(self->a);
    float a_y = vector_getY(self->a);
    float b_x = vector_getX(self->b);
    float b_y = vector_getY(self->b);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, a_x, a_y, b_x, b_y);
}
