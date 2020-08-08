//
// Created by Jacob on 22.04.2020.
//

#include "BoundingBox.h"
#include "../geometry/Plane.h"

#include <utility>
#include <iostream>
#include <cmath>

BoundingBox::BoundingBox() {

}

BoundingBox::BoundingBox(std::vector<Shape *> shapes) {

    depth = 0;
    this->shapes = std::move(shapes);
    setMinMaxMid();


    if (!this->shapes.empty()) {
        split();
    }
}

BoundingBox::BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, int depth) :
        minXminYminZ{minXminYminZ}, maxXmaxYmaxZ{maxXmaxYmaxZ}, depth{++depth}, box{minXminYminZ, maxXmaxYmaxZ} {

}


BoundingBox::BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, std::vector<Shape *> shapes, int depth) :
        minXminYminZ{minXminYminZ}, maxXmaxYmaxZ{maxXmaxYmaxZ}, depth{++depth}, box{minXminYminZ, maxXmaxYmaxZ} {

    this->shapes = std::move(shapes);
    if (!this->shapes.empty()) {
        build();
    }
}

void BoundingBox::getIntersectedShape(Ray ray, Shape &shape, Vector &Hitpoint, Vector &Hitnormal, float &distance,
                                      bool &hit) {

    for (auto &boxe : boxes) {
        if (boxe.box.getIntersect(ray)) {
            boxe.getIntersectedShape(ray, shape, Hitpoint,Hitnormal, distance, hit);
        }
    }

    if (!shapes.empty()) {
        float oldDist = distance;
        for (auto &shapehit : shapes) {
            shapehit->getIntersectVec(ray, Hitpoint, Hitnormal, distance);
            if (distance < oldDist) { // Test, if new already hit shape is closer and set shape to shape and hit to true
                shape = *shapehit;
                hit = true;
            }
        }
    }
}


/**
 * Only splits the box, if either the depth is smaller than 4
 * or if there are more than 10 shapes inside the box
 */
void BoundingBox::build() {

    setMinMaxMid();

    if (depth < 20 && shapes.size() > 8) {
        split();
    }
}


void BoundingBox::setMinMaxMid() {
    minXminYminZ = Vector(INFINITY, INFINITY,
                          INFINITY); // need to be set to opposite values to get the correct ones for all the shapes inside this box
    maxXmaxYmaxZ = Vector(-INFINITY, -INFINITY,
                          -INFINITY); // need to be set to opposite values to get the correct ones for all the shapes inside this box

    median = Vector();

    Vector medianShape;

    for (auto &shape : shapes) {
        getMin(shape->getMin());
        getMax(shape->getMax());

        medianShape = shape->getMedian();
        median = median + medianShape;
    }
    median.scale(1.0f / (float) std::size(shapes));

    box = Box{minXminYminZ, maxXmaxYmaxZ};
}

void BoundingBox::getMin(Vector shapemin) {
    for (int i = 0; i < 3; ++i) {
        if (minXminYminZ.get(i) > shapemin.get(i)) {
            minXminYminZ.set(i, shapemin.get(i));
        }
    }
}

void BoundingBox::getMax(Vector shapemax) {
    for (int i = 0; i < 3; ++i) {
        if (maxXmaxYmaxZ.get(i) < shapemax.get(i)) {
            maxXmaxYmaxZ.set(i, shapemax.get(i));
        }
    }
}

void BoundingBox::split() {

    int axis;
    Vector size = maxXmaxYmaxZ - minXminYminZ; // max of the Box in terms of width, height, depth


    if (size.getX() > size.getY() && size.getX() > size.getZ()) { // X is largest
        axis = 0; // x split
    } else if (size.getY() > size.getX() && size.getY() > size.getZ()) { // Y is lagest
        axis = 1; // y split
    } else { // Z is largest
        axis = 2; // z split
    }

    // 1 0   0
    // 0 1   1
    // 0 0   2


    BoundingBox left = BoundingBox({}, {}, depth);
    BoundingBox right = BoundingBox({}, {}, depth);

    boxes.push_back(right);
    boxes.push_back(left);


    for (int i = (int) shapes.size() - 1; 0 < i; --i) {
        if (!dynamic_cast<Plane *>(shapes[i])) { // Planes stay in the first Box, because they are really big

            if (shapes[i]->getMedian().get(axis) > median.get(axis)) { // right
                boxes[0].addShape(shapes[i]); // right
            } else {
                boxes[1].addShape(shapes[i]);
            }

            shapes.erase(shapes.begin() + i);
        }
    }

    for (auto &boxe : boxes) {
        boxe.build();
    }
}

void BoundingBox::addShape(Shape *shape) {
    shapes.push_back(shape);
}

void BoundingBox::print(int depthToPrint) {
    std::cout << std::endl << "Depth: " << this->depth << std::endl;
    std::cout << "Size: " << std::size(shapes) << std::endl;
    std::cout << "MinX: " << minXminYminZ.get(0) << " MinY: " << minXminYminZ.get(1) << " MinZ: " << minXminYminZ.get(2)
              << std::endl;
    std::cout << "MaxX: " << maxXmaxYmaxZ.get(0) << " MaxY: " << maxXmaxYmaxZ.get(1) << " MaxZ: " << maxXmaxYmaxZ.get(2)
              << std::endl;
    std::cout << "MidX: " << median.get(0) << " MidY: " << median.get(1) << " MidZ: " << median.get(2) << std::endl
              << std::endl;
    if (depthToPrint > 0) {
        depthToPrint--;
        for (auto &boxe : boxes) {
            boxe.print(depthToPrint);
        }
    }
}

Vector BoundingBox::getMedian() {
    return median;
}

Vector BoundingBox::getMin() {
    return minXminYminZ;
}

Vector BoundingBox::getMax() {
    return maxXmaxYmaxZ;
}
