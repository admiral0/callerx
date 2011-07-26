include_directories(
        ${QT_INCLUDES}
        ${CMAKE_SOURCE_DIR}/tools
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_BINARY_DIR}/tools
)

set(callerxtools_SRCS main.cpp callerxconsole.cpp )


QT4_AUTOMOC(${callerxtools_SRCS})

add_executable(callerxc ${callerxtools_SRCS})
target_link_libraries(callerxc ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} callerx)

install(TARGETS callerxc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
