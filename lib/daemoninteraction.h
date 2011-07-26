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


#ifndef DAEMONINTERACTION_H
#define DAEMONINTERACTION_H

#include <QtCore/QObject>
#include "callerxinterface.h"

/**
 * Class that interacts directly with daemon via dbus.
 * @note Note that not all calls are mapped. Only ones required for API
 */
class DaemonInteraction : public QObject
{

public:
    explicit DaemonInteraction();
    virtual ~DaemonInteraction();
    /**
     * Pings server
     */
    bool isAlive();
    /**
     * Forces server to reload all lists and configuration
     */
    void ReloadAll();
private:
    OrgCallerxInterface *callerxd;
};

#endif // DAEMONINTERACTION_H
