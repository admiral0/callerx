include_directories(
        ${QT_INCLUDES}
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/daemon
        ${CMAKE_BINARY_DIR}/lib
)

set(callerxlib_SRCS callerx.cpp configinteraction.cpp daemoninteraction.cpp ${CMAKE_SOURCE_DIR}/daemon/dbustypes.cpp)

set_property(SOURCE ${CMAKE_SOURCE_DIR}/daemon/org.callerx.xml PROPERTY NO_NAMESPACE TRUE)
set_property(SOURCE ${CMAKE_SOURCE_DIR}/daemon/org.callerx.xml PROPERTY INCLUDE "dbustypes.h")
QT4_ADD_DBUS_INTERFACE(callerxlib_SRCS ${CMAKE_SOURCE_DIR}/daemon/org.callerx.xml callerxinterface)


QT4_AUTOMOC(${callerxlib_SRCS})

add_library(callerx SHARED ${callerxlib_SRCS})
set_property(TARGET callerx PROPERTY VERSION 0.80)
set_property(TARGET callerx PROPERTY SOVERSION 1)
target_link_libraries(callerx ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY})

install(TARGETS callerx DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES callerx.h DESTINATION /usr/include)
