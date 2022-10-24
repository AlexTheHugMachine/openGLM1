#ifndef MATRIX_H
#define MATRIX_H

#include "mathematics.h"

class matrix
{
public:
    matrix();
    float MatrixTab[3][3];
    matrix IdentMatrix();
    matrix Homothetie();
    matrix RotationAxeX(double angle);
    matrix RotationAxeY(double angle);
    matrix RotationAxeZ(double angle);
    matrix Transpo();
    matrix Inverse();
    matrix constructMatrixDet();
    int detSusMatrix(int indexI, int indexT);
    int determinant();
    matrix operator+(matrix m2);
    matrix operator*(matrix m2);
    matrix operator*(float x);
};

#endif // MATRIX_H
