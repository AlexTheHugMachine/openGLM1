#ifndef CONE_H
#define CONE_H

#include "mathematics.h"

class Cone
{
public:
    Cone(float _radius, double _height, Vector _center);
    ~Cone();
    float radius;
    double height;
    Vector center;
};

#endif // CONE_H
