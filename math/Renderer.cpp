//
// Created by Jacob on 26.04.2020.
//

#include <iostream>
#include "Renderer.h"
#include "../geometry/Material.h"

Renderer::Renderer() {

}

/**
 * A method to get the pure color of a point, if an Object has been hit.
 * @param ray
 * @param depth depth of the ray
 * @param lights pointer to the lightvector to calculate the lightstrength
 * @param boundingBox to get intersections with other shapes from the ray to go to all the lightsources
 * @return color consisting of brightness for that point and each light and color of the shape blended together
 */
Color Renderer::getColor(Ray ray, int depth, std::vector<Light *> lights, BoundingBox *boundingBox) {
    Vector HitPoint = {};
    Vector HitNormal = {};


    int hit = -1;
    float mindistance = INFINITY - 1;

    std::vector<Shape *> shapes = boundingBox->getIntersectVec(ray);

    for (int i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getIntersectVec(ray, HitPoint, HitNormal, mindistance, hit,
                                       i)) { // bool if ray intersects the Object // hit & other values set for lighting & stuff
        }
    }


    if (hit > -1) { // shape gets hit


        Color Lightcolor;
        Color colorfinal = shapes[hit]->getMaterial().getColor();
        colorfinal.scale(0.2);


        Vector PointHit = HitPoint;//{HitPoint->get(0), HitPoint->get(1), HitPoint->get(2)};
        Vector HitToLight = {};

        float lightStrength = 0;
        float angle;

        if (shapes[hit]->getMaterial().getTransparency() != 1) {
            for (int i = 0; i < lights.size(); ++i) {

                if (lights[i]->getIntensity() > 0) {

                    Vector Normal = HitNormal;
                    Normal.normalize();


                    HitToLight = (lights[i]->getPosition() - PointHit);
                    lightStrength = HitToLight.getLength();
                    HitToLight.normalize();

                    angle = Normal.dot(HitToLight);

                    if (0 < angle) { // normal facing in direction of light
                        Normal.scale(0.001);
                        if (!castShadowRay({PointHit + Normal, HitToLight}, boundingBox, lightStrength)) {

                            Lightcolor = lights[i]->getColor();
                            Lightcolor.scale((angle * lights[i]->getIntensity()) /
                                             (lightStrength * lightStrength)); // brightness

                            colorfinal = shapes[hit]->getMaterial().getColor() * Lightcolor + colorfinal;
                        }
                    }
                }
            }
        }
        Color reflectionColor;
        Color refractionColor;

        if (depth < 3) { // calculates as n reflections because depth < n

            Vector Normal = HitNormal;//HitNormal.scale(0.001);

            Normal.scale(0.001);

            Vector reflectedVector = ray.getDir().getReflected(HitNormal);
            Ray reflectionray = {HitPoint + Normal, reflectedVector};
            if (shapes[hit]->getMaterial().getGlossy() > 0) {
                reflectionColor = getColor(reflectionray, depth + 1, lights, boundingBox);
            }


            if (shapes[hit]->getMaterial().getTransparency() > 0) {


                Vector position = {};

                float newRefractionindex = shapes[hit]->getMaterial().getRefractiveIndex();
                float oldrefractionIndex = ray.getRefractionindex();

                if (depth % 2 == 0) { // Camera is in air // Normal is ok
                    position = HitPoint - Normal;

                    oldrefractionIndex = 1;
                    newRefractionindex = shapes[hit]->getMaterial().getRefractiveIndex();

                } else {
                    HitNormal.scale(-1);// Normal needs to be inverted because the ray enters air again
                    position = HitPoint + Normal;

                    oldrefractionIndex = shapes[hit]->getMaterial().getRefractiveIndex(); // hitting the same shape from the inside
                    newRefractionindex = 1;

                }

                //std::cout << "old: " << oldrefractionIndex << " new: " << newRefractionindex << std::endl;

                Vector refractedVector = ray.getDir().getRefracted(HitNormal, oldrefractionIndex, newRefractionindex);


                Ray refractionray = {position, refractedVector};
                refractionray.setRefractionindex(shapes[hit]->getMaterial().getRefractiveIndex());


                refractionColor = getColor(refractionray, depth + 1, lights, boundingBox);
            }
        }


        colorfinal.scale(1 - shapes[hit]->getMaterial().getTransparency());
        reflectionColor.scale(shapes[hit]->getMaterial().getGlossy());
        refractionColor.scale(shapes[hit]->getMaterial().getTransparency());

        colorfinal = colorfinal + reflectionColor + refractionColor;

        return colorfinal;
    }
    return Color();
}

/**
 * returns true, if a shape is in the way of the lightsource (or if the distance from the hit point is smaller than the given distance)
 * @param ray to be shot
 * @param boundingBox all the geometry information
 * @param distance distance from point p (Ray position to Lightsource distance)
 * @return if the point the ray hits is 1. in front of the ray and 2. is closer than distance units it returns true
 */
bool Renderer::castShadowRay(Ray ray, BoundingBox *boundingBox, float distance) {

    Vector HitPoint = {};
    Vector HitNormal = {};

    int hit = -1;
    float mindistance = INFINITY - 1;

    std::vector<Shape *> shapes = boundingBox->getIntersectVec(ray);

    for (int i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getIntersectVec(ray, HitPoint, HitNormal, mindistance, hit,
                                       i)) { // bool if ray intersects the Object // hit & other values set for lighting & stuff
        }
    }
    return hit >= 0 && 0 < mindistance && mindistance < distance;
}


