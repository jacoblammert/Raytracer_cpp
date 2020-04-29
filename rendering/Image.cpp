//
// Created by Jacob on 29.04.2020.
//

#include <fstream>
#include <string>
#include <iostream>
#include "Image.h"

Image::Image(std::string filename) {
    this->filename = filename;
}

Image::Image(std::string filename, int width, int height) {
    this->filename = filename;
    this->width = width;
    this->height = height;
    resetImage();
}

void Image::setPixel(int x, int y, Color color) {
    //color.scale(255);
    //color.setRange(0,255);
    image[y][x] = color;
}

void Image::loadImage() {
    std::ifstream inputFile(filename);        // Input file stream object
    this->filestring = std::vector<std::string>();

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // using printf() in all tests for consistency
            //printf("%s", line.c_str());
            filestring.push_back(line);
        }
        file.close();
    }
    readImage();
}


void Image::readImage() {
    std::string token = " ";
    std::vector<std::string> result;
    for (int i = 0; i < filestring.size(); ++i) {

        while (!filestring[i].empty()) {
            int index = filestring[i].find(token);

            if (index != std::string::npos) {
                result.push_back(filestring[i].substr(0, index));
                filestring[i] = filestring[i].substr(index + token.size());
                if (filestring[i].empty())
                    result.push_back(filestring[i]);
            } else {
                result.push_back(filestring[i]);
                filestring[i] = "";
            }
        }
    }
    filestring = result;
    constructImage();
}

void Image::constructImage() {

    int x = 0;
    int y = 0;

    for (int i = 0; i < filestring.size(); ++i) {
        if (filestring[i] == "P3") {

            if (i < 4) {
                if (i == 1) {
                    width = std::stoi(filestring[i]);
                } else if (i == 2) {
                    height = std::stoi(filestring[i]);
                    resetImage();
                }
            } else {
                if (i % 3 == 1) {

                    x = ((i - 2) / 3) % width;

                    image[y][x].setR(std::stoi(filestring[i]));
                } else if (i % 3 == 2) {
                    image[y][x].setG(std::stoi(filestring[i]));
                } else {
                    image[y][x].setB(std::stoi(filestring[i]));

                    if (((i - 1) / 3) % width == 0) {
                        y++;
                    }
                    y = y % height;
                }
            }
        }
    }
}

void Image::saveImage(int number) {

    std::ofstream img("picture" + std::to_string(number) + ".ppm");
    img << "P3" << std::endl << width << " " << height << std::endl << "255" << std::endl;


    for (auto &i : image) {
        for (auto &j : i) {

            j.scale(255);
            j.setRange(0, 255);

            img << (int) j.getR() << " " << (int) j.getG() << " " << (int) j.getB() << std::endl;
        }
    }
}


/**
 * gets a number from 0 to 1 for the percentage
 * @param x width percentage
 * @param y height percentage
 * @return Color at x and y
 */
Color Image::getPixel(float x, float y) {

    x = x * (float)width;
    y = y * (float)height;

    x =  ((int)x) % (int)width;
    y =  ((int)y) % (int)height;

    return image[y][x];
}

void Image::resetImage() {
    std::vector<Color> vec;
    vec.assign(width, Color());
    image.assign(height, vec);
}








