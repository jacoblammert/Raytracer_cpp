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
    this->material.setColor({1, 1, 1});
    Vector ab = b - a;
    Vector ac = c - a;
    this->normal = ab * ac;
}

Triangle::Triangle(Vector a, Vector b, Vector c, Color color):
        a{a},
        b{b},
        c{c} {
    this->material.setColor(color);
    Vector ab = b - a;
    Vector ac = c - a;
    this->normal = ab * ac;
}

int Triangle::getId() {
    return 0;
}


bool Triangle::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();


    Vector v0v1 = b - a;
    Vector v0v2 = c - a;
    Vector pvec = raydirection * v0v2;
    float det = v0v1.dot(pvec);

    // if the determinant is negative the triangle is backfacing
    // if the determinant is close to 0, the ray misses the triangle
    if (det < 0.0001f) {
        //normal.scale(-1);
        //return false;
    }

    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < 0.0001) return false;

    float invDet = 1 / det;

    Vector tvec = rayposition - a;
    float u = tvec.dot(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    Vector qvec = tvec * v0v1;
    float v = raydirection.dot(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;

    float t = v0v2.dot(qvec) * invDet;
//#pragma omp critical
    {
        if (0 < t && t < distance) {
            distance = t;
            HitNormal = normal;
            raydirection.scale(t);
            HitPoint = rayposition + raydirection;
            id = newid;
        }
    }
    return true;
}

Vector Triangle::getNormal(Vector pos) {
    return normal;
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

/**/
Material Triangle::getMaterial() {
    return material;
}

void Triangle::setMaterial(Material material) {
    this->material = material;
}/**/
