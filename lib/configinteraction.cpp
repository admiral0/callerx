/*
    Interaction with config
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


#include "configinteraction.h"
#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QDebug>

ConfigInteraction::ConfigInteraction()
{
    settings=new QSettings("/home/user/.callerxrc",QSettings::IniFormat); //TODO move to CMake config
}
ConfigInteraction::~ConfigInteraction()
{
    delete settings;
}
QStringList ConfigInteraction::lists()
{
    settings->beginGroup("General");
    QStringList lists= settings->value("blocklists", QStringList()).toStringList();
    settings->endGroup();
    return lists;
}
void ConfigInteraction::addList(QString name)
{
    settings->beginGroup("General");
    QStringList lists= settings->value("blocklists", QStringList()).toStringList();
    lists.append(name);
    settings->setValue("blocklists",lists);
    settings->endGroup();
}
void ConfigInteraction::delList(QString list)
{
    settings->beginGroup("General");
    QStringList lists= settings->value("blocklists", QStringList()).toStringList();
    
    if(lists.contains(list)){
        lists.removeAll(list);
        settings->remove(list);
        settings->setValue("blocklists",lists);
    }
    settings->endGroup();

}
QVariant ConfigInteraction::getParam(QString list, QString name)
{
    QVariant val;
    if(settings->childGroups().contains(list)){
        settings->beginGroup(list);
        val=settings->value(name,QVariant());
        settings->endGroup();;
    };
    return val;
}
void ConfigInteraction::setParam(QString list, QString name, QVariant value)
{
    settings->beginGroup(list);
    settings->setValue(name,value);
    settings->endGroup();
}

void ConfigInteraction::addNumber(QString list, QString number)
{
    if(settings->childGroups().contains(list)){
        settings->beginGroup(list);
        QString external;
        external=settings->value("external",QString()).toString();
        if(external.isEmpty()){
            QFile eList(external);
            if(!eList.exists())
                qDebug()<<"Warning: File "<<external<<" does not exist. Creating.";
            if(!eList.open(QIODevice::Append)){
                qDebug()<<"Cannot open. Giving up.";
                return;
            }
            number.append("\n");
            eList.write(number.toAscii());
            eList.close();
        }else{
            QStringList tmpList;
            tmpList=settings->value("list",QStringList()).toStringList();
            if(!tmpList.contains(number)){
                tmpList.append(number);
                settings->setValue("list",tmpList);
            }
        }
        settings->endGroup();;
    };
}
void ConfigInteraction::delNumber(QString list, QString number)
{
    if(settings->childGroups().contains(list)){
        settings->beginGroup(list);
        QString external;
        if(!external.isEmpty()){
            QFile eList(external);
            if(!eList.exists()){
                qDebug()<<"Warning: File "<<external<<" does not exist. Giving up.";
                settings->endGroup();
                return;
            }
            if(!eList.open(QIODevice::ReadWrite)){
                qDebug()<<"Cannot open. Giving up.";
                settings->endGroup();
                return;
            }
            QTextStream in(&eList);
            QString line = in.readLine();
            QStringList l;
            while (!line.isNull() ) {
                l.append(line);
                line = in.readLine();
            }
            if(l.contains(number)){
                l.removeAll(number);
                eList.close();
                eList.open(QIODevice::WriteOnly);
                foreach(QString n,l){
                    n.append("\n");
                    eList.write(n.toAscii());
                }
            }
            eList.close();
        }else{
            QStringList tmpList;
            tmpList=settings->value("list",QStringList()).toStringList();
            if(!tmpList.contains(number)){
                tmpList.append(number);
                settings->setValue("list",tmpList);
            }
        }
        settings->endGroup();
    }
}
QVariant ConfigInteraction::getGlobal(QString name)
{
    QVariant val;
    val=settings->value(name,QVariant());
    return val;
}
void ConfigInteraction::setGlobal(QString name, QVariant value)
{
    settings->setValue(name,value);
}
QStringList ConfigInteraction::listNumbers(QString list)
{
    QStringList l;
    if(settings->childGroups().contains(list)){
        settings->beginGroup(list);
        QString external;
        if(!external.isEmpty()){
            QFile eList(external);
            if(!eList.exists()){
                qDebug()<<"Warning: File "<<external<<" does not exist. Giving up.";
                settings->endGroup();
                return l;
            }
            if(!eList.open(QIODevice::ReadOnly)){
                qDebug()<<"Cannot open. Giving up.";
                settings->endGroup();
                return l;
            }
            QTextStream in(&eList);
            QString line = in.readLine();
            while (line.isNull() ) {
                l.append(line);
                line = in.readLine();
            }
            eList.close();
        }else{
            QStringList tmpList;
            l=settings->value("list",QStringList()).toStringList();
        }
        settings->endGroup();
    }
    return l;
}

