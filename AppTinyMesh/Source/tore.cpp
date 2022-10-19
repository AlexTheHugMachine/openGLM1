#include "tore.h"

/*!
 * \class Tore tore.h
 * \brief Class which can be used to create a torus mesh
 */

/*!
 * \brief Create a tore mathematic object
 * \param _radius Radius of the tore
 * \param _thickness Thickness of the tore
 */

Tore::Tore(float _radius, float _thickness)
{
    radius = _radius;
    thickness = _thickness;
}

Tore::~Tore()
{

}
