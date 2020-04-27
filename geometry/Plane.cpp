//
// Created by Jacob on 18.04.2020.
//

#include <iostream>
#include "Plane.h"

Plane::Plane(Vector position, Vector normal) {
    pos = position;
    this->normal = normal;
    this->material.setColor({1,1,1});
}

Plane::Plane(Vector position, Vector normal, Color color) {
    pos = position;
    this->normal = normal;
    this->normal.normalize();
    //this->normal.scale(-1);
    this->material.setColor(color);
}

int Plane::getId() {
    return 0;
}



bool Plane::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();

    float denom = normal.dot(raydirection);
    Vector p0l0 = pos - rayposition;

    float t = p0l0.dot(normal) / denom;

    if (t >= 0) {
//#pragma omp critical
        {
            raydirection.scale(t);
            if (0 < t && t < distance) {
                distance = t;
                HitPoint = rayposition + raydirection;
                HitNormal = normal;
                id = newid;
            }
        }
        return true;
    }
    return false;
}

Vector Plane::getNormal(Vector pos) {
    return normal;
}

Vector Plane::getMin() {
    return Vector(); // should give back a box of the desired size of the plane
}

Vector Plane::getMax() {
    return Vector(); // should give back a box of the desired size of the plane (cutting doesn't work)
}

Vector Plane::getMedian() {
    return pos;
}

void Plane::print() {
    std::cout<<"Plane"<<std::endl;
}
/**/
Material Plane::getMaterial() {
    return material;
}
void Plane::setMaterial(Material material) {
    this->material = material;
}
/**/
