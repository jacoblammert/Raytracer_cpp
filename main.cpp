
#include "math/Vector.h"
#include "world/Camera.h"
#include "geometry/Sphere.h"
#include "world/Scene.h"
#include "geometry/Plane.h"

int main() {

    Camera cam = Camera(Vector(0, 0, 0.1), Vector(1, 0, 0), 500, 500, 1); // min dist is ca. 0.7
    cam.lookAt(Vector(10, 2, 0));

    Sphere s = Sphere(Vector(10, 3, 1), 2, Vector(255, 0, 0));
    Sphere s1 = Sphere(Vector(9, 2, 5), 3, Vector(180, 40, 120));
    Sphere s2 = Sphere(Vector(2, 2, -1), 1, Vector(80, 255, 150));

    Plane p1 = Plane(Vector(2, 1, -1), Vector(0,0,1), Vector(100, 100, 100));


    Scene scene = Scene(cam);
    for (int i = 0; i < 1200; ++i) {
        scene.addShape(&s2);
    }

    scene.render();


    return 0;
}
