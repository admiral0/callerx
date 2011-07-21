#include <QDBusMetaType>
#include <QCoreApplication>
#include "dbustypes.h"
#include "callerxconsole.h"
#include <QtCore/qcoreapplication.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Registering Dbus metatypes
    qDBusRegisterMetaType<CallInfo>();
    qDBusRegisterMetaType<CallInfoList>();
    qDBusRegisterMetaType<CallInstance>();
    qDBusRegisterMetaType<CallInstanceList>();
    qDBusRegisterMetaType<CallTimers>();
    CallerXConsole c;
}