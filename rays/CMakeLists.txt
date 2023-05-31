cmake_minimum_required(VERSION 3.21)
project(rays)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(rays
        main.cpp
        main_window.cpp
        ray.cpp
        polygon.cpp
        controllerRays.cpp
        my_view.cpp
        my_scene.cpp
        tests.cpp graphics_polygon.cpp)

target_link_libraries(rays
        Qt::Core
        Qt::Gui
        Qt::Widgets
        gtest
        )

add_test(rays ray)

