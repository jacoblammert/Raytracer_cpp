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

std::vector<Shape *> BoundingBox::getIntersectVec(Ray ray) {

    std::vector<Shape *> returnshapes;

    if (box.getIntersect(ray)) {
        if (boxes.empty()) {
            return shapes;
        }
        for (auto &boxe : boxes) {
            std::vector<Shape *> shapes2 = boxe.getIntersectVec(ray);
            returnshapes.insert(returnshapes.end(), shapes2.begin(), shapes2.end());
        }
        if (!shapes.empty()) {
            returnshapes.insert(returnshapes.end(), shapes.begin(), shapes.end());
        }

    }
    //if (this->depth == 0) {
    //returnshapes = removeDoubles(returnshapes);
    //}

    return returnshapes;
}

/**
 * removes all the doubles from the array to avoid testing the same shape twice
 * @param shapesToClear input shapes hit by the ray
 * @return output array without the same shape twice
 */
std::vector<Shape *> BoundingBox::removeDoubles(std::vector<Shape *> shapesToClear) {
    for (int i = (int) shapesToClear.size() - 1; i > 0; i--) {
        for (int j = (int) i - 1; j > 0; j--) {
            if (shapesToClear[i] == shapesToClear[j]) {
                shapesToClear.erase(shapesToClear.begin() + i);
                i--;
                j--;
            }
        }
    }
    return shapesToClear;
}


/**
 * Only splits the box, if either the depth is smaller than 4
 * or if there are more than 10 shapes inside the box
 */
void BoundingBox::build() {
    if (/**/depth < 16 && /**/shapes.size() > 80) {
        setMid();
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

void BoundingBox::setMid() {

    median = Vector();
    Vector medianShape = {};
    for (int i = 0; i < shapes.size(); ++i) {
        medianShape = shapes[i]->getMedian();
        median = median + medianShape;
    }

    median.scale(1.0f / std::size(shapes));
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

    for (int i = 0; i < shapes.size(); ++i) {
        if (!dynamic_cast<Plane *>(shapes[i])) { // Planes stay in the first Box, because they are really big
            min = shapes[i]->getMin();
            max = shapes[i]->getMax();

            if (min.get(axis) > median.get(axis)) { // right box
                boxes[0].addShape(shapes[i]);
            } else if (max.get(axis) < median.get(axis)) { // left box
                boxes[1].addShape(shapes[i]);
            } else {
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
    std::cout << "MidX: " << median.get(0) << " MidY: " << median.get(1) << " MidZ: " << median.get(2) << std::endl
              << std::endl;
    if (depthToPrint > 0) {
        depthToPrint--;
        for (int i = 0; i < boxes.size(); ++i) {
            boxes[i].print(depthToPrint);
        }
    }
}





