 /*
    Interaction with daemon via DBUS
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


#include "daemoninteraction.h"

DaemonInteraction::DaemonInteraction()
{
    callerxd=new OrgCallerxInterface("org.callerx","/org/callerx",QDBusConnection::systemBus(),this);
}
DaemonInteraction::~DaemonInteraction()
{
    delete callerxd;
}
bool DaemonInteraction::isAlive()
{
    //I am lazy
    if( QString("pong") == callerxd->Ping())
        return true;
    return false;
}
void DaemonInteraction::ReloadAll()
{
    if(isAlive())
        callerxd->Reload();
}
