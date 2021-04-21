#ifndef RAY_H_
#define RAY_H_
#include "vector.h"
#include "boundary.h"
#include <SDL2/SDL.h>

typedef struct _Ray
{
    Vector pos;
    Vector dir;
} Ray;

extern Vector* ray_getPos(const Ray* ray);
extern Vector* ray_getDir(const Ray* ray);

extern Ray* ray_set(Ray* ray, const Vector pos, const double angle);
extern void ray_setPos(Ray* ray, const Vector pos);
extern void ray_setAngle(Ray* ray, const double angle);
extern Ray* ray_create(const Vector pos, const double angle);

extern void ray_draw(const Ray* ray, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
extern Vector* ray_cast(const Ray* ray, const Boundary* wall);

#endif /* RAY */
