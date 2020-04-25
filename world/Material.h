//
// Created by Jacob on 24.04.2020.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include <vector>
#include "../math/Vector.h"
#include "../math/Ray.h"
#include "../geometry/Shape.h"
#include "Light.h"
#include "BoundingBox.h"

class Material {
public:
    Material();

    Material(Vector color);

    Material(Vector color, float roughness, float glossy, float transparency);

    Material(Vector color, float roughness, float glossy, float transparency, float refractiveIndex);

    Vector getColor(Ray ray,int depth,Shape *shape, Vector *HitPoint, Vector *HitNormal, std::vector<Light *> lights,
                    BoundingBox *boundingBox);


    Vector castRay(int depth,Ray ray, BoundingBox *boundingBox, std::vector<Light *> lights);
    bool castShadowRay(Ray ray, BoundingBox *boundingBox,float distance);

private:
    float roughness;
    float glossy;
    float transparency;
    float refractiveIndex;
    Vector color;

};


#endif //RAYTRACER_MATERIAL_H
