#include <iostream>
#include <assert.h>
#include <math.h>
#include "matrix.h"
#include "matrix4.h"
#include <vector>
#include <assert.h>

Matrix::Matrix()
{

}

Matrix::Matrix(int n, int m)
{
    array.resize(n * m, 0);
    this->n = n;
    this->m = m;
}

Matrix::Matrix(const Matrix4& matrix4)
{
    array = matrix4.array;
    this->n = matrix4.n;
    this->m = matrix4.m;
}

Matrix::Matrix(const Matrix& matrix)
{
    array = matrix.array;
    this->n = matrix.n;
    this->m = matrix.m;
}

Matrix::~Matrix()
{

}

float& Matrix::accessor(int i, int j)
{
    return array[(i * this->m) + j];
}

Matrix Matrix::identity(int m)
{
    assert(m > 0);
    Matrix matIdentity(m, m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (i == j)
            {
                matIdentity.accessor(i, j) = 1;
            }
            else
            {
                matIdentity.accessor(i, j) = 0;
            }
        }
    }
    
    return matIdentity;
}


Matrix Matrix::zero(int n, int m)
{
    assert(n > 0 && m > 0);
    Matrix matZero(n, m);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            matZero.accessor(i, j) = 0;
        }
    }

    return matZero;
}


void Matrix::transpose()
{
    Matrix transposedMatrix(this->m, this->n);
    
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < m; ++i)
        {
            transposedMatrix.accessor(i, j) = this->accessor(j, i);
        }
    }
    this->n = transposedMatrix.n;
    this->m = transposedMatrix.m;

    for (int i = 0; i < n * m; ++i)
    {
        this->array[i] = transposedMatrix.array[i];
    }
}

Matrix Matrix::operator+(Matrix const& mat)
{
    assert(mat.n == this->n);
    assert(mat.m == this->m);

    Matrix newMatrix(mat.n, mat.m);

    for (int i = 0; i < mat.n * mat.m; ++i)
    {
        newMatrix.array[i] = mat.array[i] + array[i];
    }

    return newMatrix;
}

Matrix Matrix::operator-(Matrix const& mat)
{
    assert(mat.n == this->n);
    assert(mat.m == this->m);
    
    Matrix newMatrix(mat.n, mat.m);

    for (int i = 0; i < mat.n * mat.m; ++i)
    {
        newMatrix.array[i] = mat.array[i] - array[i];
    }

    return newMatrix;
}

Matrix Matrix::operator*(Matrix& mat)
{
    assert(this->m == mat.n);

    Matrix newMatrix(this->n, mat.m);

    for (int i = 0; i < newMatrix.n; ++i)
    {
        for (int j = 0; j < newMatrix.m; ++j)
        {
            float newData = 0;

            // y < this->m  OR y < a.n
            for (int y = 0; y < this->m; ++y)
            {
                newData += (this->accessor(i, y) * mat.accessor(y, j));
            }
            newMatrix.accessor(i, j) = newData;
        }
    }

    return newMatrix;
}

float Matrix::getDeterminant_1x1()
{
    return accessor(0,0);
}

float Matrix::getDeterminant_2x2()
{
    return accessor(0,0) * accessor(1, 1) - accessor(0,1) * accessor(1, 0);
}

float Matrix::getDeterminant_3x3()
{
    float determinant = 0;
    for (int i = 0; i < 3; ++i)
    {
        Matrix subMatrix = getSubMatrix(*this, 0, i);
        float determinant2x2 = array[i] * subMatrix.getDeterminant_2x2();
        if (i == 1)
            determinant2x2 *= -1;

        determinant += determinant2x2;
    }
    
    return determinant;
}

float Matrix::getDeterminant_4x4()
{
    float determinant = 0;
    for (int i = 0; i < 4; ++i)
    {
        Matrix subMatrix = getSubMatrix(*this, 0, i);
        float determinant3x3 = array[i] * subMatrix.getDeterminant_3x3();
        if (i == 1 || i == 3)
            determinant3x3 *= -1;

        determinant += determinant3x3;
    }

    return determinant;
}

float Matrix::getDeterminant_NxN()
{
    assert(n == m && n > 0 && m > 0);
    if (n == 2)
    {
        return getDeterminant_2x2();
    }
    float determinant = 0;
    for (int i = 0; i < n; ++i)
    {
        Matrix subMatrix = getSubMatrix(*this, 0, i);
        float determinantStock = array[i];
        if (subMatrix.n == 2)
        {
            determinantStock *= subMatrix.getDeterminant_2x2();
        }
        else
        {
            determinantStock *= subMatrix.getDeterminant_NxN();
        }
        if (i % 2 == 1)
            determinantStock *= -1;

        determinant += determinantStock;
    }

    return determinant;
}



Matrix getSubMatrix(Matrix& matrix, int excludedLineIndex, int excludedColumnIndex)
{
    assert(matrix.n > 1 && matrix.m > 1);

    Matrix subMatrix(matrix.n - 1, matrix.m - 1);

    int indexSubMatrix = 0;

    for (int i = 0; i < matrix.n; ++i)
    {
        for (int j = 0; j < matrix.m; ++j)
        {
            if (i != excludedLineIndex && j != excludedColumnIndex)
            {
                subMatrix.array[indexSubMatrix] = matrix.accessor(i, j);
                ++indexSubMatrix;
            }
        }
    }

    return subMatrix;
}

float Matrix::getMinor(int n, int m)
{
    Matrix subMatrix = getSubMatrix(*this, n, m);
    return subMatrix.getDeterminant_NxN();
}

float Matrix::getCofactor(int n, int m)
{
    return getMinor(n, m) * pow(-1, n + m);
}

Matrix Matrix::getComatrix()
{
    assert(n == m && n > 0 && m > 0);
    Matrix comatrix(n, m);

    for (int i = 0; i < comatrix.n; ++i)
    {
        for (int j = 0; j < comatrix.m; ++j)
        {
            comatrix.accessor(i ,j) = this->getCofactor(i, j);
        }
        std::cout << std::endl;
    }
    return comatrix;
}

Matrix Matrix::getAdj()
{
    assert(n == m && n > 0 && m > 0);
    Matrix adj = getComatrix();
    adj.transpose();

    return adj;
}

Matrix Matrix::getReverseMatrix()
{
    assert(n == m && n > 0 && m > 0);
    float determinant = getDeterminant_NxN();
    assert(determinant != 0);
    Matrix reverseMatrix = getAdj();

    for (int i = 0; i < n * m; ++i)
    {
        reverseMatrix.array[i] /= determinant;
    }

    return reverseMatrix;
}

bool Matrix::isMatrixReversable()
{
    if (this->getDeterminant_NxN() == 0)
        return false;
    else
        return true;
}

bool Matrix::isMatrixOrthogonal()
{
    if (n == m && n > 0 && m > 0 && this->isMatrixReversable())
    {
        Matrix matTransposed = *this;
        matTransposed.transpose();
        

        if (((matTransposed * *this) == (*this * matTransposed)) &&  (*this * matTransposed) == Matrix::identity(n) && (matTransposed * *this) == Matrix::identity(n))
            return true;
    }
    
    return false;
}



Matrix Matrix::resolveSystem(Matrix& matProduct)
{
    assert(matProduct.m == 1 && this->m == matProduct.n && this-> m == this->n);
    Matrix matReverse = getReverseMatrix();
    
    return *this * matProduct;
}

void Matrix::display()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cout << "|| " << accessor(i, j) << " ||";
        }
        std::cout << std::endl;
    }
}


bool Matrix::operator==(Matrix mat)
{
    assert(this->n == mat.n);
    assert(this->m == mat.m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (accessor(i, j) != mat.accessor(i, j))
                return false;
        }
    }

    return true;
}