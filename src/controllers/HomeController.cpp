#include "HomeController.hpp"

HomeController::HomeController() {}

http::Response* HomeController::Index(const http::Request*) {
    auto response = new http::Response("Hello, my friend! This is the index page! Welcome to <a href=\"newPage\">another page</a>");
    return response;
}

http::Response* HomeController::NewPage(const http::Request*) {
    auto response = new http::Response("And this is the another new page!<br><br><a href=\"/\">Go to index</a>");
    return response;
}

HomeController::~HomeController() {
    // delete _routesMap;
}

