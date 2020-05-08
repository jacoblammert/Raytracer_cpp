//
// Created by Jacob on 08.05.2020.
//

#ifndef RAYTRACER_SKYBOX_H
#define RAYTRACER_SKYBOX_H


#include <string>
#include "../geometry/Color.h"
#include "../math/Vector.h"
#include "../rendering/Image.h"
#include "../geometry/Box.h"

class Skybox {
public:
    Skybox();
    //Skybox(std::string name);

    Color getColor(Vector direction);

private:
    std::string name;

    Image top = Image();
    Image bottom = Image();
    Image left = Image();
    Image right = Image();
    Image front = Image();
    Image back = Image();

    Box skybox = {{0, 0, 0}, 2, 2, 2};

};


#endif //RAYTRACER_SKYBOX_H
