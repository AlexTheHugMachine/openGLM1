#include "matrix.h"

/*!
 * \class matrix matrix.h
 * \brief Class which can be used for multiples operation with matrixes 3x3
 */

/*!
 * \brief Create a matrix only with 0
 */
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

/*!
 * \brief Create an identity Matrix 3x3
 * \return An Identity Matrix 3x3
 */
matrix matrix::IdentMatrix()
{
    matrix m;
    m.MatrixTab[0][0] = 1;
    m.MatrixTab[1][1] = 1;
    m.MatrixTab[2][2] = 1;

    return m;
}

/*!
 * \brief Create the homothetie of a matrix in parameter
 * \param m Matrix which we want the homothetie
 * \return The matrix of which we want the homothetie
 */
matrix matrix::Homothetie(matrix m)
{
    m.MatrixTab[1][0] = 0;
    m.MatrixTab[2][0] = 0;
    m.MatrixTab[0][1] = 0;
    m.MatrixTab[2][1] = 0;
    m.MatrixTab[0][2] = 0;
    m.MatrixTab[1][2] = 0;

    return m;
}

/*!
 * \brief Applies a rotation on the x axis to the matrix passed as a parameter
 * \param m Matrix to which we want to apply a rotation
 * \param angle Angle in degrees
 * \return The matrix with x axis rotation applied
 */
matrix matrix::RotationAxeX(matrix m, double angle)
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
    return m;
}

/*!
 * \brief Applies a rotation on the y axis to the matrix passed as a parameter
 * \param m Matrix to which we want to apply a rotation
 * \param angle Angle in degrees
 * \return The matrix with y axis rotation applied
 */
matrix matrix::RotationAxeY(matrix m, double angle)
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
    return m;
}

/*!
 * \brief Applies a rotation on the z axis to the matrix passed as a parameter
 * \param m Matrix to which we want to apply a rotation
 * \param angle Angle in degrees
 * \return The matrix with z axis rotation applied
 */
matrix matrix::RotationAxeZ(matrix m, double angle)
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
    return m;
}

/*!
 * \brief Create the Transposed matrix of a matrix passed as a parameter
 * \param m Matrix whose transpose we want to calculate
 * \return the transposed matrix
 */
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

/*!
 * \brief Create the Inverse matrix of a matrix passed as a parameter
 * \param m Matrix whose inverse we want to calculate
 * \return the Inversed matrix
 */
matrix matrix::Inverse(matrix m)
{
    matrix TranspoMatrix;
    TranspoMatrix.Transpo(TranspoMatrix);

    int determinant1;
}
