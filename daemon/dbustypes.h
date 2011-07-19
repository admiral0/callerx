#ifndef DBUSTYPES_H
#define DBUSTYPES_H

#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusArgument>

struct CallInfo {
    QDBusObjectPath path;
    uint n;
    bool b1;
    bool b2;
    bool b3;
    bool b4;
    bool b5;
    QString s;
};
Q_DECLARE_METATYPE(CallInfo)
typedef QList<CallInfo> CallInfoList;
Q_DECLARE_METATYPE(CallInfoList)

struct CallInstance {
    QDBusObjectPath path;
    uint n;
};
Q_DECLARE_METATYPE(CallInstance)
typedef QList<CallInstance> CallInstanceList;
Q_DECLARE_METATYPE(CallInstanceList)

struct CallTimers {
    uint t1;
    uint t2;
    uint t3;
    uint t4;
};
Q_DECLARE_METATYPE(CallTimers)

#include "dbustypes.h"

QDBusArgument &operator<<(QDBusArgument &argument, const CallInfo &info);
const QDBusArgument &operator>>(const QDBusArgument &argument, CallInfo &info);

QDBusArgument &operator <<(QDBusArgument &argument, const CallInstance &instance);
const QDBusArgument &operator >>(const QDBusArgument &argument, CallInstance &instance);

QDBusArgument &operator <<(QDBusArgument &argument, const CallTimers &timers);
const QDBusArgument &operator >>(const QDBusArgument &argument, CallTimers &timers);



#endif // DBUSTYPES_H
