cmake_minimum_required(VERSION 3.7.0)

project(TextCutter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)

if(WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    # Ask Qt5 where to put the translations
    execute_process(
        COMMAND ${QT5_QMAKE_EXECUTABLE} -query QT_INSTALL_TRANSLATIONS
        OUTPUT_VARIABLE qt_translations_dir OUTPUT_STRIP_TRAILING_WHITESPACE)
    # make sure we have / and not \ as qmake gives on windows
    file(TO_CMAKE_PATH "${qt_translations_dir}" qt_translations_dir)
    set(QT_TRANSLATIONS_DIR ${qt_translations_dir} CACHE PATH
        "The location of the Qt translations" FORCE)
endif (WIN32)

set(LIBCUTTER_DIR ${CMAKE_SOURCE_DIR}/source/libcutter)

add_subdirectory(source)
