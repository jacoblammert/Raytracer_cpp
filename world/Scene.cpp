//
// Created by Jacob on 19.04.2020.
//

#include <iostream>
#include <ostream>
#include <fstream>
#include "Scene.h"
#include "../Debug/Chronometer.h"

Scene::Scene() {

}

Scene::Scene(Camera camera) {
    this->camera = camera;
    Light light = Light();
}

void Scene::setCamera(Camera camera) {
    this->camera = camera;
}

void Scene::addObject(Object object) {

}

void Scene::addShape(Shape *shape) {
    shapes.push_back(shape);
}

void Scene::render() {

    int width = camera.getWidth(), height = camera.getHeight();
    int r = 0, g = 0, b = 0;
    float mindistance, distance;
    Ray ray = Ray(Vector(), Vector());
    Vector color = Vector();
    Vector HitPoint = Vector();
    Vector HitNormal = Vector();
    int hit;

    Chronometer chr = Chronometer("Raytracer");

    std::ofstream img("picture.ppm");
    img << "P3" << std::endl << width << " " << height << std::endl << "255" << std::endl;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mindistance = INFINITY - 1;
            hit = -1;
            ray = camera.generateRay(x, y);

            for (int i = 0; i < size(shapes); ++i) { // more effiecient with bounding boxes

                if (shapes[i]->getIntersectVec(ray,HitPoint,HitNormal)){ // bool if ray intersects the Object

                    distance = (ray.getPos()-HitPoint).getLength();
                    if (distance < mindistance){
                        mindistance = distance;
                        hit = i;
                    }
                }
            }

            //lightcalculations / colorcalculations




            if (hit != -1){
                color = shapes[hit]->getRgb();
                r = (int) color.getX();
                g = (int) color.getY();
                b = (int) color.getZ();
            }
            img << r << " " << g << " " << b << std::endl;
            r = 0;
            g = 0;
            b = 0;
        }
    }
    chr.stop();
}

Camera Scene::getCamera() {
    return camera;
}
