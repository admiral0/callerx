#include "daemon.h"
#include "csd.h"
#include "callerxadaptor.h"

CallerXDaemon::CallerXDaemon(QObject *parent) :
    QObject(parent)
{
    globalSettings=new QSettings(CONFIG_PATH,QSettings::IniFormat);
    phonePrefix=globalSettings->value("phonePrefix",QString()).toString();
    Reload();
    //Start global call listener
    csd=new ComNokiaCsdCallInterface(BUS_NAME,BUS_PATH,QDBusConnection::systemBus());
    //Initialize dbus adaptor
    new CallerxAdaptor(this);
}
CallerXDaemon::~CallerXDaemon()
{
    delete configWatcher;
    delete globalSettings;
}

void CallerXDaemon::Start()
{
    //New Call hook
    connect(csd,SIGNAL(Coming(QDBusObjectPath,QString)),this,SLOT(callScreen(QDBusObjectPath,QString)));
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

    configWatcher = new QFileSystemWatcher();
    configWatcher->addPath(CONFIG_PATH);
    connect(configWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(loadlist()));
    
}

void CallerXDaemon::callScreen(const QDBusObjectPath &call,const QString &number)
{
    if(isBlocked(number)){
        ComNokiaCsdCallInstanceInterface call(BUS_NAME,call.path(),QDBusConnection::systemBus());
        call.Release();
    }
}

void CallerXDaemon::Stop()
{
    emit quit();
    return;
}

void CallerXDaemon::Reload()
{
    globalSettings->beginGroup("General");
    QStringList lists= globalSettings->value("blocklists", QStringList()).toStringList();
    globalSettings->endGroup();
    //Hit me plenty...
    loadBlocklists(lists);
}

void CallerXDaemon::loadBlocklists(QStringList sLists)
{
    foreach(QString listname,sLists){
        qDebug()<<"Processing "<<listname;
        globalSettings->beginGroup(listname);
        QStringList *l=new QStringList();
        QVariantHash *settings=new QVariantHash();
        settings->insert("enabled",globalSettings->value("enabled",true));
        settings->insert("external",globalSettings->value("external",QString()));
        settings->insert("isWhitelist",globalSettings->value("isWhitelist",false));
        settings->insert("timeStart",globalSettings->value("timeStart",QTime(0,0))); //ye' olde tricke
        settings->insert("timeEnd",globalSettings->value("timeEnd",QTime(0,0))); 
        settings->insert("days",globalSettings->value("dayStart",QVariantList()));
        settings->insert("blockUnknown",globalSettings->value("blockUnknown",false));
        if(settings->value("external").toString().isEmpty()){
            QStringList storage=globalSettings->value("list",QStringList()).toStringList();
            //Moving from stack to heap like a boss
            foreach(QString blocked,storage){
                l->append(blocked);
            }
        }else{
            QString lstpath=settings->value("external").toString();
            QFile blocklist(lstpath);
            if (blocklist.exists()) {
                if (!blocklist.open(QIODevice::ReadOnly | QIODevice::Text)){                
                    QTextStream in(&blocklist);
                    QString line = in.readLine();
                    while (!line.isNull()) {
                        l->append(line);
                        line = in.readLine();
                    }
                    //This could be
                    //l=blocklist.readAll().split("\n");
                    //but looses compatibility with winnoob editors
                    blocklist.close();
                }
            }
        }
        lists->insert(listname,l);
        
        globalSettings->endGroup();
    }
}
bool CallerXDaemon::isBlocked(QString number)
{
    QTime currentTime = QTime::currentTime();
    QTime maxTime(23,59,59);
    QDate currentDate = QDate::currentDate();
    bool whitelist,tempresult,inTime;
    QTime timeStart,timeEnd;
    QVariantList days;
    if(number.startsWith(phonePrefix)){
        number.remove(0,phonePrefix.size());
    }
    foreach(QString list,lists->keys()){
        QStringList *l=lists->value(list);
        QVariantHash *s=listsSettings->value(list);
        whitelist=s->value("isWhitelist").toBool();
        days=s->value("dayStart").toList();
        timeStart=s->value("timeStart").toTime();
        timeEnd=s->value("timeEnd").toTime();
        bool e=s->value("enabled").toBool();
        inTime=false;
        if(timeStart==timeEnd)
            inTime=true;
        //multidate, too drunk to do seriously
        if(timeStart<timeEnd){
            if(currentTime>timeStart || currentTime<timeEnd)
                inTime=true;
        }else{
            if(currentTime>timeStart && currentTime<timeEnd)
                inTime=true;
        }
        //Verify if list is active. This is a monster
        if(e && days.contains(currentDate.dayOfWeek()) && inTime){
            if(s->value("blockUnknown").toBool() && number.isEmpty())
                return true;
            else if(number.isEmpty())
                return false;
            if(whitelist){
                foreach(QString match,*l){
                    if(number.startsWith(match)){
                        tempresult=false;
                    }
                }
                if(!tempresult)
                    tempresult=true;
            }else{
                foreach(QString match,*l){
                    if(number.startsWith(match) && !tempresult){
                        tempresult=true;
                    }
                }
            }
        }
        if(tempresult)
            return true;
    }
    return false;   
}
QString CallerXDaemon::Ping()
{
    return QString("pong");
}


#include "daemon.moc"
