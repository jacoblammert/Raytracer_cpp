//
// Created by Jacob on 18.04.2020.
//

#include <cmath>
#include "Triangle.h"

Triangle::Triangle(Vector a, Vector b, Vector c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = Vector(255, 255, 255);
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

bool Triangle::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();

    float t;

// compute plane's normal
    Vector v0v1 = b - a;
    Vector v0v2 = c - a;
    // no need to normalize
    Vector N = v0v1 * v0v2; // N
    float area2 = N.getLength();

    // Step 1: finding P

    // check if ray and plane are parallel ?
    float NdotRayDirection = N.dot(raydirection);
    if (fabs(NdotRayDirection) < 0.000001f) // almost 0
        return false; // they are parallel so they don't intersect !

    // compute d parameter using equation 2
    float d = N.dot(a);

    // compute t (equation 3)
    t = (N.dot(rayposition) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind

    // compute the intersection point using equation 1
    raydirection.scale(t);
    Vector P = rayposition + raydirection;

    // Step 2: inside-outside test
    Vector C; // vector perpendicular to triangle's plane

    // edge 0
    Vector edge0 = b - a;
    Vector vp0 = P - a;
    C = edge0 * vp0;
    if (N.dot(C) < 0) return false; // P is on the right side

    // edge 1
    Vector edge1 = c - b;
    Vector vp1 = P - b;
    C = edge1 * vp1;
    if (N.dot(C) < 0) return false; // P is on the right side

    // edge 2
    Vector edge2 = a - c;
    Vector vp2 = P - c;
    C = edge2 * vp2;
    if (N.dot(C) < 0) return false; // P is on the right side;

#pragma omp critical
    {
        if (t < distance) {
            distance = t;
            HitNormal = normal;
            HitPoint = P;
            id = newid;
        }
    }

    return true;
}

Vector Triangle::getNormal(Vector pos) {
    return normal;
}
