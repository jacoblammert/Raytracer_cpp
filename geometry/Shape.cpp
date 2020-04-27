//
// Created by Jacob on 18.04.2020.
//

#include "Shape.h"



int Shape::getId() {
    return 0;
}


Color Shape::getRgb() {
    return {};
}

Vector Shape::getNormal(Vector pos) {
    return {};
}
/**/
Material Shape::getMaterial() {
    return {};
}


void Shape::setMaterial(Material material) {
   this->material = material;
}/**/