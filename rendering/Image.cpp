//
// Created by Jacob on 29.04.2020.
//

#include <fstream>
#include <string>
#include <iostream>
#include "Image.h"

Image::Image() {

}

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


    //std::cout<<"Name: "<<filename<<std::endl;
    //std::cout<<"Arraysize: "<<filestring.size()<<std::endl;

    //for (int j = 0; j < filestring.size(); ++j) {
    //    std::cout<<filestring[j]<<std::endl;
    //}


    int x = 0;
    int y = 0;

    for (int i = 0; i < filestring.size(); ++i) {
        if (filestring[0] == "P3") {

            if (i < 4) {
                if (i == 1) {
                    //std::cout<<"Testtesttesttest"<<std::endl;
                    width = std::stoi(filestring[i]);
                    //std::cout<<"Width image: "<<width<<std::endl;
                } else if (i == 2) {
                    height = std::stoi(filestring[i]);
                    //std::cout<<"Height image: "<<height<<std::endl;
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
    //std::cout<<"Width image: "<<width<<std::endl;
    //std::cout<<"Height image: "<<height<<std::endl;
    //std::cout<<"Width image: "<<filestring[1]<<std::endl;
    //std::cout<<"Height image: "<<filestring[2]<<std::endl;

}

void Image::saveImage(int number) {

    std::cout << "Saving Image: " << number << std::endl;

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

    if (/*!image.empty() && !image[(int)(y * height)].empty() &&*/ 0 < x && 0 < y) {
        x = x * (float) this->width;
        y = y * (float) this->height;

        x = ((int) x) % (int) this->width;
        y = ((int) y) % (int) this->height;

        return image[y][x];
    } else{
        //std::cout<<"Image is empty, or x < 0 or y < 0! " << std::endl;
        return {0,0,0};
    }
}

void Image::resetImage() {
    std::vector<Color> vec;
    vec.assign(width, Color());
    image.assign(height, vec);
}

void Image::printR() {
    std::cout<<"RED:\n";
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[i].size(); ++j) {
            std::cout << image[i][j].getR()<< " ";
        }
        std::cout<<std::endl;
    }
}

void Image::printG() {
    std::cout<<"GREEN:\n";
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[i].size(); ++j) {
            std::cout << image[i][j].getG()<< " ";
        }
        std::cout<<std::endl;
    }
}

void Image::printB() {
    std::cout<<"BLUE:\n";
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[i].size(); ++j) {
            std::cout << image[i][j].getB()<< " ";
        }
        std::cout<<std::endl;
    }
}








