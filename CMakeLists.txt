cmake_minimum_required(VERSION 3.15)
project(Raytracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Raytracer main.cpp world/Camera.cpp math/Matrix.cpp math/Ray.cpp math/Vector.cpp geometry/Shape.cpp geometry/Shape.h geometry/Sphere.cpp geometry/Sphere.h geometry/Triangle.cpp geometry/Triangle.h geometry/Plane.cpp geometry/Plane.h debug/Chronometer.cpp debug/Chronometer.h world/Scene.cpp world/Scene.h world/Object.cpp world/Object.h)