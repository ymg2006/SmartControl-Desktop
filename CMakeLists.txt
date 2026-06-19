cmake_minimum_required(VERSION 3.21)

project(sennheiserDesktopClient
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Windows Sennheiser headphones configuration app"
)

if (NOT WIN32)
    message(FATAL_ERROR "This branch is Windows-only. Build it with MSVC and Qt 6 on Windows.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(SENNHEISER_BUILD_TESTS "Build unit tests" ON)
include(CTest)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Quick QuickControls2 Svg Test Qml QmlIntegration)
qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(gaiaV3)
add_subdirectory(btuicontrols)

qt_add_executable(sennheiserDesktopClient
    main.cpp
    AppController.cpp
    AppController.h
)

qt_add_resources(sennheiserDesktopClient "res"
    PREFIX "/"
    BASE "resources"
    FILES
        resources/appicon.png
)

qt_add_qml_module(sennheiserDesktopClient
    URI btui
    VERSION 1.0
    QML_FILES
        Main.qml
)

set_target_properties(sennheiserDesktopClient PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(sennheiserDesktopClient PRIVATE
    PROJECT_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
    PROJECT_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
    PROJECT_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
    PROJECT_DESCRIPTION="${CMAKE_PROJECT_DESCRIPTION}"
    PROJECT_URL="https://github.com/zaval/sennheiser-desktop-client"
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

target_link_libraries(sennheiserDesktopClient PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Svg
    gaiaV3
    btuicontrols
)

find_program(WINDEPLOYQT_EXECUTABLE
    NAMES windeployqt
    HINTS "${Qt6_DIR}/../../../bin"
)

add_custom_command(TARGET sennheiserDesktopClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Deploying local QML modules..."
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:sennheiserDesktopClient>/btuicontrols"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:sennheiserDesktopClient>/gaiaV3"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/btuicontrols/qmldir" "$<TARGET_FILE_DIR:sennheiserDesktopClient>/btuicontrols/qmldir"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:btuicontrolsplugin>" "$<TARGET_FILE_DIR:sennheiserDesktopClient>/btuicontrols/btuicontrolsplugin.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:btuicontrols>" "$<TARGET_FILE_DIR:sennheiserDesktopClient>/btuicontrols.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:btuicontrols>" "$<TARGET_FILE_DIR:sennheiserDesktopClient>/btuicontrols/btuicontrols.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:gaiaV3>" "$<TARGET_FILE_DIR:sennheiserDesktopClient>/$<TARGET_FILE_NAME:gaiaV3>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/gaiaV3/qmldir" "$<TARGET_FILE_DIR:sennheiserDesktopClient>/gaiaV3/qmldir"
)

if (WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET sennheiserDesktopClient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Running windeployqt..."
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            "$<$<CONFIG:Debug>:--debug>$<$<NOT:$<CONFIG:Debug>>:--release>"
            --qmldir "${CMAKE_SOURCE_DIR}"
            "$<TARGET_FILE:sennheiserDesktopClient>"
    )
endif()
