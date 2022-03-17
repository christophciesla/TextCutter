cmake_minimum_required(VERSION 3.7.0)

project(TextCutter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/source/libcutter
    ${CMAKE_SOURCE_DIR}/source/cutter_gui
    )

set(CUTTER_HDRS
    source/libcutter/cutter/cut_text.h
    )

set(CUTTER_SRCS
    source/libcutter/cutter/cut_text.cpp
    )

add_library(cutter
    ${CUTTER_HDRS}
    ${CUTTER_SRCS}
    )

target_link_libraries(cutter Qt5::Core)

set(GUI_HDRS
    source/cutter_gui/gui/main_window.h
    )

set(GUI_SRCS
    source/cutter_gui/gui/main_window.cpp
    )

add_executable(textcutter-gui WIN32
    ${GUI_HDRS}
    ${GUI_SRCS}
    source/cutter_gui/main.cpp
    README.md
    .gitignore
)

target_link_libraries(textcutter-gui cutter Qt5::Widgets)

if(WIN32)
    target_link_libraries(textcutter-gui Qt5::WinMain)
    add_custom_command(TARGET textcutter-gui POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:textcutter-gui>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:textcutter-gui>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:textcutter-gui>
        )
endif (WIN32)
