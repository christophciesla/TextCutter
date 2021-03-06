INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTTER_DIR}
    )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/translations.qrc"
        "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc" COPYONLY)

qt5_create_translation(QM_FILES
    main.cpp
    ${CMAKE_SOURCE_DIR}/translations/textcutter_en.ts
    ${CMAKE_SOURCE_DIR}/translations/textcutter_de.ts
    OPTIONS "-I ${CMAKE_CURRENT_SOURCE_DIR}"
    )

add_executable(textcutter
    main.cpp
    ${QM_FILES}
    "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc"
)

target_link_libraries(textcutter textcutter-common Qt5::Core)

if(WIN32)
    add_custom_command(TARGET textcutter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:textcutter>
        )

    add_custom_command(TARGET textcutter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:textcutter>/translations)
    add_custom_command(TARGET textcutter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_translations_dir}/qtbase_en.qm $<TARGET_FILE_DIR:textcutter>/translations
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_translations_dir}/qtbase_de.qm $<TARGET_FILE_DIR:textcutter>/translations
        )
endif (WIN32)
