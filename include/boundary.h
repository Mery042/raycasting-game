#ifndef BOUNDARY_H_
#define BOUNDARY_H_
#include "vector.h"
#include <SDL2/SDL.h>

typedef struct _Boundary
{
    Vector a;
    Vector b;
} Boundary;

extern Vector* boundary_getA(const Boundary* boundary);
extern Vector* boundary_getB(const Boundary* boundary);

extern Boundary* boundary_set(Boundary* boundary, const Vector a, const Vector b);
extern Boundary* boundary_create(const Vector a, const Vector b);

extern void boundary_draw(const Boundary* boundary, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);


#endif /* BOUNDARY */
