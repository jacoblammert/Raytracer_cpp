//
// Created by Jacob on 26.04.2020.
//

#include <iostream>
#include <utility>
#include "Renderer.h"
#include "../geometry/Material.h"

Renderer::Renderer() {
    //std::cout<< "Loading Image"<<std::endl;
    //image = Image("picture99999.ppm");
    //image.loadImage();
    //std::cout<< "Image loaded"<<std::endl;
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
        colorfinal.scale(0.2f * (1 - shapes[hit]->getMaterial().getTransparency()));


        Vector PointHit = HitPoint;//{HitPoint->get(0), HitPoint->get(1), HitPoint->get(2)};
        Vector HitToLight = {};

        float lightStrength = 0;
        float angle;

        if (shapes[hit]->getMaterial().getTransparency() != 1 && shapes[hit]->getMaterial().getGlossy() != 1) { // ||?
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


            if (shapes[hit]->getMaterial().getGlossy() > 0) {


                Color refl = {0, 0, 0};
                int reflectionsamples = 8;

                if (depth > 0){ // only the first reflection rays will be multiplied by the amount of the reflaction samples (if there are to many reflection surfaces, there might be reflectionsamples^n , n = depth reflections and extra calculations)
                    reflectionsamples = 1;
                }

                for (int i = 0; i < reflectionsamples; ++i) {
                    // the first vector doesent need to be changed, but I did it this way for now
                    refl = getReflectedColor(ray, HitPoint, HitNormal, Normal, depth, lights, boundingBox,// increasing the depth is not really necessary
                                             shapes, hit);
                    reflectionColor = refl + reflectionColor;
                }
                reflectionColor.scale(1.0f / (float) reflectionsamples);
            }

            if (shapes[hit]->getMaterial().getTransparency() > 0) {


                Color refr = {0, 0, 0};
                int refractionsamples = 8;

                if (depth > 0){
                    refractionsamples = 1;
                }


                for (int i = 0; i < refractionsamples; ++i) {

                    refr = getRefractedColor(ray, HitPoint, HitNormal, Normal, depth, lights, boundingBox, // increasing the depth is not really necessary
                                             shapes, hit);
                    refractionColor = refr + refractionColor;
                }
                refractionColor.scale(1.0f / (float) refractionsamples);
            }
        }


        colorfinal.scale(1 - shapes[hit]->getMaterial().getTransparency());

        reflectionColor.scale(shapes[hit]->getMaterial().getGlossy());
        refractionColor.scale(shapes[hit]->getMaterial().getTransparency());

        colorfinal = colorfinal + reflectionColor + refractionColor;

        colorfinal.scale(1 /
                         (shapes[hit]->getMaterial().getTransparency() + 1 /*shapes[hit]->getMaterial().getGlossy()*/ +
                          shapes[hit]->getMaterial().getRoughness()));

        return colorfinal;
    }
    return /**/getSkybox(ray.getDir());/*/Color();/**/
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

void Renderer::setSkybox(Image *skybox) {
    this->skybox = skybox;
}

/**
 * Returns the color of the Skybox, if the ray doesn't hit any objects and
 * takes the directional Vector as an Input
 * @param vector direction
 * @return color at x and y
 */
/**/
Color Renderer::getSkybox(Vector vector) {
    vector.normalize();
    Vector horizontal = {1, 0, 0};
    Vector horizontal2 = {0, 1, 0};

    Vector xvec = {vector.get(0), vector.get(1), 0};
    xvec.normalize();

    float x = horizontal.dot(xvec);
    float y = -vector.get(2);

    x = (x + 1.0f) / 2.0f;// 0 to 0.5

    if (horizontal2.dot(xvec) < 0) {
        x = -x;
    }

    x = (x + 1.0f) / 2.0f;
    y = (y + 1) / 2;

    return skybox->getPixel(x, y);
}

float Renderer::randomFloat(float range) {
    float r = ((float) rand()) / (float) (RAND_MAX / 2.0f);
    r -= 1.0f; // range from -1 to 1
    r *= range;// range from -range to range
    return r;
}

Color Renderer::getReflectedColor(Ray ray, Vector HitPoint, Vector HitNormal, Vector Normal, int depth,
                                  std::vector<Light *> lights,
                                  BoundingBox *boundingBox, std::vector<Shape *> shapes, int hit) {

    Vector reflectedVector = ray.getDir().getReflected(HitNormal);

    Vector offset = {0, 0, 0};
    float roughness = shapes[hit]->getMaterial().getRoughness();
    if (roughness != 0.0) {

        // the first vector doesent need to be changed, but I did it this way for now

        offset.set(0, randomFloat(roughness));
        offset.set(1, randomFloat(roughness));
        offset.set(2, randomFloat(roughness));
        offset.normalize();
        offset.scale(roughness);
    }
    reflectedVector = reflectedVector + offset;


    Ray reflectionray = {HitPoint + Normal, reflectedVector};

    return getColor(reflectionray, depth + 1, std::move(lights), boundingBox);
}

Color Renderer::getRefractedColor(Ray ray, Vector HitPoint, Vector HitNormal, Vector Normal, int depth,
                                  std::vector<Light *> lights, BoundingBox *boundingBox, std::vector<Shape *> shapes,
                                  int hit) {

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


    Vector offset = {0, 0, 0};
    float roughness = shapes[hit]->getMaterial().getRoughness();
    if (roughness != 0.0) {


        // the first vector doesent need to be changed, but I did it this way for now

        offset.set(0, randomFloat(roughness));
        offset.set(1, randomFloat(roughness));
        offset.set(2, randomFloat(roughness));
        offset.normalize();
        offset.scale(roughness);
    }
    refractedVector = refractedVector + offset;


    Ray refractionray = {position, refractedVector};
    refractionray.setRefractionindex(shapes[hit]->getMaterial().getRefractiveIndex());

    return getColor(refractionray, depth + 1, std::move(lights), boundingBox);
}

