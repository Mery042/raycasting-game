#include "vector.h"
#include <math.h>
#include <stdlib.h>

struct _Vector
{
    float x;
    float y;
};

float vector_getX(const Vector* self){
    return self->x;
}

float vector_getY(const Vector* self){
    return self->y;
}

double vector_getHeading(const Vector* self){
    return atan2(self->y, self->x);
}

void vector_init(Vector* self, float x, float y){
    self->x = x;
    self->y = y;
}

Vector* vector_create(float x, float y){
    Vector* result = (Vector*) malloc(sizeof(Vector));
    vector_init(result, x, y);
    return result;
}

Vector* vector_fromAngle(double angle){
    Vector* result = (Vector*) malloc(sizeof(Vector));
    vector_init(result, cos(angle), sin(angle));
    return result;
}

double vector_toAngle(Vector* self){
    return atan2(self->y, self->x);
}

void vector_normalize(Vector* self){
    float w = sqrt(self->x * self->x + self->y * self->y);
    if(w != 0){
        self->x *= 1/w;
        self->y *= 1/w;
    }
}

void vector_add(Vector* self, Vector* k){
    self->x += vector_getX(k);
    self->y += vector_getY(k);
}

void vector_setMag(Vector* self, float mag){
    vector_normalize(self);
    self->x *= mag;
    self->y *= mag;
}

float vector_distance(Vector* a, Vector* b){
    return sqrt(pow(vector_getX(a) - vector_getX(b), 2) + pow(vector_getY(a) - vector_getY(b), 2));
}

