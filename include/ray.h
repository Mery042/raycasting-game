#ifndef RAY_H_
#define RAY_H_
#include "vector.h"
#include "boundary.h"
#include <SDL2/SDL.h>

struct _Ray;
typedef struct _Ray Ray;

extern Vector* ray_getPos(const Ray* self);
extern Vector* ray_getDir(const Ray* self);

extern void ray_init(Ray* self, Vector* pos, double angle);
extern void ray_setPos(Ray* self, Vector* pos);
extern void ray_setAngle(Ray* self, double angle);
extern Ray* ray_create(Vector* pos, double angle);

extern void ray_draw(Ray* self, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
extern Vector* ray_cast(Ray* self, Boundary* wall);

#endif /* RAY */
