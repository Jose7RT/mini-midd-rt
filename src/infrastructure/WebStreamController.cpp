#include "WebStreamController.hpp"
#include <spdlog/spdlog.h>
#include <drogon/HttpAppFramework.h>
#include <json/json.h>

using namespace drogon;

void WebStreamController::setManager(std::shared_ptr<const TelemetryManager> manager) {
    _manager = manager;
}

void WebStreamController::handleNewMessage(const WebSocketConnectionPtr&, std::string&&, const WebSocketMessageType&) {}

void WebStreamController::handleNewConnection(const HttpRequestPtr& req, 
                                              const WebSocketConnectionPtr& conn) {
    spdlog::info("Nuevo cliente conectado desde: {}", conn->peerAddr().toIp());
    _sendData(conn);
}

void WebStreamController::handleConnectionClosed(const WebSocketConnectionPtr& conn) {
    spdlog::info("Cliente desconectado: {}", conn->peerAddr().toIp());
}

void WebStreamController::_sendData(const WebSocketConnectionPtr& conn) {
    if (!conn->connected() || !_manager) return;

    auto frame = _manager->getLastFrame();

    Json::Value json;
    json["ts"] = frame.timestamp;
    json["alt"] = frame.altitude;
    json["vel"] = frame.velocity;
    json["phase"] = frame.flight_phase;

    conn->send(json.toStyledString());

    // Recursividad asíncrona usando el Event Loop de Drogon
    auto self = shared_from_this();
    app().getLoop()->runAfter(0.02, [this, conn, self]() {
        _sendData(conn);
    });
}