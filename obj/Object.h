//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include <string>
#include <vector>
#include "../geometry/Triangle.h"

class Object {
public:
    Object();

    Object(std::string name);

    Object(std::string name, std::vector<Shape *> triangles);

    void setTriangles(std::vector<Shape *> triangles);

    void setMaterial(Material* material);

    void add(Vector position);


    std::vector<Shape *> getTriangles();

private:
    std::string name;
    std::vector<Shape *> triangles;
};


#endif //RAYTRACER_OBJECT_H
