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

    Color operator+(Color &obj);

    Color operator+=(Color &obj);

    Color operator-(Color &obj);

    Color operator-=(Color &obj);

    Color operator*(Color &obj);

    Color operator*=(Color &obj);

    Color operator/(Color &obj);

    Color operator/=(Color &obj);

private:
    float r, g, b;
};


#endif //RAYTRACER_COLOR_H
