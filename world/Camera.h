//
// Created by Jacob on 14.04.2020.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "../math/Ray.h"

class Camera {
public:
    Camera();
    Camera(Vector position, Vector direction, int width, int height, float dist);
    void update();
    Ray generateRay(int x, int y);
    void setPosition(Vector pos);
    void lookAt(Vector pos);
    void setDist(float dist);
    int getWidth();
    int getHeight();

    void setNumberOfPixel(int pixel);
    void setWidthToHeight(float wToH);
    void print();

private:
    Vector position;
    Vector direction;
    Vector up = Vector(0,0,1);
    Vector right;
    Vector top;
    float Fov;
    int width;
    int height;
    float dist; // Camera plane distance from the Position
    int pixel;
    float wToH;
};


#endif //RAYTRACER_CAMERA_H
