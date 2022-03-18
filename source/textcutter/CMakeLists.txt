INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTTER_DIR}
    )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/translations.qrc"
        "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc" COPYONLY)

qt5_create_translation(QM_FILES
    main.cpp
    ${GUI_SRCS}
    ${CMAKE_SOURCE_DIR}/translations/textcutter_en.ts
    ${CMAKE_SOURCE_DIR}/translations/textcutter_de.ts
    OPTIONS "-I ${CMAKE_CURRENT_SOURCE_DIR}"
    )

add_executable(textcutter
    main.cpp
    ${QM_FILES}
    "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc"
)

target_link_libraries(textcutter cutter Qt5::Core)

if(WIN32)
    add_custom_command(TARGET textcutter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:textcutter>
        )
endif (WIN32)
