#ifndef MATRIX_H
#define MATRIX_H

#include "mathematics.h"

class matrix
{
public:
    matrix();
    float MatrixTab[3][3];
    matrix IdentMatrix();
    matrix Homothetie(matrix m);
    matrix RotationAxeX(matrix m, double angle);
    matrix RotationAxeY(matrix m, double angle);
    matrix RotationAxeZ(matrix m, double angle);
    matrix Translation(matrix m, float x, float y, float z);
    matrix Transpo(matrix m);
    matrix Inverse(matrix m);
    int determinant(matrix m);
};

#endif // MATRIX_H
