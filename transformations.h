#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrix.h"

extern void mygl_scale(Matrix *m, float sx, float sy, float sz);
extern void mygl_translate(Matrix *m, float dx, float dy, float dz);
extern void mygl_rotate(Matrix *m, float ang, int x, int y, int z);
extern void mygl_shear_x(Matrix *m, float a, float b);
extern void mygl_shear_y(Matrix *m, float a, float b);
extern void mygl_shear_z(Matrix *m, float a, float b);

#endif
