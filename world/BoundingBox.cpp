//
// Created by Jacob on 22.04.2020.
//

#include "BoundingBox.h"
#include "../geometry/Plane.h"
#include "../geometry/Sphere.h"

#include <utility>
#include <iostream>

BoundingBox::BoundingBox() {

}

BoundingBox::BoundingBox(std::vector<Shape *> shapes) {
    depth = 0;
    this->shapes = std::move(shapes);
    setMinMaxMid();

    box = Box(minXminYminZ, maxXmaxYmaxZ);

    split();
}

BoundingBox::BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, int depth) {
    this->depth = depth + 1;
    this->minXminYminZ = minXminYminZ;
    this->maxXmaxYmaxZ = maxXmaxYmaxZ; // build needs to be called later

    box = Box(minXminYminZ, maxXmaxYmaxZ);
}


BoundingBox::BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, std::vector<Shape *> shapes, int depth) {
    this->depth = depth + 1;
    this->minXminYminZ = minXminYminZ;
    this->maxXmaxYmaxZ = maxXmaxYmaxZ;

    box = Box(minXminYminZ, maxXmaxYmaxZ);

    this->shapes = std::move(shapes);
    build();
}

/**
 * Only splits the box, if either the depth is smaller than 4
 * or if there are more than 10 shapes inside the box
 */
void BoundingBox::build() {
    if (depth < 2 && std::size(shapes) > 5) {
        setMid();
        split();
    }
}


std::vector<Shape *> BoundingBox::getIntersectVec(Ray ray) {

    std::vector<Shape *> returnshapes;

    if (box.getIntersect(ray)) {
        if (std::size(boxes) == 0) {
            return shapes;
        }
        for (int i = 0; i < std::size(boxes); ++i) {
            std::vector<Shape *> shapes2 = boxes[i].getIntersectVec(ray);
            returnshapes.insert(returnshapes.end(), shapes2.begin(), shapes2.end());
        }
        if(std::size(shapes) != 0){
            returnshapes.insert(returnshapes.end(), shapes.begin(), shapes.end());
        }

    }
    return returnshapes;
}

void BoundingBox::setMinMaxMid() {
    minXminYminZ = Vector(INFINITY, INFINITY,INFINITY); // need to be set to opposite values to get the correct ones for all the shapes inside this box
    maxXmaxYmaxZ = Vector(-INFINITY, -INFINITY,-INFINITY); // need to be set to opposite values to get the correct ones for all the shapes inside this box

    median = Vector();

    Vector medianShape = {};
    for (int i = 0; i < std::size(shapes); ++i) {
        getMin(shapes[i]->getMin());
        getMax(shapes[i]->getMax());
        medianShape = shapes[i]->getMedian();
        median = median + medianShape;
    }
    median.scale(1.0f/ (float)std::size(shapes));
}

void BoundingBox::setMid() {

    median = Vector();
    Vector medianShape = {};
    for (int i = 0; i < std::size(shapes); ++i) {
        medianShape = shapes[i]->getMedian();
        median = median + medianShape;
    }

    median.scale(1.0f/std::size(shapes));
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

    int axis = depth % 3; // % 3 because we want to split across x = 0, y = 1 and z = 2

    Vector min = {};
    Vector max = {};

    Vector leftMax = maxXmaxYmaxZ;
    Vector rightMin = minXminYminZ;

    leftMax.set(axis, median.get(axis));
    rightMin.set(axis, median.get(axis));

    BoundingBox left = BoundingBox(minXminYminZ, leftMax, depth);
    BoundingBox right = BoundingBox(rightMin, maxXmaxYmaxZ, depth);

    boxes.push_back(right);
    boxes.push_back(left);

    for (int i = 0; i < std::size(shapes); ++i) {
        if (!dynamic_cast<Plane*>(shapes[i])) { // Planes stay in the first Box, because they are really big
            min = shapes[i]->getMin();
            max = shapes[i]->getMax();

            if (min.get(axis) > median.get(axis)) { // right box
                boxes[0].addShape(shapes[i]);
            } else if (max.get(axis) < median.get(axis)) { // left box
                boxes[1].addShape(shapes[i]);
            } else
            {
                boxes[0].addShape(shapes[i]); // object inside the cutting plane added to both arrays -> simpler
                boxes[1].addShape(shapes[i]); // object inside the cutting plane added to both arrays -> simpler
            }

            shapes.erase(shapes.begin() + i);
            i--;
        }
    }

    boxes[0].build(); // generate box
    boxes[1].build(); // generate box

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
    std::cout << "MidX: " << median.get(0) << " MidY: " << median.get(1) << " MidZ: " << median.get(2) << std::endl<< std::endl;
    if (depthToPrint > 0) {
        depthToPrint--;
        for (int i = 0; i < std::size(boxes); ++i) {
            boxes[i].print(depthToPrint);
        }
    }
}


