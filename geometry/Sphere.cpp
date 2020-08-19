//
// Created by Jacob on 18.04.2020.
//

#include <iostream>
#include "Sphere.h"
#include "cmath"
#include "../debug/Timer.h"

Sphere::Sphere(Vector pos, float radius):
pos{pos},radius{radius}{
}

Sphere::Sphere(Vector pos, float radius, Material* material):
        pos{pos},radius{radius} {
    this->material = material;
}


bool Sphere::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();


    float t = (pos - rayposition).dot(raydirection);


    raydirection = raydirection * t;

    float y = (pos - rayposition - raydirection).getLength();

    if (y < radius) { // (y < radius)

        float x = sqrt(radius * radius - y * y);
        float t1 = t - x; // close intersection point
        float t2 = t + x; // far intersection point

        raydirection = ray.getDir();
        raydirection.normalize();


            if (0 < t1 && t1 < distance) {
                raydirection.scale(t1);
                distance = t1;
                HitPoint = rayposition + raydirection;
                HitNormal = getNormal(HitPoint);
                return true;
            }
            if (t1 < 0 && 0 < t2 && t2 < distance) {
                raydirection.scale(t2);
                distance = t2;
                HitPoint = rayposition + raydirection;
                HitNormal = getNormal(HitPoint);
                return true;
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
Material* Sphere::getMaterial() {
    return material;
}

void Sphere::setMaterial(Material* material) {
    this->material = material;
}

void Sphere::translate(Vector position) {

}
/**/
