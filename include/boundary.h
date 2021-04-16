#ifndef BOUNDARY_H_
#define BOUNDARY_H_
#include "point.h"
#include <SDL2/SDL.h>

typedef struct _Boundary
{
    Point a;
    Point b;
} Boundary;

extern Point* boundary_getA(const Boundary* boundary);
extern Point* boundary_getB(const Boundary* boundary);

extern Boundary* boundary_set(Boundary* boundary, const Point a, const Point b);
extern Boundary* boundary_create(const Point a, const Point b);

extern void boundary_draw(const Boundary* boundary, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);


#endif /* BOUNDARY */
