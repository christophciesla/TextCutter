INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTTER_DIR}
    )

set(GUI_HDRS
    gui/main_window.h
    )

set(GUI_SRCS
    gui/main_window.cpp
    )

add_executable(textcutter-gui WIN32
    ${GUI_HDRS}
    ${GUI_SRCS}
    main.cpp
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
