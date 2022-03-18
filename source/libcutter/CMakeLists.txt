INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(CUTTER_HDRS
    cutter/cut_text.h
    )

set(CUTTER_SRCS
    cutter/cut_text.cpp
    )

add_library(cutter
    ${CUTTER_HDRS}
    ${CUTTER_SRCS}
    )

target_link_libraries(cutter Qt5::Core)
