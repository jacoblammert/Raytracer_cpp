//
// Created by Jacob on 08.05.2020.
//

#include <iostream>
#include "Skybox.h"
#include "../rendering/Image.h"
#include "../math/Vector.h"

Skybox::Skybox() {

    this->skybox = {{0, 0, 0}, 2, 2, 2};

    std::cout << "Loading Skybox!" << std::endl;

    this->top = Image("posy.ppm");
    this->top.loadImage();
    std::cout << "top loaded!" << std::endl;


    this->bottom = Image("negy.ppm");
    this->bottom.loadImage();
    std::cout << "bottom loaded!" << std::endl;

    this->left = Image("negx.ppm");
    this->left.loadImage();
    std::cout << "left loaded!" << std::endl;

    this->right = Image("posx.ppm");
    this->right.loadImage();
    std::cout << "right loaded!" << std::endl;


    this->front = Image("negz.ppm");
    this->front.loadImage();
    std::cout << "front loaded!" << std::endl;

    this->back = Image("posz.ppm");
    this->back.loadImage();
    std::cout << "back loaded!" << std::endl;

    std::cout << "Skybox loaded!" << std::endl;

}


Color Skybox::getColor(Vector direction) {
    Vector normal = {0, 0, 0};
    skybox.getIntersectVec(direction, normal); // hit + normal are important to get the direction of the ray


    float x = 0, y = 0;

    Color color = {};

    if (normal.get(0) == 1) { // left

        x = (1 + direction.get(1)) / 2;
        y = (1 + -direction.get(2)) / 2;
        return this->left.getPixel(x, y);


    } else if (normal.get(0) == -1) { // right

        x = (1 + -direction.get(1)) / 2;
        y = (1 + -direction.get(2)) / 2;
        return this->right.getPixel(x, y);


    } else if (normal.get(1) == 1) { // back

        x = (1 + -direction.get(0)) / 2;
        y = (1 + -direction.get(2)) / 2;
        return this->back.getPixel(x, y);

    } else if (normal.get(1) == -1) { // front

        x = (1 + direction.get(0)) / 2;
        y = (1 + -direction.get(2)) / 2;
        return this->front.getPixel(x, y);

    } else if (normal.get(2) == 1) { // Top

        x = (1 + -direction.get(0)) / 2;
        y = (1 + direction.get(1)) / 2;
        return this->top.getPixel(x, y);

    } else/*/ if (normal.get(2) == -1) /**/{ // Bottom

        x = (1 + -direction.get(0)) / 2;
        y = (1 + -direction.get(1)) / 2;
        return this->bottom.getPixel(x, y);
    }

    return color;
}
