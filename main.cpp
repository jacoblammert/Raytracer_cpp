
#include <iostream>
#include "math/Vector.h"
#include "world/Camera.h"
#include "geometry/Sphere.h"
#include "world/Scene.h"
#include "geometry/Plane.h"
#include "geometry/Triangle.h"
#include "obj/OBJLoader.h"

int main() {


    Camera cam = Camera(Vector(10, 0, 2), Vector(1, 0, 0), 1920, 1080, 5);

    //cam.setPosition({10,0,5});
    cam.lookAt(Vector(0, 0, 0));

    //cam.setNumberOfPixel(25000);// max number of pixels for the image
    cam.setWidthToHeight(16.0f / 9.0f); // Height to width ratio

    cam.print();


    Sphere s = Sphere(Vector(0, 0, 0), 0.2, Color(0, 0, 1));

    Sphere s1 = Sphere(Vector(2, 0, 0.1), 0.2, Color(0, 1, 1));
    Sphere s2 = Sphere(Vector(0, 2, 0.1), 0.2, Color(1, 0, 1));
    Sphere s3 = Sphere(Vector(0, -3, 0.1), 0.2, Color(1, 1, 0));
    Sphere s4 = Sphere(Vector(-2, 0, 0.1), 0.2, Color(0, 0, 0));


    Plane p1 = Plane(Vector(0, 0, 0), Vector(0, 0, 1), Color(1, 1, 1));


    Box b1 = Box(Vector(-10.5226, -2.22101, -2.53902), Vector(3.58757, 2.52169, 1.53902), Color(1, 0, 0));

    Box b2 = Box(Vector(0, -2, 0.1), 0.4, 0.4, 0.4, Color(0, 0.4, 0.7));

    Box b3 = Box(Vector(2, 0, 0), 4, 0.05, 0.05, Color(1, 1, 1));

    Triangle t1 = Triangle(Vector(2, 0, 0.1), Vector(0, 2, 0.1), Vector(0, -2, 0.1), Color(1, 1, 0.5));
    //Triangle t2 = Triangle(Vector(-2, 0, 0.1), Vector(0, -2, 0.1), Vector(0, 2, 0.1), Color(0.4, 1, 1));
    Triangle t2 = Triangle({-2, 0, 0.1}, {0, 2, 0.1}, {0, -2, 0.1}, Color(0.4, 1, 1));


    Box b4 = Box(Vector(-2, -3.2, -2), Vector(4, 2.2, 2), Color(1, 1, 1));


    Scene scene = Scene(cam);
/*/
    scene.addShape(&s);
    scene.addShape(&s1);
    scene.addShape(&s2);
    scene.addShape(&s3);
    scene.addShape(&s4);

    scene.addShape(&p1);

    //scene.addShape(&b1);
    scene.addShape(&b2);
    scene.addShape(&b3);
    //scene.addShape(&b4);

    scene.addShape(&t1);
    scene.addShape(&t2);

    scene.addShape(&t2);

    scene.addShape(&p1);

    //scene.addShape(&b1);

    scene.addShape(&p1);
/**/
    scene.addShape(&p1);


    OBJLoader objLoader = OBJLoader("untitled8.obj");
    objLoader.LoadOBJ();

    Object object = objLoader.getObject(); // get the first Object inside the obj file
    scene.addShapes(object.getTriangles());




    //Sphere sp1 = {{1.33,-0.69,-1},1,{1,1,1}};

    Sphere sp1 = {{6,-0.8,1.27f},0.5f,{1,1,1}};

    //Box sp1 = {{1.33,0.2,0.5},1,1,1};
    //Sphere sp1 = {{10,0,2},1,{1,1,1}};
    sp1.setMaterial({{1,1,1},0,0,1,1.025f});


    scene.addShape(&sp1);

    Light light = {{-3,0,-1},{1,0,0.2},1};

    Light light1 = {{4,2,1},{0,1,1},1};

    Light light2 = {{4,-1.5,0},{1,0,0},1};

    Light light3 = {{1.33,-0.69,1},{1,1,0},1};

    Light light4 = {{1.33,-0.69,10},{0.125,0.125,0.125},100};


    //light.setPosition({-3,0,4});
    //light1.setPosition({10,0,4});
    light2.setPosition({2.5,-2,2});
    light3.setPosition({1.3,-1,2});
    /*/
    light3.setPosition({1.33,-0.69,7});
    light3.setPosition({1.33,-0.39,7});
    light3.setPosition({1.33,-0.09,7});
    light3.setPosition({1.33,0.29,7});


    light3.setPosition({1.33,0.59,7});
    light3.setPosition({1.33,0.89,7});
    light3.setPosition({1.33,1.19,7});/**/


    /*/
    light3.setPosition({1.33,1.59,7});
    light2.setPosition({1.33,-0.7,7});
    light3.setIntensity(25);
    light2.setIntensity(25);/**/

/**/
    //light2.setPosition({1.33,-0.7,2});
    scene.addLight(&light);
    scene.addLight(&light1);
    scene.addLight(&light2);
    scene.addLight(&light3);/**/

/*/
    Plane pl = {{5,0,3},{5,0,-1}};
    Material mat = {{},0.0,1,0};
    pl.setMaterial(mat);
    scene.addShape(&pl);/**/

    /*/scene.addLight(&light4);/**/

    scene.render();
    scene.drawImage();


    return 0;
}

