#include "daemon.h"
#include "dbustypes.h"
#include <QDBusMetaType>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Registering Dbus metatypes
    qDBusRegisterMetaType<CallInfo>();
    qDBusRegisterMetaType<CallInfoList>();
    qDBusRegisterMetaType<CallInstance>();
    qDBusRegisterMetaType<CallInstanceList>();
    qDBusRegisterMetaType<CallTimers>();

    CallerXDaemon* daemon = new CallerXDaemon();
    QObject::connect(daemon, SIGNAL(quit()), &a, SLOT(quit()));
    daemon->Start();
    return a.exec();
}
