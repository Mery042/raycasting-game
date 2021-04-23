#include "ray.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _Ray
{
    Vector* pos;
    Vector* dir;
};

Vector* ray_getPos(const Ray* self){
    return self->pos;
}

Vector* ray_getDir(const Ray* self){
    return self->dir;
}

void ray_init(Ray* self, Vector* pos, double angle){
    self->pos = pos;
    self->dir = vector_fromAngle(angle);
}

void ray_setPos(Ray* self, Vector* pos){
    self->pos = pos;
}

void ray_setAngle(Ray* self, double angle){
    self->dir = vector_fromAngle(angle);
}

Ray* ray_create(Vector* pos, double angle){
    Ray* result = (Ray*) malloc(sizeof(Ray));
    ray_init(result, pos, angle);
    return result;
}

void ray_draw(Ray* self, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    float pos_x = vector_getX(self->pos);
    float pos_y = vector_getY(self->pos);
    float dir_x = vector_getX(self->dir);
    float dir_y = vector_getY(self->dir);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, pos_x, pos_y, pos_x + dir_x * 10, pos_y + dir_y * 10);
}

Vector* ray_cast(Ray* self, Boundary* wall){
    const float x1 = vector_getX(boundary_getA(wall));
    const float y1 = vector_getY(boundary_getA(wall));
    const float x2 = vector_getX(boundary_getB(wall));
    const float y2 = vector_getY(boundary_getB(wall));

    const float x3 = vector_getX(self->pos);
    const float y3 = vector_getY(self->pos);
    const float x4 = vector_getX(self->pos) + vector_getX(self->dir);
    const float y4 = vector_getY(self->pos) + vector_getY(self->dir);

    const float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    if(den == 0){
        return NULL;
    }

    const float t = ((x1-x3) * (y3-y4) - (y1-y3) * (x3-x4)) / den;
    const float u = -((x1-x2) * (y1-y3) - (y1-y2) * (x1-x3)) / den;

    if(t > 0 && t < 1 && u > 0){
        Vector* pt = vector_create(x1 + t * (x2 - x1), y1 + t * (y2 - y1));
        return pt;
    } else {
        return NULL;
    }
}
