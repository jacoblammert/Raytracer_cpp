//
// Created by Jacob on 15.04.2020.
//

/**/
#include <iostream>
#include "Matrix.h"
#include "vector"

using namespace std;

Matrix::Matrix() {}

Matrix::Matrix(int m) {}

Matrix::Matrix(int m, int n) {
    vector<float> vec;
    vec.assign(m, 0);
    matrix.assign(n, vec);
}

Matrix::Matrix(vector<vector<float>> matrix) {
    this->matrix = matrix;
}

void Matrix::print() {
    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Matrix::transpose() {

    vector<vector<float>> mat;
    vector<float> vec;
    vec.assign(getHeight(), 0);
    mat.assign(getWidth(), vec);

    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            mat[j][i] = matrix[i][j];
        }
    }
    matrix = mat;
}

void Matrix::setValue(int m, int n, float value) {
    //if ( 0 <= m && m < getWidth() && 0 <= n && n < getHeight()){ should be valid already
    matrix[m][n] = value;
    //}
}

vector<vector<float>> Matrix::getRemainder(int m, int n) {
    vector<vector<float>> mat;
    vector<float> vec;
    vec.assign(getHeight() - 1, 0);
    mat.assign(getWidth() - 1, vec);

    int a = 0, b = 0;
    for (int i = 0; i < getWidth() - 1; ++i) {
        if (i == m)
            a++;
        b = 0;
        for (int j = 0; j < getHeight() - 1; ++j) {
            if (j == n)
                b++;
            mat[j][i] = matrix[b][a];
            b++;
        }
        a++;
    }
    return mat;
}

float Matrix::getValue(int m, int n) {
    return matrix[m][n];
}

float Matrix::getDet() {
    if (getWidth() != getHeight()) {
        cout << "Wrong Matrix dimensions m != n" << endl;
        return 0;
    }
    if (getWidth() == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else if (getWidth() == 3) {
        return (matrix[0][0] * matrix[1][1] * matrix[2][2] +
                matrix[0][1] * matrix[1][2] * matrix[2][0] +
                matrix[0][2] * matrix[1][0] * matrix[2][1]) -
               (matrix[0][2] * matrix[1][1] * matrix[2][0] +
                matrix[0][1] * matrix[1][0] * matrix[2][2] +
                matrix[0][0] * matrix[1][2] * matrix[2][1]);

    } else {
        float det = 0;
        float sign;
        Matrix matrix1;

        for (int i = 0; i < getHeight(); ++i) {
            matrix1 = Matrix(getRemainder(i, 0));
            if (i % 2 == 0) {
                sign = 1;
            } else {
                sign = -1;
            }
            det += matrix[0][i] * sign * matrix1.getDet();
        }
        return det;
    }

}

/**
 * returns the determinant of the Matrix without the m'th collum and n'th row
 * @param m number for the row
 * @param n number for the collum
 * @return determinant of the remaining matrix
 */
float Matrix::getDetRemainder(int m, int n) {
    Matrix mat = Matrix(getRemainder(m, n));
    return mat.getDet();
}


Matrix Matrix::getInverse() {
    if (getWidth() != getHeight()) {
        cout << "Wrong matrix dimensions" << endl;
        return Matrix();
    }

    Matrix matrix1 = Matrix(matrix);
    float sign = 0;

    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            if ((i + j) % 2 == 0) {
                sign = 1;
            } else {
                sign = -1;
            }
            matrix1.setValue(i, j, getDetRemainder(i, j) * sign);
        }
    }
    matrix1 * (float) (1 / getDet());
    return matrix1;
}


int Matrix::getWidth() {
    return size(matrix[0]);
}

int Matrix::getHeight() {
    return size(matrix);
}


Matrix Matrix::operator+(Matrix &obj) {
    if (getWidth() == obj.getWidth() && getHeight() == obj.getHeight()) {
        Matrix mat = Matrix(getHeight(), getWidth());

        for (int i = 0; i < getHeight(); ++i) {
            for (int j = 0; j < getWidth(); ++j) {
                mat.setValue(i, j, matrix[i][j] + obj.getValue(i, j));
            }
        }
        return mat;
    } else {
        cout << "Wrong Matrix dimensions" << endl;
        return Matrix();
    }
}

Matrix Matrix::operator-(Matrix &obj) {

    if (getWidth() == obj.getWidth() && getHeight() == obj.getHeight()) {
        Matrix mat = Matrix(getHeight(), getWidth());

        for (int i = 0; i < getHeight(); ++i) {
            for (int j = 0; j < getWidth(); ++j) {
                mat.setValue(i, j, matrix[i][j] - obj.getValue(i, j));
            }
        }
        return mat;
    } else {
        cout << "Wrong Matrix dimensions" << endl;
        return Matrix();
    }
}

Matrix Matrix::operator*(Matrix &obj) {

    if (getWidth() == obj.getHeight()) {

        Matrix mat = Matrix(obj.getWidth(), getHeight());

        float value;
        for (int i = 0; i < obj.getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                value = 0;
                for (int k = 0; k < obj.getHeight(); ++k) {
                    value += matrix[j][k] * obj.getValue(k, i);
                }
                mat.setValue(j, i, value);
            }
        }
        return mat;
    } else {
        cout << "Wrong Matrix dimensions" << endl;
        return Matrix();
    }
}

void Matrix::operator*(float obj) {
    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            matrix[i][j] *= obj;
        }
    }
}


















