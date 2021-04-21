#include "ray.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vector* ray_getPos(const Ray* ray){
    Vector* vector = malloc(sizeof(Vector));
    vector = &ray->pos;
    return vector;
}

Vector* ray_getDir(const Ray* ray){
    Vector* vector = malloc(sizeof(Vector));
    vector = &ray->dir;
    return vector;
}

Ray* ray_set(Ray* ray, const Vector pos, const double angle){
    ray->pos = pos;
    ray->dir = *vector_set(ray_getDir(ray), cos(angle), sin(angle));
    return ray;
}

void ray_setPos(Ray* ray, const Vector pos){
    ray->pos = pos;
}

void ray_setAngle(Ray* ray, const double angle){
    ray->dir = *vector_set(ray_getDir(ray), cos(angle), sin(angle));
}

Ray* ray_create(const Vector pos, const double angle){
    Ray* ray = malloc(sizeof(Ray));
    return ray_set(ray, pos, angle);
}

void ray_draw(const Ray* ray, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    float pos_x = ray->pos.x;
    float pos_y = ray->pos.y;
    float dir_x = ray->dir.x;
    float dir_y = ray->dir.y;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, pos_x, pos_y, pos_x + dir_x * 10, pos_y + dir_y * 10);
}

Vector* ray_cast(const Ray* ray, const Boundary* wall){
    const float x1 = vector_getX(boundary_getA(wall));
    const float y1 = vector_getY(boundary_getA(wall));
    const float x2 = vector_getX(boundary_getB(wall));
    const float y2 = vector_getY(boundary_getB(wall));

    const float x3 = ray->pos.x;
    const float y3 = ray->pos.y;
    const float x4 = ray->pos.x + ray->dir.x;
    const float y4 = ray->pos.y + ray->dir.y;

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
