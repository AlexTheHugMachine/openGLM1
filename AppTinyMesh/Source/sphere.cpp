#include "sphere.h"

/*!
 * \class Sphere sphere.h
 * \brief Class which can be used to create a sphere mesh
 */

/*!
 * \brief Create a sphere mathematic object
 * \param _radius Radius of the sphere
 * \param _center Center of the sphere
 */

Sphere::Sphere(float _radius, Vector _center)
{
    radius = _radius;
    center = _center;
}

Sphere::~Sphere()
{

}
