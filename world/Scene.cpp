//
// Created by Jacob on 19.04.2020.
//

#include <iostream>
#include <ostream>
#include <fstream>
#include <omp.h>
#include "Scene.h"
#include "../debug/Chronometer.h"
#include "BoundingBox.h"

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

void Scene::addShapes(std::vector<Shape *> shapesToAdd) {

    //std::vector<Shape*> shapes2 = object.getTriangles();

    shapes.insert(shapes.end(), shapesToAdd.begin(), shapesToAdd.end());
    /*/
    for (int i = 0; i < std::size(shapesToAdd); ++i) {
        std::cout << "Google" << std::endl;
        shapes.push_back(shapesToAdd[i]);
        shapesToAdd[i]->print();

        //addShape(shapes2[i]);

    }/**/

    //shapes.insert(shapes.end(), shapes2.begin(), shapes2.end());
}

void Scene::addShape(Shape *shape) {
    shapes.push_back(shape);
}

void Scene::render() {

    std::cout << "Size shapes: " << std::size(shapes) << std::endl;

    Chronometer chrb = Chronometer("BoundingBox");
    boundingBox = BoundingBox(shapes);
    //boundingBox.print(3);
    chrb.stop();

    Chronometer chr = Chronometer("Raytracer");

    omp_set_num_threads(4);

    // 1 Thread: 1.641s, 2 Threads: 1.244s, 4 Threads: 1.188s, 8 Threads: 1.304s, 16 Threads: 1.393s (666 * 375)Pixel
    // 1 Thread: 6.458s, 2 Threads: 4.741s, 4 Threads: 4.515s, 8 Threads: 5.065s, 16 Threads: 5.384s (1333 * 750)Pixel
    // 1 Thread and no Bounding Box: 4.3s (1333 * 750)Pixel = better with a total of 11 shapes, but worse with several thousands

#pragma omp parallel for

    for (int y = 0; y < camera.getHeight(); ++y) {

        //chr.getTime();
        std::cout << "Percentage: " << ((float) y * 100.0f) / (float) camera.getHeight() << " %" << std::endl;
        for (int x = 0; x < camera.getWidth(); ++x) {

            float mindistance = INFINITY - 1;
            int hit = -1;
            Ray ray = {{},
                       {}};
            Vector HitPoint = {};
            Vector HitNormal = {};
            Vector color = {};

            std::vector<Shape *> shapes2 = {};

#pragma omp critical
            {
                ray = camera.generateRay(x, y);

                shapes2 = boundingBox.getIntersectVec(ray);
            }

            for (int i = 0; i < size(shapes2); ++i) {
                if (shapes2[i]->getIntersectVec(ray, HitPoint, HitNormal, mindistance, hit,
                                                i)) { // bool if ray intersects the Object // hit & other values set for lighting & stuff
                }
            }


            //lightcalculations / colorcalculations


#pragma omp critical
            {
                int r = 0;
                int g = 0;
                int b = 0;
                if (-1 < hit && hit < size(shapes2)) {
                    color = shapes2[hit]->getRgb();
                    r = (int) color.getX();
                    g = (int) color.getY();
                    b = (int) color.getZ();
                }
                Pixel[y][x] = Vector((float) r, (float) g, (float) b);
            }
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
