include_directories(
        ${QT_INCLUDES}
        ${CMAKE_SOURCE_DIR}/tools
        ${CMAKE_SOURCE_DIR}/daemon
        ${CMAKE_BINARY_DIR}/tools
)

set(callerxtools_SRCS ${CMAKE_SOURCE_DIR}/daemon/dbustypes.cpp main.cpp callerxconsole.cpp )

set_property(SOURCE ${CMAKE_SOURCE_DIR}/daemon/org.callerx.xml PROPERTY NO_NAMESPACE TRUE)
set_property(SOURCE ${CMAKE_SOURCE_DIR}/daemon/org.callerx.xml PROPERTY INCLUDE "dbustypes.h")
QT4_ADD_DBUS_INTERFACE(callerxtools_SRCS ${CMAKE_SOURCE_DIR}/daemon/org.callerx.xml callerx)


QT4_AUTOMOC(${callerxtools_SRCS})

add_executable(callerxc ${callerxtools_SRCS})
target_link_libraries(callerxc ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY})

install(TARGETS callerxc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
