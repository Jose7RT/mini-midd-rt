#include <gtest/gtest.h>
#include "FlightLogic.hpp"
#include "TelemetryManager.hpp"
#include "IDataSource.hpp"

// Creamos una fuente de datos falsa para controlar exactamente qué recibe el Manager
class MockDataSource : public IDataSource {
public:
    TelemetryFrame fakeFrame;
    TelemetryFrame readFrame() override { return fakeFrame; }
};

// --- TESTS DE LÓGICA DE NEGOCIO (DOMAIN) ---
TEST(FlightLogicTest, DetectsIgnitionCorrectly) {
    FlightLogic logic(15.0f); // Umbral de 15g
    TelemetryFrame frame;

    frame.acceleration = 10.0f;
    EXPECT_FALSE(logic.isIgnitionDetected(frame)); // No debería detectar nada

    frame.acceleration = 16.0f;
    EXPECT_TRUE(logic.isIgnitionDetected(frame));  // Debería detectar ignición
}

// --- TESTS DEL MANAGER (APPLICATION) ---
TEST(TelemetryManagerTest, UpdatesLastFrameCorrectly) {
    // 1. Preparación
    auto mock = std::make_unique<MockDataSource>();
    mock->fakeFrame.altitude = 123.4f;
    mock->fakeFrame.acceleration = 5.0f;

    FlightLogic logic(15.0f);
    TelemetryManager manager(std::move(mock), logic);

    // 2. Ejecución
    manager.update();

    // 3. Verificación
    EXPECT_FLOAT_EQ(manager.getLastFrame().altitude, 123.4f);
}

TEST(TelemetryManagerTest, ChangesPhaseOnIgnition) {
    auto mock = std::make_unique<MockDataSource>();
    mock->fakeFrame.acceleration = 20.0f; // Por encima del umbral

    FlightLogic logic(15.0f);
    TelemetryManager manager(std::move(mock), logic);

    manager.update();

    // Verificamos que el Manager usó la lógica de negocio para cambiar la fase
    EXPECT_EQ(manager.getLastFrame().flight_phase, 1); // 1 = ASCENSO
}