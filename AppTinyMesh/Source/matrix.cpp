#include "../Include/matrix.h"

matrix::matrix()
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; i<3; i++)
        {
            MatrixTab[i][j] = 0;
        }
    }
}

void matrix::IdentMatrix()
{
    MatrixTab[0][0] = 1;
    MatrixTab[1][1] = 1;
    MatrixTab[2][2] = 1;
}

void matrix::Homothetie(matrix m)
{
    m.MatrixTab[1][0] = 0;
    m.MatrixTab[2][0] = 0;
    m.MatrixTab[0][1] = 0;
    m.MatrixTab[2][1] = 0;
    m.MatrixTab[0][2] = 0;
    m.MatrixTab[1][2] = 0;
}

void matrix::RotationAxeX(matrix m, double angle)
{
    double AngleRadians = Math::DegreeToRadian(angle);

    matrix MatriceX;
    MatriceX.MatrixTab[0][0] = 1;
    MatriceX.MatrixTab[1][0] = 0;
    MatriceX.MatrixTab[2][0] = 0;
    MatriceX.MatrixTab[0][1] = 0;
    MatriceX.MatrixTab[0][2] = 0;

    MatriceX.MatrixTab[1][1] = cos(AngleRadians);
    MatriceX.MatrixTab[2][2] = cos(AngleRadians);

    MatriceX.MatrixTab[1][2] = sin(AngleRadians);
    MatriceX.MatrixTab[2][1] = -sin(AngleRadians);

    for (int i = 0; i<3; i++)
        {
            for (int j = 0; i<3; i++)
            {
                m.MatrixTab[i][j] = m.MatrixTab[i][j] * MatriceX.MatrixTab[i][j];
            }
        }
}

void matrix::RotationAxeY(matrix m, double angle)
{
    double AngleRadians = Math::DegreeToRadian(angle);

    matrix MatriceY;
    MatriceY.MatrixTab[0][0] = cos(AngleRadians);
    MatriceY.MatrixTab[2][2] = cos(AngleRadians);

    MatriceY.MatrixTab[2][0] = -sin(AngleRadians);
    MatriceY.MatrixTab[0][2] = sin(AngleRadians);

    MatriceY.MatrixTab[1][0] = 0;
    MatriceY.MatrixTab[0][1] = 0;
    MatriceY.MatrixTab[1][1] = 1;
    MatriceY.MatrixTab[2][1] = 0;
    MatriceY.MatrixTab[1][2] = 0;

    for (int i = 0; i<3; i++)
        {
            for (int j = 0; i<3; i++)
            {
                m.MatrixTab[i][j] = m.MatrixTab[i][j] * MatriceY.MatrixTab[i][j];
            }
        }
}

void matrix::RotationAxeZ(matrix m, double angle)
{
    double AngleRadians = Math::DegreeToRadian(angle);

    matrix MatriceZ;
    MatriceZ.MatrixTab[0][0] = cos(AngleRadians);
    MatriceZ.MatrixTab[1][1] = cos(AngleRadians);

    MatriceZ.MatrixTab[1][0] = -sin(AngleRadians);
    MatriceZ.MatrixTab[0][1] = sin(AngleRadians);

    MatriceZ.MatrixTab[2][2] = 1;
    MatriceZ.MatrixTab[0][2] = 0;
    MatriceZ.MatrixTab[1][2] = 0;
    MatriceZ.MatrixTab[2][1] = 0;
    MatriceZ.MatrixTab[2][0] = 0;

    for (int i = 0; i<3; i++)
        {
            for (int j = 0; i<3; i++)
            {
                m.MatrixTab[i][j] = m.MatrixTab[i][j] * MatriceZ.MatrixTab[i][j];
            }
        }
}

matrix matrix::Transpo(matrix m)
{
    matrix TranspoMatrix = m;

    m.MatrixTab[1][0] = TranspoMatrix.MatrixTab[0][1];
    m.MatrixTab[0][1] = TranspoMatrix.MatrixTab[1][0];
    m.MatrixTab[2][0] = TranspoMatrix.MatrixTab[0][2];
    m.MatrixTab[0][2] = TranspoMatrix.MatrixTab[2][0];
    m.MatrixTab[2][1] = TranspoMatrix.MatrixTab[1][2];
    m.MatrixTab[1][2] = TranspoMatrix.MatrixTab[2][1];

    return m;
}

int matrix::determinant(matrix m)
{
    int delta;
}

void matrix::Inverse(matrix m)
{
    matrix TranspoMatrix;
    TranspoMatrix = TranspoMatrix.Transpo(TranspoMatrix);

    int determinant1;
}
