#include <drogon/drogon.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <ctime>
#include <string>

int main() {
    using namespace drogon;

    // Register handler for GET /api/health
    app().registerHandler(
        "/api/health",
        [](const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {
            // Obtain current time as ISO-like string
            auto now = std::chrono::system_clock::now();
            std::time_t tt = std::chrono::system_clock::to_time_t(now);
            // ctime gives a trailing newline; we'll trim it
            std::string timestr = std::ctime(&tt);
            if (!timestr.empty() && timestr.back() == '\n') timestr.pop_back();

            Json::Value json;
            json["status"] = "ok";
            json["time"] = timestr;

            auto resp = HttpResponse::newHttpJsonResponse(json);
            callback(resp);
        },
        {Get} // method
    );

    // Listen on all interfaces, port 3000
    app().addListener("0.0.0.0", 3000);
    // Optionally: set number of threads (by default drogon config decides). Example:
    // app().setThreadNum(4);

    spdlog::info("Starting server on 0.0.0.0:3000");
    app().run();
    return 0;
}
