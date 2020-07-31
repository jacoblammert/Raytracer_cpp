//
// Created by Jacob on 22.04.2020.
//

#include "BoundingBox.h"
#include "../geometry/Plane.h"

#include <utility>
#include <iostream>
#include <cmath>
//#include <map>
//#include <algorithm>

BoundingBox::BoundingBox() {

}

BoundingBox::BoundingBox(std::vector<Shape *> shapes) {

    depth = 0;
    this->shapes = std::move(shapes);
    setMinMaxMid();

    box = Box(minXminYminZ, maxXmaxYmaxZ);
    if (!this->shapes.empty()) {
        split();
    }
}

BoundingBox::BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, int depth) {
    this->depth = depth + 1;
    this->minXminYminZ = minXminYminZ;
    this->maxXmaxYmaxZ = maxXmaxYmaxZ; // build needs to be called later otherwise it is the last box

    box = Box(minXminYminZ, maxXmaxYmaxZ);
}


BoundingBox::BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, std::vector<Shape *> shapes, int depth) {
    this->depth = depth + 1;
    this->minXminYminZ = minXminYminZ;
    this->maxXmaxYmaxZ = maxXmaxYmaxZ;

    box = Box(minXminYminZ, maxXmaxYmaxZ);

    this->shapes = std::move(shapes);
    if (!this->shapes.empty()) {
        build();
    }
}

void BoundingBox::getIntersectedShape(Ray ray, Shape &shape, Vector &Hitpoint, Vector &Hitnormal, float &distance,
                                      bool &hit) {

    for (int i = 0; i < boxes.size(); ++i) {
        if (boxes[i].box.getIntersect(ray)) {
            boxes[i].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
        }
    }

    if (!shapes.empty()) {
        int hitid = -1;
        int newid = 2;
        float oldDist = distance;
        for (int i = 0; i < shapes.size(); ++i) {
            shapes[i]->getIntersectVec(ray, Hitpoint, Hitnormal, distance, hitid, newid);
            if (distance < oldDist) { // Test, if new already hit shape is closer and set shape to shape and hit to true
                shape = *shapes[i];
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

    box = Box(minXminYminZ, maxXmaxYmaxZ); /// needs to be renewed since the values changed

    if (depth < 14 && shapes.size() > 30) {
        split();
    }
}


void BoundingBox::setMinMaxMid() {
    minXminYminZ = Vector(INFINITY, INFINITY,
                          INFINITY); // need to be set to opposite values to get the correct ones for all the shapes inside this box
    maxXmaxYmaxZ = Vector(-INFINITY, -INFINITY,
                          -INFINITY); // need to be set to opposite values to get the correct ones for all the shapes inside this box

    median = Vector();

    Vector medianShape = {};
    for (auto &shape : shapes) {
        getMin(shape->getMin());
        getMax(shape->getMax());
        medianShape = shape->getMedian();
        median = median + medianShape;
    }
    median.scale(1.0f / (float) std::size(shapes));

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

    Vector min = {};
    Vector max = {};


    BoundingBox left = BoundingBox({}, {}, depth);
    BoundingBox right = BoundingBox({}, {}, depth);
    BoundingBox middle = BoundingBox({}, {}, depth);

    boxes.push_back(right);
    boxes.push_back(left);
    boxes.push_back(middle); /// This is a smaller box which will contain every shape "cut" in half by the seperation



    for (int i = 0; i < shapes.size(); ++i) {
        if (!dynamic_cast<Plane *>(shapes[i])) { // Planes stay in the first Box, because they are really big
            min = shapes[i]->getMin();
            max = shapes[i]->getMax();

            if (min.get(axis) > median.get(axis)) { // right box
                boxes[0].addShape(shapes[i]);
            } else if (max.get(axis) < median.get(axis)) { // left box
                boxes[1].addShape(shapes[i]);
            } else {
                boxes[2].addShape(shapes[i]);
            }
            shapes.erase(shapes.begin() + i);
            i--;
        }
    }

    boxes[0].build();
    boxes[1].build();
    boxes[2].build();

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
        for (int i = 0; i < boxes.size(); ++i) {
            boxes[i].print(depthToPrint);
        }
    }
}

Vector BoundingBox::getMedian() {
    return median;
}

bool BoundingBox::VectorInsideBox(Vector test) { // test, if a Vector is inside of the first Box
    return (minXminYminZ.get(0) <= test.get(0) && test.get(0) <= maxXmaxYmaxZ.get(0) &&
            minXminYminZ.get(1) <= test.get(1) && test.get(1) <= maxXmaxYmaxZ.get(1) &&
            minXminYminZ.get(2) <= test.get(2) && test.get(2) <= maxXmaxYmaxZ.get(2));
}

Vector BoundingBox::getMin() {
    return minXminYminZ;
}

Vector BoundingBox::getMax() {
    return maxXmaxYmaxZ;
}









