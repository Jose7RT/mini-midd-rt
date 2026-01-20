#pragma once
#include <drogon/WebSocketController.h>
#include <memory>
#include "TelemetryManager.hpp"

class WebStreamController : 
    public drogon::WebSocketController<WebStreamController>,
    public std::enable_shared_from_this<WebStreamController> 
{
public:
    static void setManager(std::shared_ptr<const TelemetryManager> manager);

    // Métodos obligatorios de Drogon
    void handleNewMessage(const drogon::WebSocketConnectionPtr&, std::string&&, const drogon::WebSocketMessageType&) override;
    void handleNewConnection(const drogon::HttpRequestPtr&, 
                             const drogon::WebSocketConnectionPtr&) override;
    void handleConnectionClosed(const drogon::WebSocketConnectionPtr&) override;

    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/telemetry");
    WS_PATH_LIST_END

private:
    static inline std::shared_ptr<const TelemetryManager> _manager = nullptr;
    void _sendData(const drogon::WebSocketConnectionPtr& conn);
};