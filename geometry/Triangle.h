//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include "../math/Vector.h"
#include "Shape.h"

class Triangle: public Shape{
public:
    Triangle(Vector a,Vector b,Vector c);
    Triangle(Vector a,Vector b,Vector c,Vector color);


    int getId() override;
    Vector getRgb() override;
    bool getIntersectVec(Ray ray, Vector& HitPoint, Vector& HitNormal) override;
    Vector getNormal(Vector pos) override;
private:
    Vector a;
    Vector b;
    Vector c;
    Vector normal;


};


#endif //RAYTRACER_TRIANGLE_H
