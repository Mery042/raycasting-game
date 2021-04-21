#include "vector.h"
#include <math.h>
#include <stdlib.h>

float vector_getX(const Vector* vector){
    return vector->x;
}

float vector_getY(const Vector* vector){
    return vector->y;
}

Vector* vector_set(Vector* vector, const float x, const float y){
    vector->x = x;
    vector->y = y;
    return vector;
}

Vector* vector_create(const float x, const float y){
    Vector* vector = malloc(sizeof(Vector));
    return vector_set(vector, x, y);
}

void vector_normalize(Vector* vector){
    float w = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= w;
    vector->y /= w;
}

float vector_distance(const Vector* a, const Vector* b){
    return sqrt(pow(vector_getX(a) - vector_getX(b), 2) + pow(vector_getY(a) - vector_getY(b), 2));
}