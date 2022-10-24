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
 * \brief Create the homothetie of a matrix
 * \return The matrix of which we want the homothetie
 */
matrix matrix::Homothetie()
{
    matrix m;
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            m.MatrixTab[i][j] = MatrixTab[i][j];
        }
    }

    m.MatrixTab[1][0] = 0;
    m.MatrixTab[2][0] = 0;
    m.MatrixTab[0][1] = 0;
    m.MatrixTab[2][1] = 0;
    m.MatrixTab[0][2] = 0;
    m.MatrixTab[1][2] = 0;

    return m;
}

/*!
 * \brief Applies a rotation on the x axis
 * \param angle Angle in degrees
 * \return The matrix with x axis rotation applied
 */
matrix matrix::RotationAxeX(double angle)
{
    double AngleRadians = Math::DegreeToRadian(angle);

    matrix m;
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
                m.MatrixTab[i][j] = MatrixTab[i][j] * MatriceX.MatrixTab[i][j];
            }
        }
    return m;
}

/*!
 * \brief Applies a rotation on the y axis
 * \param angle Angle in degrees
 * \return The matrix with y axis rotation applied
 */
matrix matrix::RotationAxeY(double angle)
{
    double AngleRadians = Math::DegreeToRadian(angle);

    matrix m;
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
                m.MatrixTab[i][j] = MatrixTab[i][j] * MatriceY.MatrixTab[i][j];
            }
        }
    return m;
}

/*!
 * \brief Applies a rotation on the z axis
 * \param angle Angle in degrees
 * \return The matrix with z axis rotation applied
 */
matrix matrix::RotationAxeZ(double angle)
{
    double AngleRadians = Math::DegreeToRadian(angle);

    matrix m;
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
                m.MatrixTab[i][j] = MatrixTab[i][j] * MatriceZ.MatrixTab[i][j];
            }
        }
    return m;
}

/*!
 * \brief Create the Transposed matrix of a matrix
 * \return the transposed matrix
 */
matrix matrix::Transpo()
{
    matrix m;
    matrix TranspoMatrix;
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            TranspoMatrix.MatrixTab[i][j] = MatrixTab[i][j];
            m.MatrixTab[i][j] = MatrixTab[i][j];
        }
    }

    m.MatrixTab[1][0] = TranspoMatrix.MatrixTab[0][1];
    m.MatrixTab[0][1] = TranspoMatrix.MatrixTab[1][0];
    m.MatrixTab[2][0] = TranspoMatrix.MatrixTab[0][2];
    m.MatrixTab[0][2] = TranspoMatrix.MatrixTab[2][0];
    m.MatrixTab[2][1] = TranspoMatrix.MatrixTab[1][2];
    m.MatrixTab[1][2] = TranspoMatrix.MatrixTab[2][1];

    return m;
}

/*!
 * \brief Calculate the determinant of the sus matrix
 * \param indexI
 * \param indexT
 * \return
 */
int matrix::detSusMatrix(int indexI, int indexT)
{
    int susMatrix[4];
    int cpt = 0;
    for(int i=0; i<3; i++)
    {
        for(int t=0; t<3; t++)
        {
            if(i != indexI && t != indexT)
            {
                susMatrix[cpt] = MatrixTab[i][t];
                cpt++;
            }
        }
    }
    return susMatrix[0] * susMatrix[3] - susMatrix[1] * susMatrix[2];
}

int matrix::determinant()
{
    int res=0;
    bool b = true;
    for(int t=0; t<3; t++)
    {
        if(b)
        {
            res += MatrixTab[0][t] * detSusMatrix(0, t);
            b = false;
        }
        else
        {
            res -= MatrixTab[0][t] * detSusMatrix(0, t);
            b = true;
        }
    }
    return res;
}

matrix matrix::constructMatrixDet()
{
    matrix matrixDet;
    bool b = true;
    for(int i = 0; i<3; i++)
    {
        for(int t = 0; t<3; t++)
        {
            if(b)
            {
                matrixDet.MatrixTab[i][t] = detSusMatrix(i, t);
                b = false;
            }
            else
            {
                matrixDet.MatrixTab[i][t] = -detSusMatrix(i, t);
                b = true;
            }
        }
    }
    return matrixDet;
}

/*!
 * \brief Create the Inverse matrix of a matrix passed as a parameter
 * \param m Matrix whose inverse we want to calculate
 * \return the Inversed matrix
 */
matrix matrix::Inverse()
{
    matrix matrixDet = constructMatrixDet();
    return matrixDet.Transpo();
}

matrix matrix::operator+(matrix m2)
{
    matrix res;
    for(int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            res.MatrixTab[i][j] = MatrixTab[i][j] + m2.MatrixTab[i][j];
        }
    }
    return res;
}

matrix matrix::operator*(matrix m2)
{
    matrix res;
    for(int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            res.MatrixTab[i][j] = (MatrixTab[i][0] * m2.MatrixTab[0][j]) + (MatrixTab[i][1] * m2.MatrixTab[1][j]) + (MatrixTab[i][2] * m2.MatrixTab[2][j]);
        }
    }
    return res;
}

matrix matrix::operator*(float x)
{
    matrix res;
    for(int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            res.MatrixTab[i][j] = MatrixTab[i][j] * x;
        }
    }
    return res;
}
