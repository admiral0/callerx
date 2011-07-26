/*
    CallerX management from console
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


#ifndef CALLERXCONSOLE_H
#define CALLERXCONSOLE_H

#include <QtCore/QObject>

#include <QtCore/QStringList>
#include "callerx.h"

class ConfigInteraction;

class CallerXConsole : public QObject
{
public:
    explicit CallerXConsole(QObject* parent = 0);
    virtual ~CallerXConsole();
private:
    void displayHelp();
    void displayStatus();
    void reload();
    void displayLists();
    void addList(QString name);
    void delList(QString arg1);
    void viewParam(QString arg1);
    void modParam(QString arg1, QString arg2); //TODO: verify type. add input for days
    void viewListParam(QString arg1, QString arg2);
    void modListParam(QString arg1, QString arg2, QString arg3);
    void addNum(QString arg1, QString arg2);
    void delNum(QString arg1, QString arg2);
    void showList(QString arg1);
    QStringList args;
    QString command;
    CallerX *callerx;
    ConfigInteraction *config;
};

#endif // CALLERXCONSOLE_H
