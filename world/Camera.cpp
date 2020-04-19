//
// Created by Jacob on 14.04.2020.
//

#include "Camera.h"
#include "../math/Ray.h"
#include "../math/Vector.h"

Camera::Camera() {

}

Camera::Camera(Vector position, Vector direction, int width, int height, float dist) {
    this->position = position;
    this->direction = direction;
    this->width = width;
    this->height = height;
    this->dist = dist;
    update();
}

/**
 * Should be called after the direction of the Camera has been changed, updates the right, top and the direction itself
 */
void Camera::update() {

    right = direction.cross(up);// from the left of the camera plane to the right
    top = right.cross(this->direction); // from bottom of the camera plane to the top
    direction.normalize();
    direction =  direction * dist;
}

/**
 * Generates a ray from the cameras position onto the camera plane. If the fov should be changed, the distance of the Camera plane needs to change.
 * The x and y positions are in pixelspace, like the width and the height of the camera
 * @param x pos of the Pixel on the screen 0 to width
 * @param y pos of the Pixel on the screen 0 to height
 * @return a new Ray with the pos of the Camera and the Direction onto the camera plane in worldspace
 */
Ray Camera::generateRay(int x, int y) {
    update(); // shouldn't be called normally, but it appears, as if the values are automatically changed, so we need to reset them

    float widthToHeight = ((float)(width-1)/(float)(height-1));

    float scalex = (((float) x / (float) (width-1))- 0.5f) * 2 * widthToHeight; // now a range from -1 to 1 depending on the x to width ratio
    float scaley = -(((float) y / (float) (height-1)) - 0.5f) * 2; // now a range from -1 to 1 depending on the y to Height ratio

    right.normalize();
    top.normalize();

    right = right * scalex;
    top = top * scaley;

    return {position,position + direction + top + right};
}

void Camera::setPosition(Vector pos) {
    position = pos;
}

void Camera::lookAt(Vector pos) {
    direction = pos - position;
    update();
}

void Camera::setDist(float dist) {
    this->dist = dist;
    update();
}

int Camera::getWidth() {
    return width;
}

int Camera::getHeight() {
    return height;
}







