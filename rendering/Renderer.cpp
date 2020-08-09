//
// Created by Jacob on 26.04.2020.
//

#include <iostream>
#include <utility>
#include "Renderer.h"
#include "../geometry/Material.h"
#include "../geometry/Triangle.h"
#include "../geometry/Sphere.h"

Renderer::Renderer() {

    //std::cout<< "Loading Image"<<std::endl;
    //image = Image("picture99999.ppm");
    //image.loadImage();
    //std::cout<< "Image loaded"<<std::endl;
}

Renderer::Renderer(Skybox *skybox, BoundingBox *boundingBox) :
        skybox{skybox}, boundingBox{boundingBox} {}

/**
 * A method to get the pure color of a point, if an Object has been hit.
 * @param ray
 * @param depth depth of the ray
 * @param lights pointer to the lightvector to calculate the lightstrength
 * @param boundingBox to get intersections with other shapes from the ray to go to all the lightsources
 * @return color consisting of brightness for that point and each light and color of the shape blended together
 */
Color Renderer::getColor(Ray ray, int depth, std::vector<Light *> lights) {
    Vector HitPoint{};
    Vector HitNormal{};


    //TODO split functions into different subfunctions to make visibility better


    float mindistance = INFINITY - 1;


    /**Get Intersected Object here**/

    bool hitbool = false;
    Sphere s{{},0};
    Shape *shape;
    boundingBox->getIntersectedShape(ray, s, HitPoint, HitNormal,mindistance, hitbool); // TODO make to pointer
    shape = &s;



    if (!hitbool || nullptr == shape) { // shape gets hit
        if (skybox != nullptr) {
            return skybox->getColor(ray.getDir());
        }
        return {};
    }




    float glossy = shape->getMaterial()->getGlossy();
    float transparency = shape->getMaterial()->getTransparency();
    float roughness = shape->getMaterial()->getRoughness();


    Color colorfinal{shape->getMaterial()->getColor()};
    colorfinal.scale(0.2f * (1 - transparency));




    if (!(transparency == 1.0f || glossy ==
                                  1.0f)) {///*/true/*/(shapes[hit]->getMaterial()->getTransparency() != 1.0f /*/||/*/&&/**/ /*/shapes[hit]->getMaterial()->getGlossy() != 1.0f/*/ true/**/)/**/) { // ||?
        float lightStrength = 0;


        Vector HitToLight = {};
        for (int i = 0; i < lights.size(); ++i) {

            if (lights[i]->getIntensity() > 0) {

                Vector Normal = HitNormal;
                Normal.normalize();


                HitToLight = (lights[i]->getPosition() - HitPoint);
                lightStrength = HitToLight.getLength();
                HitToLight.normalize();

                float angle = Normal.dot(HitToLight);

                if (0 < angle) { // normal facing in direction of light
                    Normal.scale(0.001);
                    if (!castShadowRay({HitPoint + Normal, HitToLight}, lightStrength)) {

                        Color Lightcolor = lights[i]->getColor();
                        Lightcolor.scale((angle * lights[i]->getIntensity()) / (lightStrength * lightStrength)); // brightness

                        colorfinal += (shape->getMaterial()->getColor() * Lightcolor);
                    }
                }
            }
        }
    }
    Color reflectionColor;
    Color refractionColor;

    if (depth < 20) { // calculates as n reflections because depth < n

        Vector Normal{HitNormal};//HitNormal.scale(0.001);


        if (glossy > 0) {
            int reflectionsamples = roughness == 0.0f ? 1 : 3 * (depth == 0) + 1;
            // max number of rays is 4, if the depth (iteration) is greater than 1, we do only have one new ray
            // 4 rays in the first iteration, only 1 in each following iteration. If the roughness is 0.0f, we do always have one new ray only

            for (int i = 0; i < reflectionsamples; ++i) {
                reflectionColor += getReflectedColor(ray, HitPoint, HitNormal, Normal, depth, lights,
                                                     shape);// increasing the depth is not really necessary
            }
            reflectionColor.scale(glossy / (float) reflectionsamples);
        }

        if (transparency > 0) {
            int refractionsamples = roughness == 0.0f ? 1 : 3 * (depth == 0) + 1;
            // max number of rays is 4, if the depth (iteration) is greater than 1, we do only have one new ray
            // 4 rays in the first iteration, only 1 in each following iteration. If the roughness is 0.0f, we do always have one new ray only

            for (int i = 0; i < refractionsamples; ++i) {
                refractionColor += getRefractedColor(ray, HitPoint, HitNormal, Normal, depth, lights,
                                                     shape);// increasing the depth is not really necessary
            }
            refractionColor.scale(transparency / (float) refractionsamples);
        }
    }

    colorfinal.scale(1.0f - transparency);

    colorfinal += (reflectionColor + refractionColor);

    float value = 1 - transparency;

    Vector Brightness{value, transparency, glossy};

    colorfinal.scale(1.0f / Brightness.getLength());

    return colorfinal;

}

/**
 * returns true, if a shape is in the way of the lightsource (or if the distance from the hit point is smaller than the given distance)
 * @param ray to be shot
 * @param boundingBox all the geometry information
 * @param distance distance from point p (Ray position to Lightsource distance)
 * @return if the point the ray hits is 1. in front of the ray and 2. is closer than distance units it returns true
 */
bool Renderer::castShadowRay(Ray ray, float distance) {

    Vector HitPoint{};
    Vector HitNormal{};

    bool hit = false;
    float mindistance = INFINITY - 1;

    Sphere s = {{}, 1};

    boundingBox->getIntersectedShape(ray, s, HitPoint,HitNormal, mindistance, hit);

    return hit && mindistance < distance && mindistance >= 0;
}



float Renderer::randomFloat(float range) {
    float r = ((float) rand()) / (float) (RAND_MAX / 2.0f);
    r -= 1.0f; // range from -1 to 1
    r *= range;// range from -range to range
    return r;
}

Color Renderer::getReflectedColor(Ray ray, Vector HitPoint, Vector HitNormal, Vector Normal, int depth,
                                  std::vector<Light *> lights, Shape *shape) {

    Vector reflectedVector = ray.getDir().getReflected(HitNormal);


    float roughness = shape->getMaterial()->getRoughness();
    if (roughness != 0.0) {
        Vector offset = {0, 0, 0};

        // the first vector doesent need to be changed, but I did it this way for now

        for (int i = 0; i < 3; ++i) {
            offset.set(i, randomFloat(roughness));
        }
        offset.normalize();
        offset.scale(roughness);
        reflectedVector = reflectedVector + offset;
    }


    Ray reflectionray = {HitPoint + Normal, reflectedVector};

    return getColor(reflectionray, depth + 1, std::move(lights));
}

Color Renderer::getRefractedColor(Ray ray, Vector HitPoint, Vector HitNormal, Vector Normal, int depth,
                                  std::vector<Light *> lights, Shape *shape) {

    Vector position = {};

    float newRefractionindex;
    float oldrefractionIndex;

    if (depth % 2 == 0) { // Camera is in air // Normal is ok
        position = HitPoint - Normal;
        oldrefractionIndex = 1;
        newRefractionindex = shape->getMaterial()->getRefractiveIndex();

    } else {
        HitNormal.scale(-1);// Normal needs to be inverted because the ray enters air again
        position = HitPoint + Normal;
        oldrefractionIndex = shape->getMaterial()->getRefractiveIndex(); // hitting the same shape from the inside
        newRefractionindex = 1;

    }

    //std::cout << "old: " << oldrefractionIndex << " new: " << newRefractionindex << std::endl;

    Vector refractedVector = ray.getDir().getRefracted(HitNormal, oldrefractionIndex / newRefractionindex);


    float roughness = shape->getMaterial()->getRoughness();
    if (roughness != 0.0) {
        Vector offset = {0, 0, 0};


        // the first vector doesn't need to be changed, but I did it this way for now

        for (int i = 0; i < 3; ++i) {
            offset.set(i, randomFloat(roughness));
        }
        offset.normalize();
        offset.scale(roughness);
        refractedVector = refractedVector + offset;
    }


    Ray refractionray = {position, refractedVector};
    refractionray.setRefractionindex(shape->getMaterial()->getRefractiveIndex());

    return getColor(refractionray, depth + 1, std::move(lights));
}

void Renderer::setSkybox(Skybox *skybox) {
    this->skybox = skybox;
}

void Renderer::setBoundingBox(BoundingBox *boundingBox) {
    this->boundingBox = boundingBox;
}




