#include "disk.h"

/*!
 * \class Disk disk.h
 * \brief Class which can be used to create a disk mesh
 */

/*!
 * \brief Create a disk mathematic object
 * \param _radius Radius of the disk
 * \param _height Normal of the disk
 * \param _center Center of the disk
 */

Disk::Disk(float _radius, Vector _Up, Vector _Center)
{
    radius = _radius;
    Up = _Up;
    Center = _Center;
}

Disk::~Disk()
{

}
