//
// Created by Jacob on 15.04.2020.
//
/**/
#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

#include <vector>
#include "Vector.h"

using namespace std;

class Matrix {
public:
    Matrix();

    Matrix(int m);

    //m = x , n = y
    Matrix(int m, int n);

    Matrix(vector<vector<float>> matrix);

    void print();

    void transpose();

    void setValue(int m, int n, float value);

    vector<vector<float>> getRemainder(int m, int n);

    //float getMatrix();
    float getValue(int m, int n);

    float getDet();

    float getDetRemainder(int m, int n);

    Matrix getInverse();

    int getWidth();

    int getHeight();

    Matrix operator+(Matrix &obj);

    Matrix operator-(Matrix &obj);

    Matrix operator*(Matrix &obj);

    void operator*(float obj);

    Vector operator*(Vector &obj);

private:
    vector<vector<float>> matrix;

};


#endif //RAYTRACER_MATRIX_H
/**/