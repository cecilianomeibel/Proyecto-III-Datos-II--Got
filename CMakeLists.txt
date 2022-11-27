cmake_minimum_required(VERSION 3.23)
project(Got)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server src/Server.cpp)
add_executable(Client src/Client.cpp)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/include/mysql-cppconn-8/jdbc)

include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR})
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR})

target_link_libraries(Server mysqlcppconn)
target_compile_features(Server PRIVATE cxx_range_for)
