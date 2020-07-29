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

void BoundingBox::getIntersectedShape(Ray ray, Shape &shape, Vector &Hitpoint, Vector &Hitnormal, float &distance,
                                      bool &hit) {
    if (!box.getIntersect(ray)) {
        return;
    }

    //float BoxDistance = box.getDistance(ray);

    //if(BoxDistance < 0 || (INFINITY-2) <= BoxDistance){
    //    return;
    //}


    //if (this->boxes.size() == 2) {
        /*/
        if (VectorInsideBox(ray.getPos())) { // Ray is inside of the current Box
            if (VectorInsideBoxZero(ray.getPos())) { // Test, if Ray is inside one of the boxes
                boxes[0].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
                if (hit) {
                    return;
                } else {
                    boxes[1].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
                }
            } else {
                boxes[1].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
                if (hit) {
                    return;
                } else {
                    boxes[0].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
                }
            }
        } else {/**/
            //for (int i = 0; i < boxes.size(); ++i) {
            //    //// Loops over all Boxes and all Boxes inside the boxes and returns the closest shape hit
            //    /// can be made faster by checking the closest box first and then the next closest box
            //    /// in order to prevent testing even though the closest shape hit has been found already
            //    boxes[i].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
            //}
        //}

    //}


    //TODO sort the Boxes from the first hit by the ray to last box hit by ray (distance along ray) in order to check the closest boxes/ shapes first and be faster

    for (int i = 0; i < boxes.size(); ++i) {
        boxes[i].getIntersectedShape(ray, shape, Hitpoint, Hitnormal, distance, hit);
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
 * Only splits the box, if either the depth is smaller than 4
 * or if there are more than 10 shapes inside the box
 */
void BoundingBox::build() {

    setMinMaxMid();

    box = Box(minXminYminZ, maxXmaxYmaxZ); /// needs to be renewed since the values changed

    if (depth < 14 && shapes.size() > 60) {
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

    Vector size = maxXmaxYmaxZ-minXminYminZ; // max of the Box in terms of width, height, depth


    if (size.getX() > size.getY() && size.getX() > size.getZ()){ // X is largest
        axis = 0; // x split
    } else if (size.getY() > size.getX() && size.getY() > size.getZ()){ // Y is lagest
        axis = 1; // y split
    }else { // Z is largest
        axis = 2; // z split
    }

    Vector min = {};
    Vector max = {};


    BoundingBox left = BoundingBox({},{},depth);
    BoundingBox right = BoundingBox({},{},depth);
    BoundingBox middle = BoundingBox({},{},depth);

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
/*/
bool BoundingBox::VectorInsideBoxZero(Vector test) { // test, if a Vector is inside of the first Box
    return (boxes[0].getMin().get(0) <= test.get(0) && test.get(0) <= boxes[0].getMax().get(0) &&
            boxes[0].getMin().get(1) <= test.get(1) && test.get(1) <= boxes[0].getMax().get(1) &&
            boxes[0].getMin().get(2) <= test.get(2) && test.get(2) <= boxes[0].getMax().get(2));
}/**/

/*/
bool BoundingBox::VectorInsideBox(Vector test,int i) { // test, if a Vector is inside of the first Box
    return (boxes[i].getMin().get(0) <= test.get(0) && test.get(0) <= boxes[i].getMax().get(0) &&
            boxes[i].getMin().get(1) <= test.get(1) && test.get(1) <= boxes[i].getMax().get(1) &&
            boxes[i].getMin().get(2) <= test.get(2) && test.get(2) <= boxes[i].getMax().get(2));
}/**/

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







