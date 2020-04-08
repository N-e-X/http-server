#include "HomeController.hpp"

HomeController::HomeController() {}

http::Response* HomeController::Index(const http::Request*) {
    return new http::Response();
}

http::Response* HomeController::NewPage(const http::Request*) {
    return new http::Response();
}

HomeController::~HomeController() {
    // delete _routesMap;
}

