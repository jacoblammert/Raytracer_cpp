//
// Created by Jacob on 29.04.2020.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H


#include <vector>
#include "../geometry/Color.h"

class Image {
public:

    Image();

    Image(std::string filename);

    Image(std::string filename, int width, int height);

    void setPixel(int x, int y, Color color);

    void loadImage();

    void readImage();

    void constructImage();

    void resetImage();

    void saveImage(int number);

    void printR();

    void printG();

    void printB();

    Color getPixel(float x, float y);

private:
    std::vector<std::vector<Color>> image;
    int width, height;
    std::string filename;
    std::vector<std::string> filestring;
};


#endif //RAYTRACER_IMAGE_H
