#include "cylinder.h"

/*!
 * \class Cylinder cylinder.h
 * \brief Class which can be used to create a cylinder mesh
 */

/*!
 * \brief Create a cylinder mathematic object
 * \param _radius Radius of the cylinder
 * \param _height Height of the cylinder
 * \param _center Center of the cylinder
 */

Cylinder::Cylinder(float _radius, double _height, Vector _center) {
    radius = _radius;
    height = _height;
    Center = _center;
};

Cylinder::~Cylinder()
{

}
