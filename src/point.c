#include "point.h"
#include <stdlib.h>

float point_getX(const Point* point){
    return point->x;
}

float point_getY(const Point* point){
    return point->y;
}

Point* point_set(Point* point, const float x, const float y){
    point->x = x;
    point->y = y;
    return point;
}

Point* point_create(const float x, const float y){
    Point* point = malloc(sizeof(Point));
    return point_set(point, x, y);
}