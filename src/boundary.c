#include "boundary.h"
#include <stdio.h>
#include <stdlib.h>

Point* boundary_getA(const Boundary* boundary){
    Point* point = malloc(sizeof(Point));
    point = &boundary->a;
    return point;
}

Point* boundary_getB(const Boundary* boundary){
    Point* point = malloc(sizeof(Point));
    point = &boundary->b;
    return point;
}

Boundary* boundary_set(Boundary* boundary, const Point a, const Point b){
    boundary->a = a;
    boundary->b = b;
    return boundary;
}

Boundary* boundary_create(const Point a, const Point b){
    Boundary* boundary = malloc(sizeof(Boundary));
    return boundary_set(boundary, a, b);
}

void boundary_draw(const Boundary* boundary, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    int a_x = point_getX(boundary_getA(boundary));
    int a_y = point_getY(boundary_getA(boundary));
    int b_x = point_getX(boundary_getB(boundary));
    int b_y = point_getY(boundary_getB(boundary));

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, a_x, a_y, b_x, b_y);
}
