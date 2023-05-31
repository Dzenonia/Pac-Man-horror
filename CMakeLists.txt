cmake_minimum_required(VERSION 3.21)
project(PacMan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
#)
#
#FetchContent_MakeAvailable(googletest)
#
#
#include(FetchContent)
#FetchContent_Declare(
#        spdlog
#        URL https://github.com/gabime/spdlog/archive/refs/heads/v1.x.zip
#)
#
#FetchContent_MakeAvailable(spdlog)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(PacMan
        main.cpp main_window.cpp main_window.h Level/level_field.cpp Level/level_field.h Level/field_generator.cpp Level/field_generator.h Level/bot.cpp Level/bot.h Level/hero.cpp Level/level_graph.cpp Level/level_graph.h Controller/controller.cpp Controller/controller.h View/view.cpp View/view.h View/scene.cpp View/scene.h Level/level.cpp Level/level.h Level/hero.h GraphicsOgjects/GraphicsField.cpp GraphicsOgjects/GraphicsField.h GraphicsOgjects/Pac-Man.cpp GraphicsOgjects/Pac-Man.h Level/fieldF.cpp Level/fieldF.h
        resources.qrc GraphicsOgjects/GraphicsCoin.cpp GraphicsOgjects/GraphicsCoin.h rays/my_scene.cpp rays/graphics_polygon.cpp rays/polygon.cpp
        rays/ray.cpp rays/my_view.cpp rays/controllerRays.cpp GraphicsOgjects/score.cpp GraphicsOgjects/score.h GraphicsOgjects/GraphicsGhost.cpp GraphicsOgjects/GraphicsGhost.h)

target_link_libraries(PacMan
        Qt::Core
        Qt::Gui
        Qt::Widgets
        #        gtest
        )

#add_test(rays ray)

