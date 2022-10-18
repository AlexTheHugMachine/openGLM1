#ifndef CYLINDER_H
#define CYLINDER_H
#include "mathematics.h"

class Cylinder
{
public:
    Cylinder(float _radius, double _height, Vector _center);
    ~Cylinder();
    float radius;
    double height;
    Vector Center;
};

#endif // CYLINDER_H
