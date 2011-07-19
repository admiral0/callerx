#include "dbustypes.h"

QDBusArgument &operator<<(QDBusArgument &argument, const CallInfo &info){
    argument.beginStructure();
    argument << info.path << info.n << info.b1 << info.b2 << info.b3 << info.b4 << info.b5 << info.s;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, CallInfo &info){
    argument.beginStructure();
    argument >> info.path >> info.n >> info.b1 >> info.b2 >> info.b3 >> info.b4 >> info.b5 >> info.s;
    argument.endStructure();
    return argument;
}

QDBusArgument &operator <<(QDBusArgument &argument, const CallInstance &instance){
    argument.beginStructure();
    argument << instance.path << instance.n;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, CallInstance &instance){
    argument.beginStructure();
    argument >> instance.path >> instance.n;
    argument.endStructure();
    return argument;
}

QDBusArgument &operator <<(QDBusArgument &argument, const CallTimers &timers){
    argument.beginStructure();
    argument << timers.t1 << timers.t2 << timers.t3 << timers.t4;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator >>(const QDBusArgument &argument, CallTimers &timers){
    argument.beginStructure();
    argument >> timers.t1 >> timers.t2 >> timers.t3 >> timers.t4;
    argument.endStructure();
    return argument;
}
