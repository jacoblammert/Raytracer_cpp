//
// Created by Jacob on 19.04.2020.
//

#include <iostream>
#include <ostream>
#include <fstream>
#include <omp.h>
#include "Scene.h"
#include "../debug/Chronometer.h"

Scene::Scene() {

}

Scene::Scene(Camera camera) {
    this->camera = camera;
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

            //#pragma omp parallel for num_threads(2) collapse(2)
            //{

            omp_set_num_threads(4); // new threads for every pixel => slower = bad
#pragma omp parallel for
            for (int i = 0; i < size(shapes); ++i) { // more effiecient with bounding boxes
                if (shapes[i]->getIntersectVec(ray, HitPoint, HitNormal)) { // bool if ray intersects the Object
#pragma omp critical
                    {
                        distance = (ray.getPos() - HitPoint).getLength();
                        if (distance < mindistance) {
                            mindistance = distance;
                            hit = i;
                        }
                    }
                }
            }
            //}

            //lightcalculations / colorcalculations



//#pragma omp critical
            //{
            if (hit != -1) {
                color = shapes[hit]->getRgb();
                r = (int) color.getX();
                g = (int) color.getY();
                b = (int) color.getZ();
            }

            img << r << " " << g << " " << b << std::endl;
            //}
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
