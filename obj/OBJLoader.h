//
// Created by Jacob on 23.04.2020.
//

#ifndef RAYTRACER_OBJLOADER_H
#define RAYTRACER_OBJLOADER_H


#include <string>
#include <vector>
#include "../geometry/Triangle.h"
#include "Object.h"

class OBJLoader {
public:
    OBJLoader();

    explicit OBJLoader(std::string filename);

    void setFilename(std::string filename);

    void LoadOBJ();

    void printOBJ();

    void split();

    void buildObject();

    Object getObject();

private:
    std::string filename;
    std::string objectname;
    std::vector<Shape *> shapes;
    std::vector<std::string> filestring;
    std::vector<Vector> vectors;
    Object object;
};


#endif //RAYTRACER_OBJLOADER_H
