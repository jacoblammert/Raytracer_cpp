//
// Created by Jacob on 14.04.2020.
//



#include "Vector.h"
#include <iostream>

using namespace std;

Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(float x) {
    this->x = x;
}

Vector::Vector(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector::setX(float value) {
    x = value;
}

void Vector::setY(float value) {
    y = value;
}

void Vector::setZ(float value) {
    z = value;
}

void Vector::normalize() {
    auto a = getLength();
    x /= a;
    y /= a;
    z /= a;
}

void Vector::scale(float value) {
    x *= value;
    y *= value;
    z *= value;
}

void Vector::print() {
    cout << "X: " << x << " Y: " << y << " Z: " << z << " Length: " << getLength() << endl;
}


float Vector::getX() {
    return x;
}

float Vector::getY() {
    return y;
}

float Vector::getZ() {
    return z;
}

float Vector::getLength() {
    return (float) sqrt(x * x + y * y + z * z);
}

float Vector::dot(Vector &obj) {
    return x * obj.getX() + y * obj.getY() + z * obj.getZ();
}

Vector Vector::cross(Vector &obj) {
    Vector res;
    res.setX(y * obj.getZ() - z * obj.getY());
    res.setY(z * obj.getX() - x * obj.getZ());
    res.setZ(x * obj.getY() - y * obj.getX());
    return res;
}

Vector Vector::operator+(Vector &obj) {
    Vector res;
    res.setX(x + obj.getX());
    res.setY(y + obj.getY());
    res.setZ(z + obj.getZ());
    return res;
}

Vector Vector::operator-(Vector &obj) {
    Vector res;
    res.setX(x - obj.getX());
    res.setY(y - obj.getY());
    res.setZ(z - obj.getZ());
    return res;
}

/*/
float Vector::operator * (Vector &obj) {
    float res;
    res = x * obj.getX() + y * obj.getY() + z * obj.getZ();
    return res;
}
 /*/
Vector Vector::operator*(Vector &obj) {
    Vector res;
    res.setX(y * obj.getZ() - z * obj.getY());
    res.setY(z * obj.getX() - x * obj.getZ());
    res.setZ(x * obj.getY() - y * obj.getX());
    return res;
}

Vector Vector::operator*(float &obj) {
    Vector res;
    res.setX(x * obj);
    res.setY(y * obj);
    res.setZ(z * obj);
    return res;
}









