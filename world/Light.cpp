//
// Created by Jacob on 19.04.2020.
//

#include "Light.h"

Light::Light() {
    position = Vector();
    color = Color(1,1,1);
}

Light::Light(Vector position, Color color) {
    this->position = position;
    this->color = color;
}

Light::Light(Vector position, Color color, float intensity) {
    this->position = position;
    this->color = color;
    this->intensity = intensity;
}

Vector Light::getPosition() {
    return position;
}

Color Light::getColor() {
    return color;
}

float Light::getIntensity() {
    return intensity;
}

void Light::setPosition(Vector position) {
    this->position = position;
}


void Light::setColor(Color color) {
    this->color = color;
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
}


