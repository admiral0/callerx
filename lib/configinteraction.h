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


#ifndef CONFIGINTERACTION_H
#define CONFIGINTERACTION_H

#include <QtCore/QObject>

class QSettings;

class ConfigInteraction : public QObject
{
    explicit ConfigInteraction();
    virtual ~ConfigInteraction();
public:
    QStringList lists();
    void addList(QString name);
    void delList(QString list);
    QVariant getParam(QString list,QString name);
    void setParam(QString list,QString name, QVariant value);
    void addNumber(QString list,QString number);
    void delNumber(QString list,QString number);
    QStringList listNumbers(QString list);
    QVariant getGlobal(QString name);
    void setGlobal(QString name, QVariant value);
    
private:
    QSettings *settings;
};

#endif // CONFIGINTERACTION_H
