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
#include "callerx.h"
#include <cstdlib>
#include <iostream>
#include <QtCore/qcoreapplication.h>

using namespace std;
CallerXConsole::CallerXConsole(QObject* parent): QObject(parent)
{
 args=QCoreApplication::instance()->arguments();
 if(args.size()<2)
    displayHelp();
 command=args.at(1);
 if(command=="help"){
    displayHelp();
 }else if(command=="status"){
     displayStatus();
 }else if(command=="reload"){
    reload();
 }
}
CallerXConsole::~CallerXConsole()
{
    //NOP
}
void CallerXConsole::displayHelp()
{
    if(command=="help" && args.size()>2){
        QString subcmd=args.at(2);
        if(subcmd=="help"){
            if(args.size()>3 && args.at(3)=="help"){
                if(args.size()>4 && args.at(4)=="help"){
                    cout<<"gtfo\n";
                }else{
                    cout<< "YO DAWG.\n";
                }
            }else{
                cout<< "We need to go deeper.\n";
            }
        }else if(subcmd=="status"){
            cout<< "No options"<< "\n";
        }else if(subcmd=="reload"){
            cout<< "No options\n";
        }else if(subcmd=="lists"){
            cout<< "No options\n";
        }else if(subcmd=="addlist"){
            cout<< "Usage: addlist listname\n";
        }else if(subcmd=="dellist"){
            cout<< "Usage: dellist listname\n";
        }else if(subcmd=="param"){
            cout<< "Usage: param parameter_name [newvalue]\n\n";
            cout<< " Params:\n";
            cout<< "  isEnabled yes|no\n";
            cout<< "  isWhitelist yes|no\n";
            cout<< "  blockUnknown yes|no\n";
            cout<< "  external 0|path_to_list\n";
            cout<< "  timeStart hh:mm\n";
            cout<< "  timeEnd hh:mm\n";
            cout<< "  days 1,5,6 # (Monday,Friday and Saturday)\n";
            cout<< "\n";
        }else if(subcmd=="add"){
            cout<<"Usage: add listname number\n";
        }else if(subcmd=="del"){
            cout<<"Usage: del listname number\n";
        }
    }else{
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
        cout<< " Use \"" << args.at(0).toStdString() << " help command\" to get more help.\n\n";
    }
    exit(0); //This is cruel i know
}

void CallerXConsole::displayStatus()
{
    OrgCallerxInterface iface("org.callerx","/org/callerx",QDBusConnection::systemBus(),this);
    cout<< "Nothing interesting to show yet.\n";
}

void CallerXConsole::reload()
{
    OrgCallerxInterface iface("org.callerx","/org/callerx",QDBusConnection::systemBus(),this);
    iface.Reload();
    cout<< "Command sent.\n";
}
