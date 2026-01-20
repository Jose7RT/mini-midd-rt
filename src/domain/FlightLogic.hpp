#pragma once
#include "TelemetryFrame.hpp"

class FlightLogic {
public:
    explicit FlightLogic(float ignitionThreshold);
    bool isIgnitionDetected(const TelemetryFrame& frame);

private:
    float _ignitionThreshold;
    bool _wasIgnited = false;
};