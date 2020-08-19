//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include "../math/Vector.h"
#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(Vector a, Vector b, Vector c);

    Triangle(Vector a, Vector b, Vector c, Color color);


    bool getIntersectVec(Ray ray, Vector &HitPoint,  Vector &HitNormal, float &distance) override;

    Vector getNormal(Vector pos) override;

    Vector getMin() override;

    Vector getMax() override;

    Vector getMedian() override;
/**/
    Material* getMaterial() override;

    void setMaterial(Material* material) override;
/**/

void translate(Vector position) override;

    void print() override;

private:
    Vector a;
    Vector b;
    Vector c;
    Vector normal;


};


#endif //RAYTRACER_TRIANGLE_H
