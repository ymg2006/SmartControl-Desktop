find_package(Qt6 6.5 REQUIRED COMPONENTS Core Test Qml QmlIntegration)

function(add_gaia_test target source)
    qt_add_executable(${target}
        ${source}
    )
    target_link_libraries(${target} PRIVATE
        Qt6::Core
        Qt6::Test
        Qt6::Qml
        Qt6::QmlIntegration
        gaiaV3
    )
    target_include_directories(${target} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
    )
    add_test(NAME ${target} COMMAND ${target})
endfunction()

add_gaia_test(test_GAIAPropertyBase test_GAIAPropertyBase.cpp)
add_gaia_test(test_GAIARfcommClient test_GAIARfcommClient.cpp)
add_gaia_test(test_BluetoothSocketWrapper test_BluetoothSocketWrapper.cpp)
