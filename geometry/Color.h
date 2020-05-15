//
// Created by Jacob on 24.04.2020.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


class Color {
public:
    Color();

    Color(float r, float g, float b);

    float getR();

    float getG();

    float getB();

    void setRange(float min, float max);

    void scale(float scale);

    void print();

    void setR(int red);

    void setG(int green);

    void setB(int blue);

    Color operator+(Color const&obj);

    Color operator+=(Color const&obj);

    Color operator-(Color const&obj);

    Color operator-=(Color const&obj);

    Color operator*(Color const&obj);

    Color operator*=(Color const&obj);

    Color operator/(Color const&obj);

    Color operator/=(Color const&obj);

private:
    float r, g, b;
};


#endif //RAYTRACER_COLOR_H
