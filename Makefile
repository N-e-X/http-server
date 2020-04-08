INCLUDE = -I./include -I./include/http -I./include/http/exceptions -I./include/controllers -I./include/server -I./include/server/exceptions -I./include/utils
FLAGS = -Wall -g -std=c++17 $(INCLUDE)
TEST_INCLUDE = -I./tests/unitTests -I./tests/fakeClasses
TEST_FLAGS = $(FLAGS) ${TEST_INCLUDE}

CONTROLLERS_CPP = src/controllers/HomeController.cpp
HTTP_CPP = src/http/Method.cpp src/http/Protocol.cpp src/http/StatusCode.cpp
SERVER_CPP = src/server/HttpHandler.cpp src/server/Parser.cpp 
CPP = src/router.cpp ${CONTROLLERS_CPP} ${HTTP_CPP} ${SERVER_CPP}

BUILD_CPP = Main.cpp ${CPP}
TEST_CPP = Tests.cpp ${CPP}

# all: g++ main.cpp src/server.cpp src/controller.cpp src/parser.cpp src/response_handler.cpp src/router.cpp -o http_server_app.exe
build: 
	g++ ${FLAGS} ${BUILD_CPP} -o http_server_app.exe

# test: 
# 	g++ ${FLAGS} tests/routerTests.cpp src/http/Request.cpp src/http/Response.cpp src/controllers/HomeController.cpp src/router.cpp -o http_server_app_test.exe

test: 
	g++ ${TEST_FLAGS} ${TEST_CPP} -o http_server_app_test.exe

clean:
	rm *.exe