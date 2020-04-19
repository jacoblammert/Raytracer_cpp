//
// Created by Jacob on 18.04.2020.
//

#include "Triangle.h"

Triangle::Triangle(Vector a, Vector b, Vector c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = Vector(255,255,255);
    Vector ab = b - a;
    Vector ac = c - a;
    this->normal = ab * ac;
}

Triangle::Triangle(Vector a, Vector b, Vector c, Vector color) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = color;
    Vector ab = b - a;
    Vector ac = c - a;
    this->normal = ab * ac;
}

int Triangle::getId() {
    return 0;
}

Vector Triangle::getRgb() {
    return color;
}

bool Triangle::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();



    return false;
}

Vector Triangle::getNormal(Vector pos) {
    return normal;
}
