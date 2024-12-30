cmake_minimum_required(VERSION 3.20)

project(QtCircularBuffer VERSION 0.0.1 LANGUAGES CXX)

option(QT_IMPLEMANTATION "Use Qt implementation" OFF)
option(BUILD_SHARED "Build as shared lib" ON)
option(BUILD_TESTS "Build with tests" ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(QT_IMPLEMANTATION)
find_package(Qt6 REQUIRED Core)
qt_standard_project_setup()
endif()

add_subdirectory(src)
if(BUILD_TESTS)
add_subdirectory(test)
endif()