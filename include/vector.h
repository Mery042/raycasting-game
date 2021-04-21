#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct _Vector
{
    float x;
    float y;
} Vector;

extern float vector_getX(const Vector* vector);
extern float vector_getY(const Vector* vector);
extern Vector* vector_set(Vector* vector, const float x, const float y);
extern Vector* vector_create(const float x, const float y);

extern void vector_normalize(Vector* vector);

extern float vector_distance(const Vector* a, const Vector* b);

#endif /* VECTOR */
