//
// Created by Jacob on 19.04.2020.
//

#ifndef RAYTRACER_TIMER_H
#define RAYTRACER_TIMER_H

#include <chrono>
#include <string>


class Timer {
public:
    Timer(std::string message);
    void start(std::string message);
    void getTime();
    void stop();


private:
    std::string message = "";
    std::chrono::time_point<std::chrono::high_resolution_clock> startvalue;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopvalue;
};


#endif //RAYTRACER_TIMER_H
