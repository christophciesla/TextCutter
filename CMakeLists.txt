cmake_minimum_required(VERSION 3.7.0)

project(TextCutter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/source)

set(GUI_HDRS
    source/gui/main_window.h
    )
set(GUI_SRCS
    source/gui/main_window.cpp
    )

add_executable(TextCutter WIN32
    ${GUI_HDRS}
    ${GUI_SRCS}
    source/main.cpp
    README.md
    .gitignore
)

target_link_libraries(TextCutter Qt5::Widgets)

if(WIN32)
    target_link_libraries(TextCutter Qt5::WinMain)
    add_custom_command(TARGET TextCutter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:TextCutter>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:TextCutter>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:TextCutter>
        )
endif (WIN32)
