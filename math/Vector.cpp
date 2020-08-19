//
// Created by Jacob on 14.04.2020.
//



#include "Vector.h"
#include <iostream>
#include <cmath>


Vector::Vector() :
        x{0}, y{0}, z{0} {
}

Vector::Vector(float x) :
        x{x}, y{0}, z{0} {}

Vector::Vector(float x, float y) :
        x{x}, y{y}, z{0} {}

Vector::Vector(float x, float y, float z) :
        x{x}, y{y}, z{z} {}

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
    std::cout << "X: " << x << " Y: " << y << " Z: " << z << " Length: " << getLength() << std::endl;
}


float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

float Vector::getZ() const {
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

float Vector::dot(Vector const &obj) {
    return x * obj.x + y * obj.y + z * obj.z;
}

Vector Vector::cross(Vector const &obj) {
    return {y * obj.z - z * obj.y, z * obj.x - x * obj.z, x * obj.y - y * obj.x};
}


Vector Vector::getReflected(Vector normal) {
    Vector thisVec = *this;
    thisVec.scale(-1);
    float NV = fmax(normal.dot(thisVec), 0);//angle
    normal.scale(NV * 2);
    return normal - thisVec;
}

Vector Vector::getRefracted(Vector normal, float n) {

    Vector thisVec{*this};

    float cosI = -thisVec.dot(normal);
    float sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) return thisVec.getReflected(normal); // TIR
    float cosT = sqrt(1.0 - sinT2);

    thisVec.scale(n);
    normal.scale((n * cosI - cosT));
    return thisVec + normal;
}

Vector Vector::operator+(Vector const &obj) {
    return {x + obj.x, y + obj.y, z + obj.z};
}

Vector Vector::operator-(Vector const &obj) {
    return {x - obj.x, y - obj.y, z - obj.z};
}

///free operator:
Vector operator-(const Vector &left, const Vector *right) {
    return {left.getX() - right->getX(), left.getY() - right->getY(), left.getZ() - right->getY()};
}



//Vector Vector::operator-(Vector *const &obj) {
//    return {x - obj->x,y - obj->y,z - obj->z};
//}

/*/
float Vector::operator * (Vector &obj) {
    float res;
    res = x * obj.getX() + y * obj.getY() + z * obj.getZ();
    return res;
}
 /*/
Vector Vector::operator*(Vector const &obj) {
    return {y * obj.z - z * obj.y, z * obj.x - x * obj.z, x * obj.y - y * obj.x};
}

Vector Vector::operator*(float &obj) {
    return {x * obj, y * obj, z * obj};
}

void Vector::divide(float value) {
    x = value / x;
    y = value / y;
    z = value / z;
}

int Vector::sign(int pos) {
    return ((pos == 0 && x < 0) || (pos == 1 && y < 0) || (pos == 2 && z < 0));
}

















