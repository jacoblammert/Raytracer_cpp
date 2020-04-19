//
// Created by Jacob on 19.04.2020.
//

#include "Light.h"

Light::Light() {
    position = Vector();
    color = Vector(255,255,255);
}

Light::Light(Vector position, Vector color) {
    this->position = position;
    this->color = color;
}

Vector Light::getPosition() {
    return position;
}

Vector Light::getColor() {
    return color;
}
