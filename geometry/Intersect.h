//
// Created by Jacob Lammert on 21.08.2020.
//

#ifndef RAYTRACER_INTERSECT_H
#define RAYTRACER_INTERSECT_H


#include <cmath>
#include "../math/Ray.h"

struct Intersect {
public:
    Ray ray;
    Vector HitPoint;
    Vector HitNormal;
    float distance = INFINITY;
};


#endif //RAYTRACER_INTERSECT_H
