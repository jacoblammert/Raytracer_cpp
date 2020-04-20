
#include "math/Vector.h"
#include "world/Camera.h"
#include "geometry/Sphere.h"
#include "world/Scene.h"
#include "geometry/Plane.h"
#include "geometry/Triangle.h"

int main() {

    Camera cam = Camera(Vector(0, 0, 0.1), Vector(1, 0, 0), 500, 500, 1);
    cam.lookAt(Vector(1, 0, 0));

    Sphere s = Sphere(Vector(10, -4, 4), 4, Vector(0, 0, 255));
    Sphere s1 = Sphere(Vector(9, 2, 5), 3, Vector(180, 40, 120));
    Sphere s2 = Sphere(Vector(2, 2, -1), 1, Vector(80, 255, 150));

    Plane p1 = Plane(Vector(2, 2, -2), Vector(0,0,1), Vector(255, 0, 0));

    Triangle t1 = Triangle(Vector(10,-2.5,-4),Vector(10,7.5,-4),Vector(10,2.5,5),Vector(255,255,0));

    Scene scene = Scene(cam);

    scene.addShape(&s);
    scene.addShape(&s1);
    scene.addShape(&s2);
    for (int i = 0; i < 0; ++i) {
        scene.addShape(&s2);
    }
    scene.addShape(&p1);
    scene.addShape(&t1);

    scene.render();


    return 0;
}

