cmake_minimum_required(VERSION 3.7.0)

project(TextCutter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

set(LIBCUTTER_DIR ${CMAKE_SOURCE_DIR}/source/libcutter)

add_subdirectory(source)
