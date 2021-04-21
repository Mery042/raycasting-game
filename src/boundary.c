#include "boundary.h"
#include <stdio.h>
#include <stdlib.h>

Vector* boundary_getA(const Boundary* boundary){
    Vector* vector = malloc(sizeof(Vector));
    vector = &boundary->a;
    return vector;
}

Vector* boundary_getB(const Boundary* boundary){
    Vector* vector = malloc(sizeof(Vector));
    vector = &boundary->b;
    return vector;
}

Boundary* boundary_set(Boundary* boundary, const Vector a, const Vector b){
    boundary->a = a;
    boundary->b = b;
    return boundary;
}

Boundary* boundary_create(const Vector a, const Vector b){
    Boundary* boundary = malloc(sizeof(Boundary));
    return boundary_set(boundary, a, b);
}

void boundary_draw(const Boundary* boundary, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    float a_x = vector_getX(boundary_getA(boundary));
    float a_y = vector_getY(boundary_getA(boundary));
    float b_x = vector_getX(boundary_getB(boundary));
    float b_y = vector_getY(boundary_getB(boundary));

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, a_x, a_y, b_x, b_y);
}
