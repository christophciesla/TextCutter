INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTTER_DIR}
    )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/translations.qrc"
        "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc" COPYONLY)

set(GUI_HDRS
    gui/main_window.h
    )

set(GUI_SRCS
    gui/main_window.cpp
    )

qt5_create_translation(QM_FILES
    main.cpp
    ${GUI_SRCS}
    ${CMAKE_SOURCE_DIR}/translations/textcutter-gui_en.ts
    ${CMAKE_SOURCE_DIR}/translations/textcutter-gui_de.ts
    OPTIONS "-I ${CMAKE_CURRENT_SOURCE_DIR}"
    )

add_executable(textcutter-gui WIN32
    ${GUI_HDRS}
    ${GUI_SRCS}
    main.cpp
    ${QM_FILES}
    "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc"
)

target_link_libraries(textcutter-gui textcutter-common Qt5::Widgets)

if(WIN32)
    target_link_libraries(textcutter-gui Qt5::WinMain)
    add_custom_command(TARGET textcutter-gui POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:textcutter-gui>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:textcutter-gui>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:textcutter-gui>
        )
endif (WIN32)
