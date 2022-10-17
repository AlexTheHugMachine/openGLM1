#ifndef DISK_H
#define DISK_H

#include "mathematics.h"

class Disk
{
public :
    Disk(float _radius, Vector _Up, Vector _Center);
    ~Disk();
    float radius;
    Vector Up;
    Vector Center;
};

#endif // DISK_H
