//
// Created by Jacob on 21.04.2020.
//

#include <iostream>
#include "Box.h"

Box::Box() {}

Box::Box(Vector minXminYminZ, Vector maxXmaxYmaxZ) {

    bounds.push_back(minXminYminZ);
    bounds.push_back(maxXmaxYmaxZ);

    position = minXminYminZ + maxXmaxYmaxZ;
    position.scale(0.5);
}

Box::Box(Vector Pos, float xScale, float yScale, float zScale) {
    Vector minXminYminZ = Vector(Pos.getX() - xScale / 2, Pos.getY() - yScale / 2, Pos.getZ() - zScale / 2);
    Vector maxXmaxYmaxZ = Vector(Pos.getX() + xScale / 2, Pos.getY() + yScale / 2, Pos.getZ() + zScale / 2);
    bounds.push_back(minXminYminZ);
    bounds.push_back(maxXmaxYmaxZ);
    position = Pos;
}

Box::Box(Vector minXminYminZ, Vector maxXmaxYmaxZ, Color color) {
    bounds.push_back(minXminYminZ);
    bounds.push_back(maxXmaxYmaxZ);

    position = minXminYminZ + maxXmaxYmaxZ;
    position.scale(0.5);
}

Box::Box(Vector Pos, float xScale, float yScale, float zScale, Color color) {
    Vector minXminYminZ = Vector(Pos.getX() - xScale / 2, Pos.getY() - yScale / 2, Pos.getZ() - zScale / 2);
    Vector maxXmaxYmaxZ = Vector(Pos.getX() + xScale / 2, Pos.getY() + yScale / 2, Pos.getZ() + zScale / 2);
    bounds.push_back(minXminYminZ);
    bounds.push_back(maxXmaxYmaxZ);
    position = Pos;
}

int Box::getId() {
    return 0;
}


bool Box::getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) {

    Vector rayposition = ray.getPos();
    Vector raydirection = ray.getDir();
    raydirection.divide(1);

    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tmax = (bounds[1 - raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tymin = (bounds[raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();
    tymax = (bounds[1 - raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();
    tzmax = (bounds[1 - raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;


    if (0 < tmin && tmin < distance) {
        raydirection = ray.getDir();
        raydirection.scale(tmin);

        distance = tmin;
        HitPoint = rayposition + raydirection;
        HitNormal = getNormal(HitPoint);
        id = newid;
        return true;
    }
    if (tmin < 0 && 0 < tmax && tmax < distance) {
        raydirection = ray.getDir();
        raydirection.scale(tmax);

        distance = tmax;
        HitPoint = rayposition + raydirection;
        HitNormal = getNormal(HitPoint);
        id = newid;
        return true;
    }


}

/**
 * Only important for the Skybox
 * we now the ray hits the Skybox, therfore we can remove a few things
 * @param direction
 * @param HitNormal
 */
void Box::getIntersectVec(Vector &direction, Vector &HitNormal) {

    Vector raydirection = direction;

    direction.divide(1);

    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[direction.sign(0)].getX()) * direction.getX();
    tmax = (bounds[1 - direction.sign(0)].getX()) * direction.getX();
    tymin = (bounds[direction.sign(1)].getY()) * direction.getY();
    tymax = (bounds[1 - direction.sign(1)].getY()) * direction.getY();

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[direction.sign(2)].getZ()) * direction.getZ();
    tzmax = (bounds[1 - direction.sign(2)].getZ()) * direction.getZ();


    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;


    if (0 < tmin) {
        direction = raydirection;
        direction.scale(tmin);

        HitNormal = getNormal(direction);
    }
    if (tmin < 0 && 0 < tmax) {
        direction = raydirection; // original direction values get passed onto the original direction vector
        direction.scale(tmax);

        HitNormal = getNormal(direction);
    }
}

float Box::getDistance(Ray ray) {

    Vector rayposition = ray.getPos();
    Vector raydirection = ray.getDir();
    raydirection.divide(1);

    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tmax = (bounds[1 - raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tymin = (bounds[raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();
    tymax = (bounds[1 - raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();

    if ((tmin > tymax) || (tymin > tmax))
        return INFINITY;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();
    tzmax = (bounds[1 - raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();

    if ((tmin > tzmax) || (tzmin > tmax))
        return INFINITY;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;


    if (0 < tmin) {
        return tmin;
    }
    if (tmin < 0 && 0 < tmax) {
        return tmax;
    }
    return INFINITY;
}


/**
 * Important for BoundingBox intersection testing. Similar to the previous method, but without all the useless stuff
 * @param ray that get tested against this box
 * @return true if the ray hits
 */
bool Box::getIntersect(Ray ray) {

    Vector rayposition = ray.getPos();
    Vector raydirection = ray.getDir();
    raydirection.divide(1);

    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tmax = (bounds[1 - raydirection.sign(0)].getX() - rayposition.getX()) * raydirection.getX();
    tymin = (bounds[raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();
    tymax = (bounds[1 - raydirection.sign(1)].getY() - rayposition.getY()) * raydirection.getY();

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();
    tzmax = (bounds[1 - raydirection.sign(2)].getZ() - rayposition.getZ()) * raydirection.getZ();

    return !((tmin > tzmax) || (tzmin > tmax));
}

Vector Box::getNormal(Vector pos) {

    float epsilon = 0.000001f;

    //pos.scale(1.001);

    if (pos.get(0) <= bounds[0].get(0) + epsilon) {
        return {-1, 0, 0}; // back
    } else if (pos.get(0) >= bounds[1].get(0) - epsilon) {
        return {1, 0, 0}; // front
    }
    if (pos.get(1) <= bounds[0].get(1) + 0.001) {
        return {0, -1, 0}; // left
    } else if (pos.get(1) >= bounds[1].get(1) - epsilon) {
        return {0, 1, 0}; // right
    }
    if (pos.get(2) <= bounds[0].get(2) + epsilon) {
        return {0, 0, -1}; // bottom
    } else if (pos.get(2) >= bounds[1].get(2) - epsilon) {
        return {0, 0, 1}; // top
    }
    return {0, 1, 0}; // if in corner, or something is wrong
}

Vector Box::getMin() {
    return bounds[0];
}

Vector Box::getMax() {
    return bounds[1];
}

Vector Box::getMedian() {
    return position;
}

void Box::print() {
    std::cout << "Box: " << std::endl;
    std::cout<< "Min: ";
    bounds[0].print();
    std::cout<< "Max: ";
    bounds[1].print();
}

/**/
Material* Box::getMaterial() {
    return material;
}

void Box::setMaterial(Material* material) {
    this->material = material;
}




/**/






