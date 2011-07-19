#include "daemon.h"
#include "csd.h"
#include "callerxadaptor.h"

CallerXDaemon::CallerXDaemon(QObject *parent) :
    QObject(parent)
{
    settings=new QSettings(CONFIG_PATH,QSettings::IniFormat);
    settings->beginGroup("General");
    whitelistmode = settings->value("whitelistmode", false).toBool();
    settings->endGroup();
    settings->beginGroup("Paths");
    whitelistpath = settings->value("whitelistpath", DEFAULT_WHITELIST).toString();
    blacklistpath = settings->value("blacklistpath", DEFAULT_BLACKLIST).toString();
    settings->endGroup();
    if (whitelistmode) {
        listPath = whitelistpath;
    }
    else {
        listPath = blacklistpath;
    }
    csd=new ComNokiaCsdCallInterface(BUS_NAME,BUS_PATH,QDBusConnection::systemBus());
    new CallerxAdaptor(this);
}

CallerXDaemon::~CallerXDaemon()
{
    //Syncing settings before exit...
    settings->beginGroup("General");
    settings->setValue("whitelistmode", whitelistmode);
    settings->endGroup();
    settings->beginGroup("Paths");
    settings->setValue("whitelistpath", whitelistpath);
    settings->setValue("blacklistpath", blacklistpath);
    settings->endGroup();
    settings->sync();
    delete fileWatcher;
    delete settings;
}

void CallerXDaemon::Start()
{
    //New Call
    connect(csd,SIGNAL(Coming(QDBusObjectPath,QString)),this,SLOT(callScreen(QDBusObjectPath,QString)));
    //Why???!
    //connect(csd,SIGNAL(UserConnection(bool)),this,SLOT(callOn(bool))); 
    //connect(csdi,SIGNAL(Terminated()),this,SLOT(callOff()));
    QDBusConnection dbusif=QDBusConnection::systemBus();
    if (!dbusif.isConnected()) {
        emit quit();
        return;
    }
    if (!dbusif.registerService("org.callerx")) {
        emit quit();
        return;
    }
    if (!dbusif.registerObject("/org/callerx", this)) {
        emit quit();
        return;
    }

    QFile blocklist(listPath);
    if (!blocklist.exists()) {
        if (!blocklist.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }
        blocklist.close();
    }

    fileWatcher = new QFileSystemWatcher();
    fileWatcher->addPath(listPath);
    loadlist();
    connect(fileWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(loadlist()));
    
}

void CallerXDaemon::callScreen(const QDBusObjectPath &call,const QString &number)
{
    dbusPath=call.path();
    if (whitelistmode) {
    //Kick'em if not in the list
        bool match = false;
        for (int i = 0; i < nlist.size(); ++i){
            if (number.startsWith(nlist.at(i))){
                break;
            }
        }
        if(!match){
            callRelease();
        }
    }else{
        for (int i = 0; i < nlist.size(); ++i){
            if (number.startsWith(nlist.at(i))){
                callRelease();
                break;
            }
        }
    }

}

void CallerXDaemon::Stop()
{
    emit quit();
    return;
}

void CallerXDaemon::Reload()
{
    loadlist();
}

void CallerXDaemon::SetWhitelistMode ( bool enabled )
{
    whitelistmode=enabled;
    fileWatcher->removePath(listPath);
    if(enabled){
        listPath=whitelistpath;
    }else{
        listPath=blacklistpath;
    }
    fileWatcher->addPath(listPath);
    Reload();
}

void CallerXDaemon::callRelease()
{
     ComNokiaCsdCallInstanceInterface call(BUS_NAME,dbusPath,QDBusConnection::systemBus());
     call.Release();
}

void CallerXDaemon::loadlist()
{
    nlist.clear();
    QFile blocklist(listPath);
    if (blocklist.exists()) {
        if (!blocklist.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }
        QTextStream in(&blocklist);
        QString line = in.readLine();
        while (!line.isNull()) {
            if (!nlist.contains(line)) {
               nlist.append(line);
            }
            line = in.readLine();
        }
        //This could be
        //nlist=blocklist.readAll().split("\n");
        //but looses compatibility with winnoob editors
        blocklist.close();
    }
}

#include "daemon.moc"
