//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_CHRONOMETER_H
#define RAYTRACER_CHRONOMETER_H

#include <chrono>
#include <xstring>


class Chronometer {
public:
    Chronometer(std::string message);
    void start(std::string message);
    void stop();


private:
    std::string message = "";
    std::chrono::time_point<std::chrono::high_resolution_clock> startvalue;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopvalue;
};


#endif //RAYTRACER_CHRONOMETER_H
