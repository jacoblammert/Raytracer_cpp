//
// Created by Jacob on 23.04.2020.
//

#include <ostream>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <string>
#include <utility>
#include "OBJLoader.h"
#include "Object.h"

OBJLoader::OBJLoader() {
}

OBJLoader::OBJLoader(std::string filename) {
    this->filename = std::move(filename);
}

void OBJLoader::setFilename(std::string filename) {
    this->filename = std::move(filename);
}

void OBJLoader::LoadOBJ() {
    this->shapes = std::vector<Shape *>();
    this->vectors = std::vector<Vector>();
    this->filestring = std::vector<std::string>();


    std::vector<int> numbers;
    std::ifstream inputFile(filename);        // Input file stream object

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // using printf() in all tests for consistency
            //printf("%s", line.c_str());
            filestring.push_back(line);
        }
        file.close();
    }

    split();
}

void OBJLoader::printOBJ() {
    for (int i = 0; i < filestring.size(); ++i) {
        std::cout << filestring[i] << std::endl;
    }
}


void OBJLoader::split() {

    std::string token = " ";
    std::vector<std::string> result;
    for (int i = 0; i < filestring.size(); ++i) {

        while (!filestring[i].empty()) {
            int index = filestring[i].find(token);

            if (index != std::string::npos) {
                result.push_back(filestring[i].substr(0, index));
                filestring[i] = filestring[i].substr(index + token.size());
                if (filestring[i].empty())
                    result.push_back(filestring[i]);
            } else {
                result.push_back(filestring[i]);
                filestring[i] = "";
            }
        }
    }
    filestring = result;
    buildObject();
}

Object OBJLoader::getObject() {
    return object;
}

void OBJLoader::buildObject() {

    int A, B, C;

    int count = 0;

    for (int i = 0; i < filestring.size(); ++i) {
        if (filestring[i] == "o") {
            if (count == 0) {
                objectname = filestring[i + 1];
                count++;
            }//new Object or abort
            else {
                Object a = Object(objectname, shapes);
                //objects.push_back(&a);
                object = a;
                objectname = filestring[i + 1];
                count++;
            }
        } else if (filestring[i] == "v") {
            Vector vector{std::stof(filestring[i + 1]),
                                   std::stof(filestring[i + 2]),
                                   std::stof(filestring[i + 3])};
            vectors.push_back(vector);
        } else if (filestring[i] == "f") {

            A = (int) std::stof(filestring[i + 1]);
            B = (int) std::stof(filestring[i + 2]);
            C = (int) std::stof(filestring[i + 3]);

            Triangle* triangle = new Triangle{vectors[A-1], vectors[B-1], vectors[C-1]};

            shapes.push_back(triangle);
        }
    }
    Object a = Object(objectname, shapes);
    //objects.push_back(&a);
    object = a;

}
