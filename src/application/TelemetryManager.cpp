#include "TelemetryManager.hpp"
#include <spdlog/spdlog.h>

TelemetryManager::TelemetryManager(std::unique_ptr<IDataSource> source, FlightLogic logic)
    : _dataSource(std::move(source)), _logic(logic) {}

void TelemetryManager::update() {
    // 1. Obtener datos de la infraestructura
    auto frame = _dataSource->readFrame();
    
    // 2. Aplicar lógica de negocio (Dominio)
    if (_logic.isIgnitionDetected(frame)) {
        _currentPhase = 1; // Cambiamos el estado interno del Manager para siempre
        spdlog::info(">>> EVENTO: IGNICIÓN CONFIRMADA - DESPEGUE EN CURSO <<<");
    }

    frame.flight_phase = _currentPhase;

    // 3. Guardar resultados de forma segura
    {
        std::lock_guard<std::mutex> lock(_frameMutex);
        _lastFrame = frame;
    }
}

TelemetryFrame TelemetryManager::getLastFrame() const {
    std::lock_guard<std::mutex> lock(_frameMutex);
    return _lastFrame;
}