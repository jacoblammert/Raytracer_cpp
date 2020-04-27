//
// Created by Jacob on 17.04.2020.
//

#include <iostream>
#include "Ray.h"

Ray::Ray(Vector position, Vector direction) {
    this->position = position;
    this->direction = direction;
    this->direction.normalize();
}

void Ray::print() {
    std::cout << "Position: ";
    position.print();
    std::cout << "Dircetion: ";
    direction.print();
}

Vector Ray::getPos() {
    return this->position;
}


Vector Ray::getDir() {
    return this->direction;
}

float Ray::getRefractionindex() {
    return this->refractionindex;
}

void Ray::setRefractionindex(float index) {
    this->refractionindex = index;
}


