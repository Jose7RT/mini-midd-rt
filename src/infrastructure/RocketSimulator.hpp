#pragma once
#include "IDataSource.hpp"

class RocketSimulator : public IDataSource {
public:
    RocketSimulator();
    TelemetryFrame readFrame() override;

private:
    double _startTime;
    const float _gravity = 9.81f;
    const float _initialVelocity = 50.0f;

    double getCurrentTimeSeconds() const;
};