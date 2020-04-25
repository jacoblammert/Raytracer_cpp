//
// Created by Jacob on 24.04.2020.
//

#include <iostream>
#include "Color.h"

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;

}

/**
 * 0 - 1
 * @return red
 */
float Color::getR() {
    return r;
}

/**
 * 0 - 1
 * @return green
 */
float Color::getG() {
    return g;
}

/**
 * 0 - 1
 * @return blue
 */
float Color::getB() {
    return b;
}

void Color::setRange(float min, float max) {

    if (r < min) {
        r = min;
    } else if (max < r) {
        r = max;
    }

    if (g < min) {
        g = min;
    } else if (max < g) {
        g = max;
    }

    if (b < min) {
        b = min;
    } else if (max < b) {
        b = max;
    }
}

void Color::scale(float scale) {
    r *= scale;
    g *= scale;
    b *= scale;
}

void Color::print() {
    std::cout<<"Red: " <<r<<" Green: " << g << " Blue: "<<std::endl;
}

Color Color::operator+(Color &obj) {
    Color a = Color(r + obj.getR(), g + obj.getG(), b + obj.getB());
    return a;
}

Color Color::operator+=(Color &obj) {

    Color a = Color(r + obj.getR(), g + obj.getG(), b + obj.getB());
    return a;
}

Color Color::operator-(Color &obj) {

    Color a = Color(r - obj.getR(), g - obj.getG(), b - obj.getB());
    return a;
}

Color Color::operator-=(Color &obj) {
    Color a = Color(r - obj.getR(), g - obj.getG(), b - obj.getB());
    return a;;
}

Color Color::operator*(Color &obj) {
    Color a = Color(r * obj.getR(), g * obj.getG(), b * obj.getB());
    return a;
}

Color Color::operator*=(Color &obj) {
    Color a = Color(r * obj.getR(), g * obj.getG(), b * obj.getB());
    return a;
}

Color Color::operator/(Color &obj) {
    Color a = Color(r / obj.getR(), g / obj.getG(), b / obj.getB());
    return a;
}

Color Color::operator/=(Color &obj) {
    Color a = Color(r / obj.getR(), g / obj.getG(), b / obj.getB());
    return a;
}






