//
// Created by Jacob on 22.04.2020.
//

#ifndef RAYTRACER_BOUNDINGBOX_H
#define RAYTRACER_BOUNDINGBOX_H


#include <vector>
#include "../math/Vector.h"
#include "../geometry/Shape.h"
#include "../geometry/Box.h"

class BoundingBox {
public:
    BoundingBox();

    BoundingBox(std::vector<Shape *> shapes);

    BoundingBox(int depth);

    //BoundingBox(Vector minXminYminZ, Vector maxXmaxYmaxZ, std::vector<Shape *> shapes, int depth);

    //std::vector<Shape *> getIntersectVec(Ray ray);

    void getIntersectedShape(Shape &shape, Intersect* intersect,bool &hit);

    void build();

    void split();

    void setMinMaxMid();

    void getMin(Vector shapemin);

    void getMax(Vector shapemax);

    void addShape(Shape *shape);

    Vector getMedian();

    Vector getMin();

    Vector getMax();

    void print(int depth);

private:
    Vector minXminYminZ;
    Vector maxXmaxYmaxZ;
    Vector median;

    int depth;

    Box box;


    std::vector<BoundingBox> boxes;

    std::vector<Shape *> shapes;


};


#endif //RAYTRACER_BOUNDINGBOX_H
