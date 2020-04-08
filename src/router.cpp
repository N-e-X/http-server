#include "router.hpp"
#include "HomeController.hpp"

using std::function;

vector<RouteMap> GetHomeControllerRoutesMap();

/** 
 * Регистрация маршрутов контроллеров 
 */
vector<vector<RouteMap>> RegisterControllersRoutesMap()
{
    return vector<vector<RouteMap>>
    {
        GetHomeControllerRoutesMap()
        // сюда добавлять новые методы получения маршрутов контроллеров
    };
}

vector<RouteMap> GetHomeControllerRoutesMap()
{
    vector<RouteMap> routesMap
    {
        RouteMap(
            "index", 
            http::Method::GET, 
            [](const http::Request* request) { HomeController homeController; return homeController.Index(request);}
        ),
        RouteMap(
            "newPage", 
            http::Method::GET, 
            [](const http::Request* request) { HomeController homeController; return homeController.NewPage(request);}
        )
    };

    return routesMap;
}

vector<RouteMap> GetRoutesMap()
{
    auto controllersRoutesMap = RegisterControllersRoutesMap();

    vector<RouteMap> routesMap;
    for (auto &&controllerRoutesMap : controllersRoutesMap)
    {
        routesMap.insert(routesMap.end(), controllerRoutesMap.begin(), controllerRoutesMap.end());
    }

    return routesMap;
}


