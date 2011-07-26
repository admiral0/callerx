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


#ifndef CALLERX_H
#define CALLERX_H
#include <QtCore/QStringList>
#include <QtCore/QVariant>

class ConfigInteraction;
class DaemonInteraction;

/**
 * @brief Public API to CallerX
 * Use this class to communicate with daemon and set configuration
 * @note If any functionality is missing please open an issue and/or provide patches.
 */
class CallerX
{
    ///List settings
    enum {
        ENABLED, /** List is enabled, bool */
        EXTERNAL, /** Path of external list, empty|NULL otherwise , QString */
        ISWHITELIST, /** Whitelist mode for the list, bool */
        TIME_START,/** Time when list starts being active, QTime */
        TIME_END, /** Time when list starts being inactive, QTime */
        DAYS, /** List of days when list is active, QList of int */
        LIST, /** Numbers blocked/whitelisted, QStringList */
        BLOCK_UNKNOWN /** Block unknown numbers?, bool */
    };
    ///Global Wide settings
    enum {
        PHONE_PREFIX, /** Prefix of phones to ignore. */
    };
    CallerX(); /** Main constructor. Opens up configuration and sets up connection to daemon */
    ~CallerX(); /** Cleanup */
    /**
     * Asks daemon via dbus to reload configuration
     */
    void reload();
    /**
     * Is daemon alive?
     */
    bool isAlive();
    /**
     * All lists in the configuration
     */
    QStringList blockLists();
    /**
     * Adds a list
     * @note call <method>reload</method> to load new blacklist
     */
    void addList(QString name);
    /**
     * Deletes a list in configuration
     * @note call <method>reload</method> to unload list.
     */
    void delList(QString name);
    /**
     * Gets/sets global setting.
     * @param setting Look at global setting enum
     */
    QVariant globalParam(int setting, QVariant *value=0);
    /**
     * Gets/sets list setting
     */
    QVariant listParam(QString list, int setting, QVariant* value = 0);
    /**
     * Adds number to blacklist
     */
    QVariant addNumber(QString list,QString number);
    /**
     * Deletes number to blacklist
     */
    QVariant delNumber(QString list,QString number);
    /**
     * Lists all numbers in a blocklist
     */
    QStringList list(QString name);
private:
    DaemonInteraction *daemon;
    ConfigInteraction *config;
};

#endif // CALLERX_H
