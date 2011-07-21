#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QFile>
#include <QFileSystemWatcher>
#include <QSettings>
#include <QList>
#include <QString>
#include <QTextStream>

#include "csd.h"
#include "csdi.h"

#define BUS_NAME "com.nokia.csd.Call"
#define BUS_PATH "/com/nokia/csd/call"
#define INSTANCE_INTERFACE "com.nokia.csd.Call.Instance"

#define CONFIG_PATH "/home/user/.callerxrc"
#define DEFAULT_BLACKLIST "/home/user/MyDocs/blacklist.txt"


class CallerxAdaptor;
class CallerXDaemon : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.callerx")

public:

    explicit CallerXDaemon(QObject *parent = 0);
    ~CallerXDaemon();
    bool isBlocked(QString number);
    void Start();


signals:
    void quit();

public slots:
    void Reload();
    void Stop();

private slots:
    void callScreen(const QDBusObjectPath& call, const QString& number);

private:
    void loadBlocklists(QStringList lists);
    QString phonePrefix;
    QFileSystemWatcher* configWatcher;
    QHash<QString,QStringList*> *lists;
    QHash<QString,QVariantHash*> *listsSettings; //Contains list settings "external","isEnabled","timeStart","timeEnd","days", "isWhitelist"
    QSettings *globalSettings;
    ComNokiaCsdCallInterface *csd;
    CallerxAdaptor *adaptor;
};
#endif // MAINWINDOW_H
