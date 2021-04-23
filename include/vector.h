#ifndef VECTOR_H_
#define VECTOR_H_
#include <math.h>
#define DEG2RAD(a) ((a) * (M_PI / 180.0))

struct _Vector;
typedef struct _Vector Vector;

extern float vector_getX(const Vector* self);
extern float vector_getY(const Vector* self);
extern double vector_getHeading(const Vector* self);

extern void vector_init(Vector* self, float x, float y);
extern Vector* vector_create(float x, float y);

extern Vector* vector_fromAngle(double angle);
extern double vector_toAngle(Vector* self);

extern void vector_normalize(Vector* self);
extern void vector_add(Vector* self, Vector* k);
extern void vector_setMag(Vector* self, float mag);

extern float vector_distance(Vector* a, Vector* b);

#endif /* VECTOR */
