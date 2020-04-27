//
// Created by Jacob on 24.04.2020.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include <vector>
#include "../math/Vector.h"
#include "../math/Ray.h"
#include "Light.h"

class Material {
public:
    Material();

    Material(Vector color);

    Material(Vector color, float roughness, float glossy, float transparency);

    Material(Vector color, float roughness, float glossy, float transparency, float refractiveIndex);

    float getRoughness();

    float getGlossy();

    float getTransparency();

    float getrefractiveIndex();

private:
    float roughness;
    float glossy;
    float transparency;
    float refractiveIndex;
    Vector color;

};


#endif //RAYTRACER_MATERIAL_H
