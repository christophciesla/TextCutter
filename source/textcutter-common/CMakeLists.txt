INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(CUTTER_HDRS
    common/text_cutter.h
    )

set(CUTTER_SRCS
    common/text_cutter.cpp
    )

add_library(
    textcutter-common
    ${CUTTER_HDRS}
    ${CUTTER_SRCS}
    )

target_link_libraries(textcutter-common Qt5::Core)
