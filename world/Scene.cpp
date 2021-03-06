//
// Created by Jacob on 19.04.2020.
//

#include <iostream>
#include <ostream>
#include <fstream>
#include <omp.h>
#include "Scene.h"
#include "../debug/Timer.h"
#include "BoundingBox.h"
#include "../rendering/Renderer.h"
#include "../rendering/Image.h"

Scene::Scene(const std::vector<Light *> &lights) : lights(lights) {

}

Scene::Scene(Camera camera, const std::vector<Light *> &lights) : lights(lights) {
    this->camera = camera;

}

void Scene::setCamera(Camera camera) {
    this->camera = camera;
}

void Scene::addShapes(std::vector<Shape *> shapesToAdd) {
    shapes.insert(shapes.end(), shapesToAdd.begin(), shapesToAdd.end());
}

void Scene::addShape(Shape *shape) {
    shapes.push_back(shape);
}

//void Scene::addLight(Light *light) {
//    lights.push_back(light);
//}

void Scene::render() {

    Timer timer = Timer("Raytracer");

    omp_set_num_threads(128); //64

    int progress = 0;

    image = Image("picture", camera.getWidth(), camera.getHeight());

    //Renderer renderer = Renderer(skybox);



#pragma omp parallel for schedule(dynamic,2)// collapse(2)

//float error = 0.0f;

//#pragma omp target teams distribute parallel for// reduction(max:error)/*private(x,y)/*schedule(dynamic,2)*/ //collapse(2)
    for (int x = 0; x < camera.getWidth(); ++x) {
/*/
        Camera camera1 = camera; // local copies for parallelization
        Renderer renderer1 = Renderer(skybox,boundingBox);
/**/
        Renderer renderer1 = Renderer(skybox,boundingBox);
        renderer1.setLights(lights);
        Camera camera1 = camera;
        for (int y = 0; y < camera.getHeight(); ++y) {
            image.setPixel(x, y, renderer1.getColor(camera1.generateRay(x, y), 0));
        }
        //progress++;
        //if (progress % 10 == 0) {
        //    std::cout << "Progress: " << (float) (100 * progress) / (float) camera.getWidth() << "% Thread: "
        //              << omp_get_thread_num() << std::endl;
        //}
    }

    timer.stop();
}

Camera Scene::getCamera() {
    return camera;
}


void Scene::drawImage(int number) {
    image.saveImage(number);
}

void Scene::buildBoundingBox() {
    std::cout << "Size shapes: " << shapes.size() << std::endl;
    std::cout << "Size lights: " << lights.size() << std::endl;

    Timer timerb = Timer("BoundingBox");
    this->boundingBox = new BoundingBox(this->shapes);
    timerb.stop();
    //this->boundingBox.print(3);
}

void Scene::setSkybox(Skybox *skybox) {
    this->skybox = skybox;
}


