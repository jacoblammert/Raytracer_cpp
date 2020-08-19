//
// Created by Jacob on 18.04.2020.
//

#include "Shape.h"


Material* Shape::getMaterial() {
    return material;
}

void Shape::setMaterial(Material* material) {
   this->material = material;
}