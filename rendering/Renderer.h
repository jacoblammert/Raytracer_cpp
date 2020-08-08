//
// Created by Jacob on 26.04.2020.
//

#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H


#include <vector>
#include "../geometry/Color.h"
#include "../math/Ray.h"
#include "../world/Light.h"
#include "../world/BoundingBox.h"
#include "Image.h"
#include "../world/Skybox.h"

class Renderer {
public:
    Renderer();

    Renderer(Skybox *skybox,BoundingBox* boundingBox);


    Color getColor(Ray ray, int depth, std::vector<Light *> lights);

    bool castShadowRay(Ray ray, float distance);

    void setSkybox(Skybox *skybox);

    void setBoundingBox(BoundingBox *boundingBox);

    //Color getSkybox(Vector vector);

    Color getRefractedColor(Ray ray, Vector HitPoint, Vector HitNormal, Vector Normal, int depth,
                            std::vector<Light *> lights, Shape *shape);

    Color getReflectedColor(Ray ray, Vector HitPoint, Vector HitNormal, Vector Normal, int depth,
                            std::vector<Light *> lights, Shape *shape);

    float randomFloat(float range);

private:
    Skybox *skybox;
    BoundingBox* boundingBox;
};


#endif //RAYTRACER_RENDERER_H
