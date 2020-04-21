//
// Created by Jacob on 18.04.2020.
//

#include "Plane.h"

Plane::Plane(Vector position, Vector normal) {
    pos = position;
    this->normal = normal;
    this->color = Vector(255, 255, 255);
}

Plane::Plane(Vector position, Vector normal, Vector color) {
    pos = position;
    this->normal = normal;
    this->normal.normalize();
    //this->normal.scale(-1);
    this->color = color;
}

int Plane::getId() {
    return 0;
}


Vector Plane::getRgb() {
    return color;
}

bool Plane::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector raydirection = ray.getDir();
    Vector rayposition = ray.getPos();

    float denom = normal.dot(raydirection);
    Vector p0l0 = pos - rayposition;

    float t = p0l0.dot(normal) / denom;

    if (t >= 0) {
#pragma omp critical
        {
            raydirection.scale(t);

            float dist = t;
            if (dist < distance) {
                distance = dist;
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


