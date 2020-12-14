cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME "CPPLS2_SERVER")
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
)

include("${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt")

target_include_directories(
    ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../asio-1.18.0/include
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dropbox)