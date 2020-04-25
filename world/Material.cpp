//
// Created by Jacob on 24.04.2020.
//

#include "Material.h"

#include <utility>
#include <iostream>

Material::Material() {
    roughness = 0.5f;
    glossy = 0.5f;
    transparency = 0.0f;
    refractiveIndex = 1;
    color = {255, 255, 255};
}

Material::Material(Vector color) {

    roughness = 0.5f;
    glossy = 0.5f;
    transparency = 0.0f;
    refractiveIndex = 1;
    this->color = color;
}

Material::Material(Vector color, float roughness, float glossy, float transparency) {
    this->roughness = roughness;
    this->glossy = glossy;
    this->transparency = transparency;
    refractiveIndex = 1;
    this->color = color;
}

Material::Material(Vector color, float roughness, float glossy, float transparency, float refractiveIndex) {

    this->roughness = roughness;
    this->glossy = glossy;
    this->transparency = transparency;
    this->refractiveIndex = refractiveIndex;
    this->color = color;
}


Vector
Material::getColor(Ray ray, int depth, Shape *shape, Vector *HitPoint, Vector *HitNormal, std::vector<Light *> lights,
                   BoundingBox *boundingBox) {

    if (depth < 1) {
        float r = 0;
        float g = 0;
        float b = 0;

        Color colorfinal;
        Color colorlight;
        Color Lightcolor;


        Vector HitPoint2 = {HitPoint->get(0), HitPoint->get(1), HitPoint->get(2)};


        Color colorobject = shape->getRgb();

        colorfinal = colorobject;

        colorfinal.scale(0.2);


        Vector hitNORMAL = {HitNormal->get(0), HitNormal->get(1), HitNormal->get(2)};

        hitNORMAL.normalize();

        Vector HitNormal2 = hitNORMAL;


        HitNormal2.scale(0.001);

        float lightStrength = 0;
        float angle;

        Vector LightHit = {};


        for (int i = 0; i < lights.size(); ++i) {

            if (lights[i]->getIntensity() > 0) {

                LightHit = (lights[i]->getPosition() - HitPoint2);

                lightStrength = LightHit.getLength();

                LightHit.normalize();

                angle = hitNORMAL.dot(LightHit);


                if (0 < angle) { // normal facing in direction of light

                    if (!castShadowRay({HitPoint2 + HitNormal2, LightHit}, boundingBox, lightStrength)) {
                        /**/


                        ////float anglelight = ray.getDir().dot(LightHit);


                        //angleall += angle;

                        //float brightness = (lights[i]->getIntensity() / pow(lightStrength, 2));
                        //float brightness = (1 / pow(lightStrength, 2)); // previously intensityLight
                        ////float brightness = (lights[i]->getIntensity() /(lightStrength * lightStrength)); // previously intensityLight


                        ////Lightcolor = lights[i]->getColor();
                        //Color colorobject = shape->getRgb();


                        //Lightcolor = Lightcolor * colorobject;


                        //Lightcolor.scale(/**/sqrt(sqrt(angle)) * /**/brightness);//intensityLight);//sqrt(angle/* * intensityLight*/) * intensityLight);//sqrt(angle) * intensityLight);
                        //Lightcolor.scale(/**/sqrt(sqrt(angle)) * (1-anglePointRayOrigin) * /**/brightness);//intensityLight);//sqrt(angle/* * intensityLight*/) * intensityLight);//sqrt(angle) * intensityLight);
                        ////Lightcolor.scale(angle  * brightness);//intensityLight);//sqrt(angle/* * intensityLight*/) * intensityLight);//sqrt(angle) * intensityLight);
                        //colorobject.scale(angle * intensityLight);


                        //colorfinal = colorfinal + Lightcolor;/* + colorobject/*;*/



                        ////colorobject = shape->getRgb(); // light brightens part of the objects color
                        ////colorobject = colorobject * Lightcolor; // light brightens part of the objects color

                        //colorobject.scale(brightness);


                        ////colorlight = colorlight /*/+ Lightcolor/**/ + colorobject;/**/


                        //float anglelight = ray.getDir().dot(LightHit);


                        Lightcolor = lights[i]->getColor();
                        Lightcolor.scale(
                                (angle * lights[i]->getIntensity()) / (lightStrength * lightStrength)); // brightness

                        colorobject = shape->getRgb(); // light brightens part of the objects color
                        colorobject = colorobject *
                                      Lightcolor; // light brightens part of the objects color // can be optimised by multiplying at the end only

                        colorlight = colorlight + colorobject;
                    }
                }
            }
        }

        //Vector colorobject = shape->getRgb();
        //colorfinal = /*colorfinal + */colorobject;
/*/
        colorfinal = colorfinal + colorlight;

        colorfinal.scale(1.0f / angleall);//(angleall));
/**/



        //colorlight.scale(1.0f / angleall);//(angleall));

        colorfinal = colorfinal + colorlight;
        //colorfinal = colorlight;


        colorfinal.scale(255);
        colorfinal.setRange(0, 255);

        r = colorfinal.getR();
        g = colorfinal.getG();
        b = colorfinal.getB();

        return Vector(r, g, b);
    }
    return Vector();
}

/**
 * First Ray from the Camera into the scene
 * @param depth of the ray.
 * @param ray from camera into the scene
 * @param boundingBox with all the shapes from the scene
 * @param lights in the scene
 * @return color for the pixel
 */
Vector Material::castRay(int depth, Ray ray, BoundingBox *boundingBox, std::vector<Light *> lights) {

    if (depth <= 2) {

        Vector HitPoint = {};
        Vector HitNormal = {};

        int hit = -1;
        float mindistance = INFINITY - 1;

        std::vector<Shape *> shapes;

//#pragma omp critical
        {
            shapes = boundingBox->getIntersectVec(ray);
        }
        for (int i = 0; i < shapes.size(); ++i) {
            if (shapes[i]->getIntersectVec(ray, HitPoint, HitNormal, mindistance, hit,
                                           i)) { // bool if ray intersects the Object // hit & other values set for lighting & stuff
            }
        }

        if (hit >= 0) { // closest object gets returned
            return getColor(ray, depth, shapes[hit], &HitPoint, &HitNormal, std::move(lights), boundingBox);
        }
    }
    return {0, 0, 0};
}

/**
 * returns true, if a shape is in the way of the lightsource (or if the distance from the hit point is smaller than the given distance)
 * @param ray to be shot
 * @param boundingBox all the geometry information
 * @param distance distance from point p (Ray position to Lightsource distance)
 * @return if the point the ray hits is 1. in front of the ray and 2. is closer than distance units it returns true
 */
bool Material::castShadowRay(Ray ray, BoundingBox *boundingBox, float distance) {

    Vector HitPoint = {};
    Vector HitNormal = {};

    int hit = -1;
    float mindistance = INFINITY - 1;

    std::vector<Shape *> shapes;

//#pragma omp critical
    {
        shapes = boundingBox->getIntersectVec(ray);
    }
    for (int i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getIntersectVec(ray, HitPoint, HitNormal, mindistance, hit,
                                       i)) { // bool if ray intersects the Object // hit & other values set for lighting & stuff
        }
    }

    if (hit >= 0) { // closest object in front of the ray gets returned
        //std::cout<<"mindist: " <<mindistance<< " other dist: " << (ray.getPos()-HitPoint).getLength()<<std::endl;
        /*/if (mindistance < 0){
            return false;
        }/**/
        if (distance > mindistance) {
            if (mindistance > 0) {
                return true;
            }
        }

        //return false;//distance > mindistance;//(ray.getPos()-HitPoint).getLength();
    }
    return false;
}




