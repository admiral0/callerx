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


#include "callerxconsole.h"
#include <iostream>
#include <QtCore/qcoreapplication.h>

using namespace std;
CallerXConsole::CallerXConsole(QObject* parent): QObject(parent)
{
 args=QCoreApplication::instance()->arguments();
 displayHelp();
}
CallerXConsole::~CallerXConsole()
{

}
void CallerXConsole::displayHelp()
{
    cout<< " Usage: "<< args.at(0).toStdString() << " command " << "[command options]" << "\n\n" ;
    cout<< " " << "Commands:" << "\n";
    cout<< "  " << "help    " << " " << "Displays this help message." << "\n"; 
    cout<< "  " << "status  " << " " << "Displays status of daemon" << "\n";
    cout<< "  " << "reload  " << " " << "Forces daemon to reload settings" << "\n";
    cout<< "  " << "lists   " << " " << "Displays all lists" << "\n"; 
    cout<< "  " << "addlist " << " " << "Adds a new blacklist" << "\n";
    cout<< "  " << "dellist " << " " << "Deletes blacklist" << "\n";
    cout<< "  " << "param   " << " " << "Displays/Modifies list settings" << "\n";
    cout<< "  " << "add     " << " " << "Adds a new number to specified blacklist" << "\n"; 
    cout<< "  " << "del     " << " " << "Deletes number from specified blacklist" << "\n"; 
    cout<<"\n";
}

