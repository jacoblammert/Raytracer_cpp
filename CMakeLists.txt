cmake_minimum_required(VERSION 3.9)
project(Raytracer)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP REQUIRED)

add_executable(Raytracer main.cpp world/Camera.cpp math/Matrix.cpp math/Ray.cpp math/Vector.cpp geometry/Shape.cpp geometry/Shape.h geometry/Sphere.cpp geometry/Sphere.h geometry/Triangle.cpp geometry/Triangle.h geometry/Plane.cpp geometry/Plane.h debug/Chronometer.cpp debug/Chronometer.h world/Scene.cpp world/Scene.h world/Object.cpp world/Object.h world/Light.cpp world/Light.h geometry/Box.cpp geometry/Box.h world/BoundingBox.cpp world/BoundingBox.h world/OBJLoader.cpp world/OBJLoader.h)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Raytracer PUBLIC OpenMP::OpenMP_CXX)
endif()

