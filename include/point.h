#ifndef POINT_H_
#define POINT_H_

typedef struct _Point
{
    float x;
    float y;
} Point;

extern float point_getX(const Point* point);
extern float point_getY(const Point* point);
extern Point* point_set(Point* point, const float x, const float y);
extern Point* point_create(const float x, const float y);

#endif /* POINT */
