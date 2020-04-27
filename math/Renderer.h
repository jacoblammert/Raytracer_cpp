//
// Created by Jacob on 26.04.2020.
//

#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H


#include <vector>
#include "../geometry/Color.h"
#include "Ray.h"
#include "../world/Light.h"
#include "../world/BoundingBox.h"

class Renderer {
public:
    Renderer();


    Color
    getColor(Ray ray, int depth, std::vector<Light *> lights,
             BoundingBox *boundingBox);

    bool castShadowRay(Ray ray, BoundingBox *boundingBox, float distance);

};


#endif //RAYTRACER_RENDERER_H
