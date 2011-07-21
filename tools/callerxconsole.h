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


class CallerXConsole : public QObject
{
public:
    explicit CallerXConsole(QObject* parent = 0);
    virtual ~CallerXConsole();
private:
    void displayHelp();
    QStringList args;
};

#endif // CALLERXCONSOLE_H
