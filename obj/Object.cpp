//
// Created by Jacob on 19.04.2020.
//

#include "Object.h"

#include <utility>
#include <iostream>

Object::Object() {

}

Object::Object(std::string name) {
    this->name = std::move(name);
}

Object::Object(std::string name, std::vector<Shape*> triangles) {
    this->name = std::move(name);
    this->triangles = std::move(triangles);

}

void Object::setTriangles(std::vector<Shape*> triangles) {
    this->triangles = std::move(triangles);
}

std::vector<Shape *> Object::getTriangles() {
    return this->triangles;
}

void Object::setMaterial(Material* material) {
    for (int i = 0; i < triangles.size(); ++i) {
        triangles[i]->setMaterial(material);
    }

}

void Object::add(Vector position) {
    for (int i = 0; i < triangles.size(); ++i) {
            triangles[i]->translate(position);
    }
}


