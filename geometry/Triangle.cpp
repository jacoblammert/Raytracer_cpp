//
// Created by Jacob on 18.04.2020.
//

#include <cmath>
#include <iostream>
#include "Triangle.h"

Triangle::Triangle(Vector a, Vector b, Vector c) :
        a{a},
        b{b},
        c{c} {
    Vector ab = b - a;
    Vector ac = c - a;
    this->normal = ab * ac;
    this->normal.normalize();
}

Triangle::Triangle(Vector a, Vector b, Vector c, Color color) :
        a{a},
        b{b},
        c{c} {
    Vector ab = b - a;
    Vector ac = c - a;
    this->normal = ab * ac;
    this->normal.normalize();
}


bool Triangle::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance) {




    Vector pvec = ray.getDir() * (c - a);
    float det = pvec.dot(b - a);

    // ray and triangle are parallel if det is close to 0
    if (fabs(det) == 0.0f)
        return false;

    Vector rayposition = ray.getPos();

    float u = pvec.dot(rayposition - a)/det;

    if (u < 0 || u > 1)
        return false;

    pvec = (rayposition - a) * (b-a);
    float v = pvec.dot(ray.getDir()) / det;

    if (v < 0 || (u + v) > 1)
        return false;

    det = pvec.dot(c - a)/det;

    if (0 < det && det < distance) {
        distance = det;
        HitNormal = this->normal;
        pvec = ray.getDir();
        pvec.scale(det);
        HitPoint = rayposition + pvec;
    }
    return true;
}

Vector Triangle::getNormal(Vector pos) {
    return this->normal;
}

Vector Triangle::getMin() {
    Vector min = a;

    for (int j = 0; j < 3; ++j) {
        if (min.get(j) > b.get(j)) {
            min.set(j, b.get(j));
        }
    }

    for (int j = 0; j < 3; ++j) {
        if (min.get(j) > c.get(j)) {
            min.set(j, c.get(j));
        }
    }
    return min;
}


Vector Triangle::getMax() {
    Vector max = a;
    for (int j = 0; j < 3; ++j) {
        if (max.get(j) < b.get(j)) {
            max.set(j, b.get(j));
        }
    }
    for (int j = 0; j < 3; ++j) {
        if (max.get(j) < c.get(j)) {
            max.set(j, c.get(j));
        }
    }
    return max;
}

Vector Triangle::getMedian() {

    Vector median = a + b + c;
    median.scale(1.0f / 3.0f);
    return median;
}

void Triangle::print() {
    std::cout << "Triangle" << std::endl;
    std::cout << "A: ";
    a.print();
    std::cout << "B: ";
    b.print();
    std::cout << "C: ";
    c.print();
}

Material *Triangle::getMaterial() {
    return this->material;
}

void Triangle::setMaterial(Material *material) {
    this->material = material;
}

void Triangle::translate(Vector position) {
    a = a+position;
    b = b+position;
    c = c+position;
}
