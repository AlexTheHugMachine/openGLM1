#ifndef CYLINDER_H
#define CYLINDER_H
#include "mathematics.h"

class Cylinder
{
    Cylinder(float _radius, Vector _center);
    ~Cylinder();
    float radius;
    Vector center;
};

#endif // CYLINDER_H
