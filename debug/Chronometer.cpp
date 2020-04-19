//
// Created by Jacob on 19.04.2020.
//

#include <iostream>
#include <utility>
#include "Chronometer.h"


Chronometer::Chronometer(const std::string message) {
    start(message);
}

void Chronometer::start(std::string message) {
    std::cout << "Starting: " << message.data() << std::endl;

    this->message = std::move(message);
    startvalue = std::chrono::high_resolution_clock::now();
}

void Chronometer::stop() {

    stopvalue = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stopvalue - startvalue);

    std::cout << message.data() << " elapsed time: " << duration_ms.count()/1000.0f << " s"<<std::endl;
}
