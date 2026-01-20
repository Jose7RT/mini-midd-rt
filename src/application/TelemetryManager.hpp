#pragma once
#include "IDataSource.hpp"
#include "FlightLogic.hpp"
#include <memory>
#include <mutex>

class TelemetryManager {
public:
    TelemetryManager(std::unique_ptr<IDataSource> source, FlightLogic logic);

    void update();
    
    // Es const gracias a que el mutex es mutable
    TelemetryFrame getLastFrame() const;

private:
    std::unique_ptr<IDataSource> _dataSource;
    FlightLogic _logic;
    TelemetryFrame _lastFrame;
    int _currentPhase = 0; // 0: Pre-lanzamiento, 1: Ascenso
    mutable std::mutex _frameMutex; // Permite bloquear/desbloquear incluso en métodos const
};