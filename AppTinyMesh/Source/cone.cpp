#include "cone.h"

/*!
 * \class Cone cone.h
 * \brief Class which can be used to create a cone mesh
 */

/*!
 * \brief Create a cone mathematic object
 * \param _radius Radius of the cone
 * \param _height Height of the cone
 * \param _center Center of the cone
 */
Cone::Cone(float _radius, double _height, Vector _center)
{
    radius = _radius;
    height = _height;
    Center = _center;
}

Cone::~Cone()
{

}
