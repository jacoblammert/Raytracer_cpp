//
// Created by Jacob on 17.04.2020.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "Vector.h"

class Ray {
public:
    Ray(Vector position, Vector direction);

    void print();

    Vector getPos();

    Vector getDir();

private:
    Vector position;
    Vector direction;
};


#endif //RAYTRACER_RAY_H
