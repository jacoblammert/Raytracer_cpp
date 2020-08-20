//
// Created by Jacob on 18.04.2020.
//

#include <iostream>
#include "Plane.h"

Plane::Plane(Vector position, Vector normal) {
    pos = position;
    this->normal = normal;
}

Plane::Plane(Vector position, Vector normal, Material *material) :
        pos{position}, normal{normal} {
    this->normal.normalize();
    this->material = material;
}


bool Plane::getIntersectVec(Intersect* intersect) {

    Vector raydirection = intersect->ray.getDir();
    Vector rayposition = intersect->ray.getPos();

    float denom = normal.dot(raydirection);
    Vector p0l0 = pos - rayposition;

    float t = p0l0.dot(normal) / denom;

    if (t >= 0) {

        raydirection.scale(t);
        if (0 < t && t < intersect->distance) {
            intersect->distance = t;
            intersect->HitPoint = rayposition + raydirection;
            intersect->HitNormal = normal;
        }
        return true;
    }
    return false;
}

Vector Plane::getNormal(Vector pos) {
    return normal;
}

Vector Plane::getMin() {
    return {}; // should give back a box of the desired size of the plane
}

Vector Plane::getMax() {
    return {}; // should give back a box of the desired size of the plane (cutting doesn't work)
}

Vector Plane::getMedian() {
    return pos;
}

void Plane::print() {
    std::cout << "Plane" << std::endl;
}

/**/
Material *Plane::getMaterial() {
    return material;
}

void Plane::setMaterial(Material *material) {
    this->material = material;
}

void Plane::translate(Vector position) {

}
/**/
