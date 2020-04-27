//
// Created by Jacob on 24.04.2020.
//

#include "Material.h"

#include <utility>
#include <iostream>

Material::Material() {
    roughness = 0.5f;
    glossy = 0.0f;
    transparency = 0.00f;
    refractiveIndex = 1.0f;
    color = {255, 255, 255};
}

Material::Material(Color color) {

    roughness = 0.5f;
    glossy = 0.0f;
    transparency = 0.0f;
    refractiveIndex = 1;
    this->color = color;
}

Material::Material(Color color, float roughness, float glossy, float transparency) {
    this->roughness = roughness;
    this->glossy = glossy;
    this->transparency = transparency;
    refractiveIndex = 1;
    this->color = color;
}

Material::Material(Color color, float roughness, float glossy, float transparency, float refractiveIndex) {

    this->roughness = roughness;
    this->glossy = glossy;
    this->transparency = transparency;
    this->refractiveIndex = refractiveIndex;
    this->color = color;
}


float Material::getRoughness() {
    return roughness;
}

float Material::getGlossy() {
    return glossy;
}

float Material::getTransparency() {
    return transparency;
}

Color Material::getColor() {
    return color = Color(1.0f,1.0f,1.0f);
}

float Material::getRefractiveIndex() {
    return refractiveIndex;
}

void Material::setColor(Color color) {
    this->color = color;
}




