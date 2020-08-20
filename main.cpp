
#include <iostream>
#include <cmath>
#include <memory>
#include "math/Vector.h"
#include "world/Camera.h"
#include "geometry/Sphere.h"
#include "world/Scene.h"
#include "world/Skybox.h"
#include "geometry/Plane.h"
#include "geometry/Triangle.h"
#include "obj/OBJLoader.h"
#include "debug/Timer.h"
#include "rendering/Image.h"


int main() {


    Camera cam = Camera(Vector(10, 0, 2), Vector(1, 0, 0), 1920, 1080, 2);//5

    cam.setPosition({10,0,2});
    cam.lookAt(Vector(0, 0, 0));

    //cam.setNumberOfPixel(100000);// max number of pixels for the image  // old full hd car: 874s new full hd car: 223.9s new full hd car 40 split Bounding Box split: 108.2s

    //cam.setNumberOfPixel(50000);// max number of pixels for the image
    //cam.setWidthToHeight(16.0f / 9.0f); // Height to width ratio

    cam.print();

/*/
    Sphere s = Sphere(Vector(0, 0, 0.5), 1);
    //s.setMaterial(new Material{{0,0,0},0,1,0});



    Sphere s1 = Sphere(Vector(2, 0, 0.1), 0.2, Color(0, 1, 1));
    Sphere s2 = Sphere(Vector(0, 2, 0.1), 0.2, Color(1, 0, 1));
    Sphere s3 = Sphere(Vector(0, -3, 0.1), 0.2, Color(1, 1, 0));
    Sphere s4 = Sphere(Vector(-2, 0, 0.1), 0.2, Color(0, 0, 0));





    Box b1 = Box(Vector(-10.5226, -2.22101, -2.53902), Vector(3.58757, 2.52169, 1.53902), Color(1, 0, 0));

    Box b2 = Box(Vector(0, -2, 0.1), 0.4, 0.4, 0.4, Color(0, 0.4, 0.7));

    Box b3 = Box(Vector(2, 0, 0), 4, 0.05, 0.05, Color(1, 1, 1));

    Triangle t1 = Triangle(Vector(2, 0, 0.1), Vector(0, 2, 0.1), Vector(0, -2, 0.1), Color(1, 1, 0.5));
    //Triangle t2 = Triangle(Vector(-2, 0, 0.1), Vector(0, -2, 0.1), Vector(0, 2, 0.1), Color(0.4, 1, 1));
    Triangle t2 = Triangle({-2, 0, 0.1}, {0, 2, 0.1}, {0, -2, 0.1}, Color(0.4, 1, 1));


    Box b4 = Box(Vector(-2, -3.2, -2), Vector(4, 2.2, 2), Color(1, 1, 1));

/**/

    Light light = {{0, 0, 1.7}, {0.3, 0.7, 1}, 2.5};
    Light light1 = {{-2, 2, 1}, {1, 0.7, 0}, 1.5};
    Light light2 = {{-2, -2, 1}, {1, 0.2, 0}, 1.5};
    Light light3 = {{2, -2, 1}, {1, 0.6, 0.0}, 0.5};
    Light light4 = {{0, 0, 2}, {0.075, 0.125, 0.125}, 0.5};

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

    const std::vector<Light *> &lightvec = /*/{};/*/{&light/*/, &light1/**//*/, &light2/*/,&light3,&light4/**/};/**/

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

    /// wtc

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

    Material* material = new Material{{1.0,1.0,1.0},0.20,0.9,0.0,1.025};
    object.setMaterial(material);

    Material* material2 = new Material{{0.3,0.3,0.3},0.5,0.5,0.0,1.025};
    object2.setMaterial(material2);

    scene.addShapes(object.getTriangles());
    scene.addShapes(object2.getTriangles());

/*/


    auto* materialPlane = new Material{{1,1,1},0,0,0,0};

    auto* p1 = new Plane({0, 0, -1.3}, {0, 0, 1}, materialPlane);

    scene.addShape(p1);


    /// normal


    OBJLoader objLoader = OBJLoader("dragon1.obj"); //car // dragon1 // untitled11 -> statue // untitled9 // skull // statue //worldtrade
    objLoader.LoadOBJ();
    Object object = objLoader.getObject(); // get the first Object inside the obj file
    //Material* material = new Material{{0.65,0.75,0.35},0.00,1.0,0.0,0};
    auto* material = new Material{/**/{0.75,0.8,0.7}/*/{0.7,0.8,0.7}/**/,/**/0.00f,0.00f,0.0f,/**//*/0.0f/*/1.36f/**/};/*/0.00625f,0.0f,0.8f,1.36f};/**/ // 1.36 = Water
    object.setMaterial(material);
    scene.addShapes(object.getTriangles());



    //OBJLoader objLoaderb = OBJLoader("dragon1.obj"); //car // dragon1 // untitled11 -> statue // untitled9 // skull // statue //worldtrade
    //objLoaderb.LoadOBJ();
    //Object objectaa = objLoaderb.getObject(); // get the first Object inside the obj file
    ////Material* material = new Material{{0.65,0.75,0.35},0.00,1.0,0.0,0};
    //auto* material11 = new Material{/**/{1,0,0}/*/{0.7,0.8,0.7}/**/,/**/0.100f,1.00f,0.0f,/**//*/0.0f/*/1.36f/**/};/*/0.00625f,0.0f,0.8f,1.36f};/**/ // 1.36 = Water
    //objectaa.setMaterial(material11);
    //objectaa.add({0,0,2});
    //scene.addShapes(objectaa.getTriangles());


    /**/

    //Sphere* sphere = new Sphere{{},1};
    //sphere->setMaterial(material);
    //scene.addShape(sphere);


/**/
    //scene.addShape(&s);

    Skybox skybox = Skybox();
    scene.setSkybox(&skybox);

    scene.buildBoundingBox();


    Vector Origin = {3, -0.2, 2};
    Vector LookAt = {3,-0.2,1};


    LookAt = {0,0,0.3}; // 1 1 0.5
    Origin={0, 0, 1}; // 1 1 0.15  //{0, 0, 1.0}


    float images = /**/1;/*/100.0f;/**/

    Timer timermovie = Timer("Video");

    float pi = 3.14159265f;
    float progress;
    float dist = 4;

    for (int i = 0; i < images; ++i) {


        progress = /**/0.25f;/*/(float) i / images;/**/

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

        //material->setRefractiveIndex( 0.6f * (1 + cos(progress*2*pi)));

        Vector offset = {(float)(dist * sin(progress*2.0f*pi)), (float)(dist * cos(progress*2*pi)),0/* cos(progress*2*pi)*/};

        cam.setPosition(Origin + offset);
        cam.lookAt(LookAt);

        scene.setCamera(cam);
        scene.render();
        scene.drawImage(i);
    }
    timermovie.stop();

    return 0;
}

