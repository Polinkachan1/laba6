cmake_minimum_required(VERSION 4.0)
project(untitled9)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories(server/headers)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(client
        client/main.cpp
        client/application.cpp
        client/interface.cpp
        common/common.cpp
        common/communicator.cpp
)
target_link_libraries(client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
)
add_executable(server
        server/main.cpp
        server/application.cpp
        server/array.cpp
        server/polynom.cpp
        server/complex.cpp
        common/common.cpp
        common/communicator.cpp
)

target_link_libraries(server
        Qt::Core
        Qt::Network
)
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()

    # Для клиента
    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:client>/plugins/platforms/")
        add_custom_command(TARGET client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:client>/plugins/platforms/")
    endif()
    foreach(QT_LIB Core Gui Widgets Network)
        add_custom_command(TARGET client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:client>")
    endforeach(QT_LIB)

    # Для сервера
    foreach(QT_LIB Core Network)
        add_custom_command(TARGET server POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:server>")
    endforeach(QT_LIB)
endif()