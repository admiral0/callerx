project(callerx)

cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Qt4 COMPONENTS QtCore QtDbus REQUIRED QtGui OPTIONAL)

add_definitions (
    ${QT_DEFINITIONS}
)

add_subdirectory(daemon)
add_subdirectory(tools)