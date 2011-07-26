/*
    Public API
    Copyright (C) 2011  Radu Andries <admiral0@tuxfamily.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "callerx.h"
#include "daemoninteraction.h"
#include "configinteraction.h"

CallerX::CallerX()
{
    daemon=new DaemonInteraction();
    config=new ConfigInteraction();
}
CallerX::~CallerX()
{
    delete daemon;
    delete config;
}
void CallerX::addList(QString name)
{
    config->addList(name);
}
QVariant CallerX::addNumber(QString list, QString number)
{
    config->addNumber(list,number);
}
QStringList CallerX::blockLists()
{
    config->lists();
}
void CallerX::delList(QString name)
{
    config->delList(name);
}
QVariant CallerX::globalParam(int setting, QVariant *value)
{
    QVariant ret;
    QString ssetting;
    switch(setting){
        case PHONE_PREFIX:
            ssetting="phonePrefix";
            break;
        default:
            return ret;
    }
    if(value==0){
        //Get
        ret=config->getGlobal(ssetting);
    }else{
        //Set
        config->setGlobal(ssetting,*value);
    }
    return ret;
}
bool CallerX::isAlive()
{
    return daemon->isAlive();
}
QStringList CallerX::list(QString name)
{
    return config->listNumbers(name);
}
QVariant CallerX::listParam(QString list,int setting, QVariant* value)
{
    QVariant ret;
    QString ssetting;
    switch(setting){
        case ENABLED:
            ssetting="enabled";
            break;
        case EXTERNAL:
            ssetting="enabled";
            break;
        case ISWHITELIST:
            ssetting="isWhitelist";
            break;
        case TIME_START:
            ssetting="timeStart";
            break;
        case TIME_END:
            ssetting="timeEnd";
            break;
        case DAYS:
            ssetting="days";
            break;
        case LIST:
            ssetting="list";
            break;
        case BLOCK_UNKNOWN:
            ssetting="blockUnknown";
            break;
        default:
            return ret;
    }
    if(value==0){
        //Get
        ret=config->getParam(list,ssetting);
    }else{
        //Set
        config->setParam(list,ssetting,*value);
    }
    return ret;
}
void CallerX::reload()
{
    daemon->ReloadAll();
}
QVariant CallerX::delNumber(QString list, QString number)
{
    config->delNumber(list,number);
}




