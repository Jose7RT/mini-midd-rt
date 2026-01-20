#pragma once
#include "TelemetryFrame.hpp"

class IDataSource {
public:
    virtual ~IDataSource() = default;
    virtual TelemetryFrame readFrame() = 0;
};