//
// Created by Jacob on 24.04.2020.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include <vector>
#include "../math/Vector.h"
#include "../math/Ray.h"
#include "../world/Light.h"

class Material { /// struct would be better
public:
    Material();

    Material(Color color);

    Material(Color color, float roughness, float glossy, float transparency);

    Material(Color color, float roughness, float glossy, float transparency, float refractiveIndex);

    float getRoughness();

    void setRoughness(float roughness);

    float getGlossy();

    void setGlossy(float glossy);

    float getTransparency();

    void setTransparency(float transparency);

    float getRefractiveIndex();

    void setRefractiveIndex(float refractiveIndex);

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
