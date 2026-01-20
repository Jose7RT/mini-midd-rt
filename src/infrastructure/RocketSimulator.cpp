#include "RocketSimulator.hpp"
#include <chrono>

RocketSimulator::RocketSimulator() {
    _startTime = getCurrentTimeSeconds();
}

TelemetryFrame RocketSimulator::readFrame() {
    double now = getCurrentTimeSeconds();
    float t = static_cast<float>(now - _startTime);

    TelemetryFrame frame;
    frame.timestamp = now;
    
    frame.altitude = (_initialVelocity * t) - (0.5f * _gravity * t * t);
    if (frame.altitude < 0) frame.altitude = 0;

    frame.velocity = _initialVelocity - (_gravity * t);
    frame.acceleration = (t < 2.0f) ? 25.0f : -_gravity; 
    frame.battery_level = 98.5f - (t * 0.01f);
    frame.flight_phase = 0; 

    return frame;
}

double RocketSimulator::getCurrentTimeSeconds() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count() / 1000.0;
}