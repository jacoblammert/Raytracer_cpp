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
#include "../math/Renderer.h"

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
    shapes.insert(shapes.end(), shapesToAdd.begin(), shapesToAdd.end());
}

void Scene::addShape(Shape *shape) {
    shapes.push_back(shape);
}

void Scene::addLight(Light *light) {
    lights.push_back(light);
}

void Scene::render() {

    std::cout << "Size shapes: " << shapes.size() << std::endl;
    std::cout << "Size lights: " << lights.size() << std::endl;

    Chronometer chrb = Chronometer("BoundingBox");
    this->boundingBox = BoundingBox(this->shapes);
    //boundingBox.print(0);
    chrb.stop();

    Chronometer chr = Chronometer("Raytracer");

    omp_set_num_threads(64);

    int progress = 0;

#pragma omp parallel for
    for (int y = 0; y < camera.getHeight(); ++y) {
        for (int x = 0; x < camera.getWidth(); ++x) {

            Ray ray = {{},
                       {}};
            Renderer renderer = Renderer();
//#pragma omp critical
            //{
            Camera camera1 = camera;

            ray = camera1.generateRay(x, y);
            //}
            Pixel[y][x] = renderer.getColor(ray, 0, lights, &boundingBox);/**/
        }
        progress++;
        std::cout << "Progress: " << (float) (100 * progress) / (float) camera.getHeight() << "%" << std::endl;
    }

    chr.stop();

    //boundingBox.print(40);
}

Camera Scene::getCamera() {
    return camera;
}

void Scene::resetImage() {

    std::vector<Color> vec;
    vec.assign(camera.getWidth(), Color());
    Pixel.assign(camera.getHeight(), vec);
}

void Scene::drawImage() {

    Chronometer chr = Chronometer("Image");

    std::ofstream img("picture.ppm");
    img << "P3" << std::endl << camera.getWidth() << " " << camera.getHeight() << std::endl << "255" << std::endl;


    for (auto &i : Pixel) {
        for (auto &j : i) {

            j.scale(255);
            j.setRange(0, 255);

            img << (int) j.getR() << " " << (int) j.getG() << " " << (int) j.getB() << std::endl;
        }
    }
    chr.stop();
}


