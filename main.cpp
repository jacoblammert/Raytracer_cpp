
#include <iostream>
#include "math/Vector.h"
#include "world/Camera.h"
#include "geometry/Sphere.h"
#include "world/Scene.h"
#include "world/Skybox.h"
#include "geometry/Plane.h"
#include "geometry/Triangle.h"
#include "obj/OBJLoader.h"
#include "debug/Chronometer.h"
#include "rendering/Image.h"

int main() {


    Camera cam = Camera(Vector(10, 0, 2), Vector(1, 0, 0), 1920, 1080, 2);//5

    cam.setPosition({10,0,2});
    cam.lookAt(Vector(0, 0, 0));

    cam.setNumberOfPixel(200000);// max number of pixels for the image  // old full hd car: 874s new full hd car: 223.9s

    //cam.setNumberOfPixel(50000);// max number of pixels for the image
    cam.setWidthToHeight(16.0f / 9.0f); // Height to width ratio

    cam.print();


    Sphere s = Sphere(Vector(0, 0, 0), 0.2, Color(0, 0, 1));

    Sphere s1 = Sphere(Vector(2, 0, 0.1), 0.2, Color(0, 1, 1));
    Sphere s2 = Sphere(Vector(0, 2, 0.1), 0.2, Color(1, 0, 1));
    Sphere s3 = Sphere(Vector(0, -3, 0.1), 0.2, Color(1, 1, 0));
    Sphere s4 = Sphere(Vector(-2, 0, 0.1), 0.2, Color(0, 0, 0));


    Plane p1 = Plane(Vector(0, 0, 0.1), Vector(0, 0, 1), Color(1, 1, 1));


    Box b1 = Box(Vector(-10.5226, -2.22101, -2.53902), Vector(3.58757, 2.52169, 1.53902), Color(1, 0, 0));

    Box b2 = Box(Vector(0, -2, 0.1), 0.4, 0.4, 0.4, Color(0, 0.4, 0.7));

    Box b3 = Box(Vector(2, 0, 0), 4, 0.05, 0.05, Color(1, 1, 1));

    Triangle t1 = Triangle(Vector(2, 0, 0.1), Vector(0, 2, 0.1), Vector(0, -2, 0.1), Color(1, 1, 0.5));
    //Triangle t2 = Triangle(Vector(-2, 0, 0.1), Vector(0, -2, 0.1), Vector(0, 2, 0.1), Color(0.4, 1, 1));
    Triangle t2 = Triangle({-2, 0, 0.1}, {0, 2, 0.1}, {0, -2, 0.1}, Color(0.4, 1, 1));


    Box b4 = Box(Vector(-2, -3.2, -2), Vector(4, 2.2, 2), Color(1, 1, 1));



    Light light = {{2, 2, 1}, {0.7, 0.7, 0}, 3};
    Light light1 = {{-2, 2, 1}, {1, 0.7, 0}, 3};
    Light light2 = {{-2, -2, 1}, {1, 0.2, 0}, 3};
    Light light3 = {{2, -2, 1}, {1, 0.6, 0.0}, 3};
    Light light4 = {{0, 0, 2}, {0.075, 0.125, 0.125}, 3};

    Light* light5 = new Light{};

    std::shared_ptr<Light> light6 = std::make_shared<Light>(Light{});

    //light.setPosition({0,0,4});
    //light1.setPosition({-0.5,-0.5,1});
    //light2.setPosition({0.5,0.5,1});
    //light3.setPosition({-0.5,0.5,2});
    //light4.setPosition({0.5,-0.5,2});

    /*/scene.addLight(&light);
    scene.addLight(&light1);
    scene.addLight(&light2);
    scene.addLight(&light3);/**/

    const std::vector<Light *> &lightvec = {&light/**/, &light1, &light2,&light3,&light4/**/};

    Scene scene = Scene(cam, lightvec);
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
    //scene.addShape(&p1);

/*/
    //OBJLoader objLoader = OBJLoader("dragon1.obj");
    //OBJLoader objLoader = OBJLoader("dragon.obj"); //car
    OBJLoader objLoader = OBJLoader("singleTower_mirror.obj"); //car
    //OBJLoader objLoader = OBJLoader("../models/wtcobj.obj");
    //OBJLoader objLoader = OBJLoader("wtcobj.obj");
    //OBJLoader objLoader = OBJLoader("dragon.obj");


    OBJLoader objLoader2 = OBJLoader("singleTower_metal.obj"); //car

    objLoader.LoadOBJ();
    objLoader2.LoadOBJ();

    Object object = objLoader.getObject(); // get the first Object inside the obj file
    Object object2 = objLoader2.getObject(); // get the first Object inside the obj file

    Material material = {{1.0,1.0,1.0},0.00,1.0,0.0,1.025};
    object.setMaterial(material);

    Material material2 = {{1.0,1.0,1.0},1.00,1.0,0.0,1.025};
    object2.setMaterial(material2);

    scene.addShapes(object.getTriangles());
    scene.addShapes(object2.getTriangles());

/*/

    OBJLoader objLoader = OBJLoader("car.obj"); //car
    objLoader.LoadOBJ();
    Object object = objLoader.getObject(); // get the first Object inside the obj file
    Material material = {{1.0,1.0,1.0},0.00,1.0,0.0,1.025};
    object.setMaterial(material);
    scene.addShapes(object.getTriangles());
/**/

    //Sphere sp1 = {{1.33,-0.69,-1},1,{1,1,1}};

    Sphere sp1 = {{4, -0.8, 1.27f}, 1.0f, {1, 0, 0}};



    //Box sp1 = {{1.33,0.2,0.5},1,1,1};
    //Sphere sp1 = {{10,0,2},1,{1,1,1}};
    sp1.setMaterial({{1, 0, 0}, 0.0, 0.2, 1, 1.025f});
    sp1.setMaterial({{1,1,1},0,1,0});
    //scene.addShape(&sp1);

    Box box = Box{{2.7,-1.3,0.5},1,1,1};
    box.setMaterial({{0.2,0.6,0.7},0,1,0});
    //scene.addShape(&box);


    Box box1 = Box{{2,1.3,0.5},2,1,1};
    box1.setMaterial({{1,0.1,0.1},1,0,0});
    //scene.addShape(&box1);


    Sphere sphere = {{2, 0.8, 1.27f}, 0.3f, {1, 0, 0}};
    sphere.setMaterial({{0, 1, 0}, 0.1, 0, 0.7, 1.035f});
    //scene.addShape(&sphere);





    /*

    //Image skies = Image("skies.ppm");

    Image skies = Image("Skies.ppm");//"picture80.ppm");

    Image skies = Image("skybox4.ppm");//"picture80.ppm");

    skies.loadImage();
    scene.setSkybox(&skies);
    //skies.saveImage(123456);

    /**/



    Skybox skybox = Skybox();
    //skybox.getColor();

    scene.setSkybox(&skybox);





    Sphere testMetal = {{3.44,-0.25,0.87},2};
    Sphere testMetal1 = {{5.44,-0.6,1},2};
    Sphere testMetal3 = {{5.44,1.6,3},1};

    Box testMetal2 = {{3.44,-0.25,0.0},10,10,0.2};


    testMetal.setMaterial({{1,1,1},0,1,0,1});

    //scene.addShape(&testMetal);
    //scene.addShape(&testMetal1);
    //scene.addShape(&testMetal2);
    //scene.addShape(&testMetal3);

/*/
    Light light = {{-3,0,-1},{1,0,0.2},1};

    Light light1 = {{4,2,1},{0,1,1},1};

    Light light2 = {{4,-1.5,0},{1,0,0},1};

    Light light3 = {{1.33,-0.69,1},{1,1,0},1};

    Light light4 = {{1.33,-0.69,10},{0.125,0.125,0.125},100};

/**/
    //light.setPosition({-3,0,4});
    //light1.setPosition({10,0,4});
    ////light2.setPosition({2.5,-2,2});
    ////light3.setPosition({1.3,-1,2});
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

/*/////
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

    scene.buildBoundingBox();

    /*/scene.render();/**/
    /*/scene.drawImage(0);/**/

/*/
    Vector Origin = {10,0,2};
    Vector Mid = {3.44,30,4};
    Vector Goal = {-4,0,2};

    float images = 101.0f;

    Chronometer chronomovie = Chronometer("Video");

    for (int i = 0; i < images; ++i) {

        Vector a = (Mid - Origin);
        a.scale(((float)i/images));
        Vector b = (Goal - a - Origin);
        b.scale(((float)i/images));
        Vector pos = Origin + a + b;

        cam.setPosition(pos);
        cam.lookAt({3.44, 0.166, 0.8786});

        scene.setCamera(cam);
        scene.render();
        scene.drawImage(i);
    }
    chronomovie.stop();
/**/

    Vector Origin = {3, -0.2, 2};
    Vector LookAt = {3,-0.2,1};
    LookAt = {3.44,-0.25,0.87};
    Origin = {3.44, -0.25, 1.5};


    LookAt = {0,0,0.5}; // 1 1 0
    Origin = {0, 0, 1.6}; // 1 1 0.15

    //LookAt = {0.0,0,0.8};//obj9
    //Origin = {0.0, 0, 1.4};//obj9

    float images = 100.0f;

    Chronometer chronomovie = Chronometer("Video");

    float pi = 3.14159265f;
    float progress;
    float dist = 3;

    for (int i = 0; i < images; ++i) {


        progress = (float) i / images;

        //material = {{1.0,1.0,1.0},0,1.0,0,1.025}; // Glas

        //object.setMaterial(material);

        //testMetal.setMaterial(material);

        /*/
        material = {{1.0,1.0,1.0},0,0.3,0.95,1.03}; // Glas
        testMetal1.setMaterial(material);

        material =  {{0.8,0.8,0.8},1,0.8,0.0,0.0}; // Metal
        testMetal2.setMaterial(material);



        material =  {{0.8,0.8,0.8},0,1,0.0,0.0}; // Mirror
        testMetal3.setMaterial(material);


        /**/

        Vector offset = {dist * sin(progress*2*pi), dist * cos(progress*2*pi), 0};

        cam.setPosition(Origin + offset);
        cam.lookAt(LookAt);

        scene.setCamera(cam);
        scene.render();
        scene.drawImage(i);
    }
    chronomovie.stop();

    return 0;
}

