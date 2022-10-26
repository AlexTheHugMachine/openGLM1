#ifndef MATRIX_H
#define MATRIX_H

#include "mathematics.h"

class matrix
{
public:
    matrix();
    matrix(float aa, float ab, float ac, float ba, float bb, float bc, float ca, float cb, float cc);
    float MatrixTab[3][3];
    matrix IdentMatrix();
    matrix Homothetie();
    void RotationAxeX(int angle);
    void RotationAxeY(int angle);
    void RotationAxeZ(int angle);
    matrix Transpo();
    matrix Inverse();
    matrix constructMatrixDet();
    int detSusMatrix(int indexI, int indexT);
    int determinant();
    matrix operator+(matrix m2);
    matrix operator*(matrix m2);
    matrix operator*(float x);
    matrix operator*(Vector v);
};

#endif // MATRIX_H
