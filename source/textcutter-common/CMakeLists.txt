INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/translations_common.qrc"
        "${CMAKE_CURRENT_BINARY_DIR}/translations_common.qrc" COPYONLY)

set(CUTTER_HDRS
    common/text_cutter.h
    )

set(CUTTER_SRCS
    common/text_cutter.cpp
    )

qt5_create_translation(QM_FILES
    ${CUTTER_SRCS}
    ${CMAKE_SOURCE_DIR}/translations/textcutter-common_en.ts
    ${CMAKE_SOURCE_DIR}/translations/textcutter-common_de.ts
    OPTIONS "-I ${CMAKE_CURRENT_SOURCE_DIR}"
    )

add_library(
    textcutter-common
    ${CUTTER_HDRS}
    ${CUTTER_SRCS}
    ${QM_FILES}
    "${CMAKE_CURRENT_BINARY_DIR}/translations_common.qrc"
    )

target_link_libraries(textcutter-common Qt5::Core)
