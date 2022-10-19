#ifndef TORE_H
#define TORE_H

#include "mathematics.h"

class Tore
{
public:
    Tore(float _radius, float _thickness);
    ~Tore();
    float radius;
    float thickness;
};

#endif // TORE_H
