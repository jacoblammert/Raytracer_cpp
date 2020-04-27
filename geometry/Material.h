//
// Created by Jacob on 24.04.2020.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include <vector>
#include "../math/Vector.h"
#include "../math/Ray.h"
#include "../world/Light.h"

class Material {
public:
    Material();

    Material(Color color);

    Material(Color color, float roughness, float glossy, float transparency);

    Material(Color color, float roughness, float glossy, float transparency, float refractiveIndex);

    float getRoughness();

    float getGlossy();

    float getTransparency();

    float getRefractiveIndex();

    void setColor(Color color);

    Color getColor();

private:
    float roughness;
    float glossy;
    float transparency;
    float refractiveIndex;
    Color color;

};


#endif //RAYTRACER_MATERIAL_H
