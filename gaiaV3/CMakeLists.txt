find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(GAIAPropertyClasses_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GAIAPropertyClasses.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GAIAPropertyClasses.cpp
)

set(GAIAPropertyManager_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GAIAPropertyManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GAIAPropertyManager.cpp
)

add_custom_command(
    OUTPUT ${GAIAPropertyClasses_SRC}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/property_creator.py
        -i ${CMAKE_CURRENT_SOURCE_DIR}/m4.json
        -o ${CMAKE_CURRENT_SOURCE_DIR}/GAIAPropertyClasses
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/m4.json ${CMAKE_CURRENT_SOURCE_DIR}/scripts/property_creator.py
    VERBATIM
)

add_custom_command(
    OUTPUT ${GAIAPropertyManager_SRC}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/property_manager_creator.py
        -i ${CMAKE_CURRENT_SOURCE_DIR}/m4.json
        -o ${CMAKE_CURRENT_SOURCE_DIR}/GAIAPropertyManager
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/m4.json ${CMAKE_CURRENT_SOURCE_DIR}/scripts/property_manager_creator.py
    VERBATIM
)

qt_add_library(gaiaV3 SHARED
    GAIAPropertyBase.cpp
    GAIAPropertyBase.h
    gaiaV3_export.h
    ${GAIAPropertyClasses_SRC}
    ${GAIAPropertyManager_SRC}
    GAIARfcommClient.cpp
    GAIARfcommClient.h
    GAIAPropertyManagerBase.cpp
    GAIAPropertyManagerBase.h
    BluetoothSocketWrapper.cpp
    BluetoothSocketWrapper.h
)

qt_add_qml_module(gaiaV3
    URI gaiaV3
    VERSION 1.0
    SOURCES
        ${GAIAPropertyClasses_SRC}
        ${GAIAPropertyManager_SRC}
        GAIARfcommClient.cpp
        GAIARfcommClient.h
)

set_target_properties(gaiaV3 PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_include_directories(gaiaV3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(gaiaV3 PRIVATE GAIA_V3_LIBRARY WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_libraries(gaiaV3
    PUBLIC
        Qt6::Core
        Qt6::Qml
        Qt6::QmlIntegration
    PRIVATE
        Qt6::Quick
        Ws2_32
        Bthprops
)

if (SENNHEISER_BUILD_TESTS AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
