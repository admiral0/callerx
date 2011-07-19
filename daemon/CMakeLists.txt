include_directories(
	${QT_INCLUDES}
	${CMAKE_SOURCE_DIR}/daemon
	${CMAKE_BINARY_DIR}/daemon
)

set(callerxdaemon_SRCS daemon.cpp dbustypes.cpp main.cpp)

set_property(SOURCE com.nokia.csd.Call.xml PROPERTY NO_NAMESPACE TRUE)
set_property(SOURCE com.nokia.csd.Call.xml PROPERTY INCLUDE "dbustypes.h")
QT4_ADD_DBUS_INTERFACE(callerxdaemon_SRCS com.nokia.csd.Call.xml csd)

set_property(SOURCE com.nokia.csd.Call.Instance.xml PROPERTY NO_NAMESPACE TRUE)
set_property(SOURCE com.nokia.csd.Call.Instance.xml PROPERTY INCLUDE "dbustypes.h")
QT4_ADD_DBUS_INTERFACE(callerxdaemon_SRCS com.nokia.csd.Call.Instance.xml csdi)

QT4_ADD_DBUS_ADAPTOR(callerxdaemon_SRCS org.callerx.xml daemon.h CallerXDaemon)

QT4_AUTOMOC(${callerxdaemon_SRCS})

add_executable(callerxd ${callerxdaemon_SRCS})
target_link_libraries(callerxd ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY})

install(TARGETS callerxd DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(FILES data/callerx.conf DESTINATION /etc/dbus-1/system.d)
install(FILES data/callerx DESTINATION /etc/init.d)
