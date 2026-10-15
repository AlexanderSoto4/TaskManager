cmake_minimum_required(VERSION 3.16)
project(GestorDeTareas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GestorDeTareas
    main.cpp
    MainWindow.h
    MainWindow.cpp
    Tarea.h
    Tarea.cpp
    ListaDeTareas.h
    ListaDeTareas.cpp
)

target_link_libraries(GestorDeTareas PRIVATE Qt6::Widgets)