#include <spdlog/spdlog.h>
#include "FlightLogic.hpp"
#include "TelemetryManager.hpp"
#include "RocketSimulator.hpp"
#include "WebStreamController.hpp"

int main() {
    // Configuración básica de spdlog
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    spdlog::info("Iniciando Middleware del Cohete...");
    
    // --- 1. CAPA DE DOMINIO ---
    FlightLogic logic(15.0f);

    // --- 2. CAPA DE INFRAESTRUCTURA (ENTRADA) ---
    auto simulator = std::make_unique<RocketSimulator>();

    // --- 3. CAPA DE APLICACIÓN ---
    auto manager = std::make_shared<TelemetryManager>(std::move(simulator), logic);

    // --- 4. CAPA DE INFRAESTRUCTURA (SALIDA/RED) ---
    // Configuramos el controlador para que use nuestro manager
    WebStreamController::setManager(manager);

    // Hilo para que el Manager actualice los datos de forma independiente
    std::jthread worker([manager](std::stop_token st) {
        while (!st.stop_requested()) {
            manager->update();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });

    // Lanzar servidor Drogon en el puerto 8080
    drogon::app().addListener("0.0.0.0", 8080).run();

    return 0;
}