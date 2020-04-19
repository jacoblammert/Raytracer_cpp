//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "Object.h"
#include "Camera.h"
#include "../geometry/Shape.h"
#include <vector>
//#include "../geometry/Shape.h"

class Scene {
public:
    Scene();
    explicit Scene(Camera camera);


    void setCamera(Camera camera);
    void addObject(Object object); // many triangles of a single object
    void addShape(Shape *shape); // different shapes like spheres, triangles or cubes
    void render();
    Camera getCamera();


private:
    Camera camera;
    //BoundingBox (Object array)
    std::vector<Shape*> shapes;
};


#endif //RAYTRACER_SCENE_H
