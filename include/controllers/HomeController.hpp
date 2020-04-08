#if !defined(HOME_CONTROLLER_HPP)
#define HOME_CONTROLLER_HPP

#include "Request.hpp"
#include "Response.hpp"

// #include <map>
// using std::map;

class HomeController
{
private:

public:
    HomeController();
    http::Response* Index(const http::Request*);
    http::Response* NewPage(const http::Request*);
    ~HomeController();
};

#endif // HOME_CONTROLLER_HPP
