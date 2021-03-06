cmake_minimum_required(VERSION 3.9)
project(Raytracer)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP REQUIRED)

add_executable(Raytracer main.cpp world/Camera.cpp math/Matrix.cpp math/Ray.cpp math/Vector.cpp geometry/Shape.cpp geometry/Shape.h geometry/Sphere.cpp geometry/Sphere.h geometry/Triangle.cpp geometry/Triangle.h geometry/Plane.cpp geometry/Plane.h debug/Timer.cpp debug/Timer.h world/Scene.cpp world/Scene.h obj/Object.cpp obj/Object.h world/Light.cpp world/Light.h geometry/Box.cpp geometry/Box.h world/BoundingBox.cpp world/BoundingBox.h obj/OBJLoader.cpp obj/OBJLoader.h geometry/Material.cpp geometry/Material.h geometry/Color.cpp geometry/Color.h rendering/Renderer.cpp rendering/Renderer.h rendering/Image.cpp rendering/Image.h world/Skybox.cpp world/Skybox.h geometry/Intersect.h)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Raytracer PUBLIC OpenMP::OpenMP_CXX)
endif()

