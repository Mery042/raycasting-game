#ifndef BOUNDARY_H_
#define BOUNDARY_H_
#include "vector.h"
#include <SDL2/SDL.h>

struct _Boundary;
typedef struct _Boundary Boundary;


extern Vector* boundary_getA(const Boundary* self);
extern Vector* boundary_getB(const Boundary* self);

extern void boundary_init(Boundary* self, Vector* a, Vector* b);
extern Boundary* boundary_create(Vector* a, Vector* b);

extern void boundary_draw(Boundary* self, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);


#endif /* BOUNDARY */
