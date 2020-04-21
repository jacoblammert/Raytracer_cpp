//
// Created by Jacob on 21.04.2020.
//

#include "Box.h"

Box::Box(Vector minXminYminZ, Vector maxXmaxYmaxZ) {
    color = Vector(255, 255, 255);

    bounds.push_back(minXminYminZ);
    bounds.push_back(maxXmaxYmaxZ);
}

Box::Box(Vector minXminYminZ, Vector maxXmaxYmaxZ, Vector color) {
    bounds.push_back(minXminYminZ);
    bounds.push_back(maxXmaxYmaxZ);
    this->color = color;
}

int Box::getId() {
    return 0;
}

Vector Box::getRgb() {
    return color;
}

bool Box::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector rayposition = ray.getPos();
    Vector raydirection = ray.getDir();
    raydirection.divide(1);

    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tmax = (bounds[1 - raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tymin = (bounds[raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();
    tymax = (bounds[1 - raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();
    tzmax = (bounds[1 - raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

#pragma omp critical
    {
        raydirection = ray.getDir();
        raydirection.scale(tmin);

        float dist = tmin;//(/*ray.getPos() - rayposition + */raydirection).getLength();

        if (dist < distance) {
            distance = dist;
            HitPoint = rayposition + raydirection;
            HitNormal = getNormal(HitPoint);
            id = newid;
        }
    }
    return true;
}

Vector Box::getNormal(Vector pos) {

    float epsilon = 0.001f;

    if (pos.getX() <= bounds[0].getX() + epsilon) {
        return {-1, 0, 0};
    } else if (pos.getX() >= bounds[1].getX() - epsilon) {
        return {1, 0, 0};
    }
    if (pos.getY() <= bounds[0].getY() + 0.001) {
        return {0, -1, 0};
    } else if (pos.getY() >= bounds[1].getY() - epsilon) {
        return {0, 1, 0};
    }
    if (pos.getZ() <= bounds[0].getZ() + epsilon) {
        return {0, 0, -1};
    } else if (pos.getZ() >= bounds[1].getZ() - epsilon) {
        return {0, 0, 1};
    }
    return {0, 1, 0};
}
