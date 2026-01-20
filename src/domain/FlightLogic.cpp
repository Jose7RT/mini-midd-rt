#include "FlightLogic.hpp"

FlightLogic::FlightLogic(float ignitionThreshold) 
    : _ignitionThreshold(ignitionThreshold) {}

bool FlightLogic::isIgnitionDetected(const TelemetryFrame& frame) {
    bool currentlyIgnited = frame.acceleration > _ignitionThreshold;

    if (currentlyIgnited && !_wasIgnited) {
        _wasIgnited = true;
        return true;
    }
    
    return false;
}