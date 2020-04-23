
#include <iostream>
#include "math/Vector.h"
#include "world/Camera.h"
#include "geometry/Sphere.h"
#include "world/Scene.h"
#include "geometry/Plane.h"
#include "geometry/Triangle.h"
#include "world/OBJLoader.h"

int main() {


    Camera cam = Camera(Vector(0.181818, 6, 2.5), Vector(1, 0, 0), 250, 250, 1);

    cam.lookAt(Vector(0.181818, 0, 0));

    cam.setNumberOfPixel(500000);// max number of pixels for the image
    cam.setWidthToHeight(16.0f / 9.0f); // Height to width ratio

    cam.print();


    Sphere s = Sphere(Vector(0, 0, 0), 0.2, Vector(0, 0, 255));

    Sphere s1 = Sphere(Vector(2, 0, 0.1), 0.2, Vector(0, 255, 255));
    Sphere s2 = Sphere(Vector(0, 2, 0.1), 0.2, Vector(255, 0, 255));
    Sphere s3 = Sphere(Vector(0, -3, 0.1), 0.2, Vector(255, 255, 0));
    Sphere s4 = Sphere(Vector(-2, 0, 0.1), 0.2, Vector(0, 0, 0));


    Plane p1 = Plane(Vector(0, 0, 0), Vector(0, 0, 1), Vector(100, 100, 100));


    Box b1 = Box(Vector(-0.1, -0.1, -2), Vector(0.1, 0.1, 2), Vector(255, 0, 0));

    Box b2 = Box(Vector(0, -2, 0.1), 0.4, 0.4, 0.4, Vector(0, 120, 180));

    Box b3 = Box(Vector(2, 0, 0), 4, 0.05, 0.05, Vector(255, 255, 255));

    Triangle t1 = Triangle(Vector(2, 0, 0.1), Vector(0, 2, 0.1), Vector(0, -2, 0.1), Vector(255, 255, 150));
    Triangle t2 = Triangle(Vector(-2, 0, 0.1), Vector(0, -2, 0.1), Vector(0, 2, 0.1), Vector(120, 255, 255));


    Box b4 = Box(Vector(-2, -3.2, -2), Vector(4, 2.2, 2), Vector(255, 255, 255));


    Scene scene = Scene(cam);
/*/
    scene.addShape(&s);
    scene.addShape(&s1);
    scene.addShape(&s2);
    scene.addShape(&s3);
    scene.addShape(&s4);

    scene.addShape(&p1);

    scene.addShape(&b1);
    scene.addShape(&b2);
    scene.addShape(&b3);
    //scene.addShape(&b4);

    scene.addShape(&t1);
    scene.addShape(&t2);
/**/
    //scene.addShape(&t2);

    //scene.addShape(&p1);

    OBJLoader objLoader = OBJLoader("untitled4.obj");
    objLoader.LoadOBJ();
    Object object = objLoader.getObject();
    scene.addShapes(object.getTriangles());


    scene.render();
    scene.drawImage();


    return 0;
}

