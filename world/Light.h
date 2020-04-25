//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "../math/Vector.h"
#include "../geometry/Color.h"

class Light {
public:
    Light();

    Light(Vector position, Color color);

    Light(Vector position, Color color, float intensity);

    float getIntensity();

    Vector getPosition();

    void setPosition(Vector position);
    void setIntensity(float intensity);

    Color getColor();

    void setColor(Color color);

private:
    float intensity;
    Vector position;
    Color color;
};


#endif //RAYTRACER_LIGHT_H
