//
// Created by Jacob on 14.04.2020.
//



#include "Vector.h"
#include <iostream>
#include <cmath>

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

void Vector::set(int position, float value) {
    if (position % 3 == 0) {
        x = value;
    } else if (position % 3 == 1) {
        y = value;
    } else {
        z = value;
    }
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

float Vector::get(int position) {
    if (position % 3 == 0) {
        return x;
    } else if (position % 3 == 1) {
        return y;
    } else {
        return z;
    }
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

Vector Vector::getReflected(Vector normal) {
    Vector thisVec = *this;
    thisVec.normalize();
    normal.normalize();
    thisVec.scale(-1);
    float NV = fmax(normal.dot(thisVec), 0);//angle
    normal.scale(NV * 2);
    return normal - thisVec;
}

Vector Vector::getRefracted(Vector normal, float n1, float n2) {

    Vector thisVec = *this;
    thisVec.normalize();
    normal.normalize();

    float n = n1 / n2;
    float cosI = -thisVec.dot(normal);
    float sinT2 = n * n * (1.0 - cosI * cosI);
    if(sinT2 > 1.0) return thisVec.getReflected(normal); // TIR
    float cosT = sqrt(1.0 - sinT2);

    thisVec.scale(n);
    normal.scale((n * cosI - cosT));
    return thisVec + normal;
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

void Vector::divide(float value) {
    x = value / x;
    y = value / y;
    z = value / z;
}

int Vector::sign(int pos) {
    if ((pos == 0 && x < 0) || (pos == 1 && y < 0) || (pos == 2 && z < 0)) {
        return 1;
    }
    return 0;
}
















