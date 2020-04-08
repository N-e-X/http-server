#if !defined(ROUTE_MAP_HPP)
#define ROUTE_MAP_HPP

#include <functional>
#include <vector>
#include "Response.hpp"
#include "Request.hpp"

using std::function;
using std::vector;

typedef struct RouteMap {
    const char* Route;
    http::Method Method;
    function<http::Response*(const http::Request*)> Action;
    RouteMap(const char* route, http::Method method, function<http::Response*(const http::Request*)> handler)
    {
        Route = route;
        Method = method;
        Action = handler;
    };
} RouteMap;

#endif // ROUTE_MAP_HPP
