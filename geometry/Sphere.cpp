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

Sphere::Sphere(Vector pos, float radius, Color color) {
    this->pos = pos;
    this->radius = radius;
    this->color = color;
}

int Sphere::getId() {
    return 0;
}


Color Sphere::getRgb() {
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
        float t2 = t + x; // far intersection point

        raydirection = ray.getDir();
        raydirection.normalize();

//#pragma omp critical
        {

            //float dist = t1;//(ray.getPos() - rayposition + raydirection).getLength();

            if (0 < t1 && t1 < distance) {
                raydirection.scale(t1);
                distance = t1;
                HitPoint = rayposition + raydirection;
                HitNormal = getNormal(HitPoint);
                id = newid;
                return true;
            }
            if (t1 < 0 && 0 < t2 && t2 < distance) {
                raydirection.scale(t2);
                distance = t2;
                HitPoint = rayposition + raydirection;
                HitNormal = getNormal(HitPoint);
                id = newid;
                //std::cout<<"Hitpoint: ";
                //HitPoint.print();
                //std::cout<<std::endl;
                return true;
            }
        }
    }
    return false;
}

Vector Sphere::getNormal(Vector position) {
    Vector normal = position - this->pos;
    normal.normalize();
    return normal;
}

Vector Sphere::getMin() {
    Vector rad = Vector(radius, radius, radius);
    return pos - rad;
}

Vector Sphere::getMax() {
    Vector rad = Vector(radius, radius, radius);
    return pos + rad;
}

Vector Sphere::getMedian() {
    return pos;
}

void Sphere::print() {
    std::cout << "Sphere" << std::endl;
}

/**/
Material Sphere::getMaterial() {
    return material;
}

void Sphere::setMaterial(Material material) {
    this->material = material;
}/**/
