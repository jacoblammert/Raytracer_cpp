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
    resetImage();
}

void Scene::setCamera(Camera camera) {
    this->camera = camera;
    resetImage();
}

void Scene::addObject(Object object) {

}

void Scene::addShape(Shape *shape) {
    shapes.push_back(shape);
}

void Scene::render() {

    int r = 0, g = 0, b = 0;
    float mindistance, distance;
    Ray ray = Ray(Vector(), Vector());
    Vector color = Vector();
    Vector HitPoint = Vector();
    Vector HitNormal = Vector();
    int hit;

    Chronometer chr = Chronometer("Raytracer");

    for (int y = 0; y < camera.getHeight(); ++y) {

        std::cout << "Percentage: " << (y * 100.0f) / (float) camera.getHeight() << " %" << std::endl;

        for (int x = 0; x < camera.getWidth(); ++x) {

            mindistance = INFINITY - 1;
            hit = -1;
            ray = camera.generateRay(x, y);


            omp_set_num_threads(4); // new threads for every pixel => slower = bad
#pragma omp parallel for
            for (int i = 0; i < size(shapes); ++i) { // more effiecient with bounding boxes
                if (shapes[i]->getIntersectVec(ray, HitPoint, HitNormal,mindistance,hit,i)) { // bool if ray intersects the Object

                }
            }


            //lightcalculations / colorcalculations



            r = 0;
            g = 0;
            b = 0;
            if (hit != -1 && hit < size(shapes)) {
                color = shapes[hit]->getRgb();
                r = (int) color.getX();
                g = (int) color.getY();
                b = (int) color.getZ();
            }
            Pixel[y][x] = Vector((float) r, (float) g, (float) b);

        }
    }
    chr.stop();
}

Camera Scene::getCamera() {
    return camera;
}

void Scene::resetImage() {

    std::vector<Vector> vec;
    vec.assign(camera.getWidth(), Vector());
    Pixel.assign(camera.getHeight(), vec);
}

void Scene::drawImage() {

    Chronometer chr = Chronometer("Image");

    std::ofstream img("picture.ppm");
    img << "P3" << std::endl << camera.getWidth() << " " << camera.getHeight() << std::endl << "255" << std::endl;

    for (int i = 0; i < size(Pixel); ++i) {
        for (int j = 0; j < size(Pixel[i]); ++j) {

            img << Pixel[i][j].getX() << " " << Pixel[i][j].getY() << " " << Pixel[i][j].getZ() << std::endl;
        }
    }
    chr.stop();
}
