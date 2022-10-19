#ifndef MATRIX_H
#define MATRIX_H

#include "mathematics.h"

class matrix
{
public:
    matrix();
    float MatrixTab[3][3];
    void IdentMatrix();
    void Homothetie(matrix m);
    void RotationAxeX(matrix m, double angle);
    void RotationAxeY(matrix m, double angle);
    void RotationAxeZ(matrix m, double angle);
    void Translation(matrix m, float x, float y, float z);
    matrix Transpo(matrix m);
    void Inverse(matrix m);
    int determinant(matrix m);
};

#endif // MATRIX_H
