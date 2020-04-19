//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "../math/Vector.h"

class Light {
public:
    Light();
    Light(Vector position, Vector color);
    Vector getPosition();
    Vector getColor();
private:
    Vector position;
    Vector color;
};


#endif //RAYTRACER_LIGHT_H
