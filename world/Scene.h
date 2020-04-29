//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "../obj/Object.h"
#include "Camera.h"
#include "../geometry/Shape.h"
#include "Light.h"
#include "BoundingBox.h"
#include "../rendering/Image.h"
#include <vector>

class Scene {
public:
    Scene(const std::vector<Light *> &lights);

    explicit Scene(Camera camera, const std::vector<Light *> &lights);


    void setCamera(Camera camera);

    void addShapes(std::vector<Shape *> shapes); // many triangles of a single object
    void addShape(Shape *shape); // different shapes like spheres, triangles or cubes
    void addLight(Light *lights); // many triangles of a single object
    void render();

    Camera getCamera();

    void buildBoundingBox();

    void drawImage(int number);

    //static Image background = Image("");

private:
    Camera camera;
    BoundingBox boundingBox;
    std::vector<Shape *> shapes;
    const std::vector<Light *> &lights;
    Image image = Image("picture");
};


#endif //RAYTRACER_SCENE_H
