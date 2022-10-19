#ifndef SPHERE_H
#define SPHERE_H

#include "mathematics.h"

class Sphere
{
public:
    Sphere(float _radius, Vector _center);
    ~Sphere();
    float radius;
    Vector center;
};

#endif // SPHERE_H
