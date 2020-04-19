//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


class Light {
public:
    Light();
    Light(Vector position, vector color);
private:
    Vector position;
    Vector color;
};


#endif //RAYTRACER_LIGHT_H
