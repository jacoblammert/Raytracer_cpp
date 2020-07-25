//
// Created by Jacob on 18.04.2020.
//

#include "Shape.h"



int Shape::getId() {
    return 0;
}


Vector Shape::getNormal(Vector pos) {
    return {};
}
/**/
Material* Shape::getMaterial() {
    return material;
}


void Shape::setMaterial(Material* material) {
   this->material = material;
}/**/