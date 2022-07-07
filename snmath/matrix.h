#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>

    class Matrix4;

    class Matrix
    {
        public:
            int n;
            int m;
            std::vector<float> array;

            Matrix();
            Matrix(int n, int m);
            Matrix(const Matrix& matrix);
            Matrix(const Matrix4& matrix4);
            ~Matrix();

            float& accessor(int i, int j);
            float getDeterminant();
            float getDeterminant_1x1();
            float getDeterminant_2x2();
            float getDeterminant_3x3();
            float getDeterminant_4x4();
            float getDeterminant_NxN();
            float getMinor(int n, int m);
            float getCofactor(int n, int m);

            static Matrix identity(int m);
            static Matrix zero(int n, int m);

            void transpose();
            void display();

            Matrix getComatrix();
            Matrix getAdj();
            Matrix getReverseMatrix();
            Matrix resolveSystem(Matrix& matProduct);
            
            bool isMatrixReversable();
            bool isMatrixOrthogonal();

            Matrix operator+(const Matrix& mat);
            Matrix operator-(const Matrix& mat);
            Matrix operator*(Matrix& mat);
            bool   operator==(Matrix mat);
    };

    Matrix getSubMatrix(Matrix& matrix, int excludedLineIndex, int excludedColumnIndex);

    
#endif