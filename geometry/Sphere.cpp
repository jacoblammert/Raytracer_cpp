//
// Created by Jacob on 18.04.2020.
//

#include <iostream>
#include "Sphere.h"
#include "cmath"
#include "../Debug/Chronometer.h"

Sphere::Sphere(Vector pos, float radius) {
    this->pos = pos;
    this->radius = radius;
}

Sphere::Sphere(Vector pos, float radius, Vector color) {
    this->pos = pos;
    this->radius = radius;
    this->color = color;
}

int Sphere::getId() {
    return 0;
}


Vector Sphere::getRgb() {
    return color;
}

bool Sphere::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();


    float t = (pos - rayposition).dot(raydirection);


    raydirection = raydirection * t;
    Vector point = rayposition + raydirection;

    float y = (pos - point).getLength();

    if (y < radius) { // (y < radius)

        float x = sqrt(radius * radius - y * y);
        float t1 = t - x; // close intersection point

        raydirection = ray.getDir() * t1;

//#pragma omp critical
        {

            float dist = (ray.getPos() - rayposition + raydirection).getLength();

            if (dist < distance) {
                distance = dist;
                HitPoint = rayposition + raydirection;
                HitNormal = getNormal(HitPoint);
                id = newid;
            }
        }
        return true;
    }
    return false;
}

Vector Sphere::getNormal(Vector pos) {
    return pos - this->pos;
}

Vector Sphere::getMin() {
    Vector rad = Vector(radius,radius,radius);
    return pos - rad;
}

Vector Sphere::getMax() {
    Vector rad = Vector(radius,radius,radius);
    return pos + rad;
}

Vector Sphere::getMedian() {
    return pos;
}

void Sphere::print() {
    std::cout<<"Sphere"<<std::endl;
}


