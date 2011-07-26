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
#include <cstdlib>
#include <iostream>
#include <QtCore/qcoreapplication.h>
#include "configinteraction.h"

using namespace std;
CallerXConsole::CallerXConsole(QObject* parent): QObject(parent)
{
 callerx=new CallerX();
 config=new ConfigInteraction();
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
 }else if(command=="lists"){
    displayLists();
 }else if(command=="addList"){
    if(args.size()<3){
        cout<<"Error: Needs argument\n";
        displayHelp();
    }
    addList(args.at(2));
 }else if(command=="delList"){
    if(args.size()<3){
        cout<<"Error: Needs argument\n";
        displayHelp();
    }
    delList(args.at(2));
 }else if(command=="show"){
    if(args.size()<3){
        cout<<"Error: Needs argument\n";
        displayHelp();
    }
    showList(args.at(2));
 }else if(command=="global"){
    if(args.size()<3){
        cout<<"Error: Needs argument\n";
        displayHelp();
    }
    if(args.size()==4)
        modParam(args.at(2),args.at(3));
    else
        viewParam(args.at(2));
 }else if(command=="param"){
    if(args.size()<4){
        cout<<"Error: Needs 2 arguments\n";
        displayHelp();
    }
    if(args.size()==5)
        modListParam(args.at(2),args.at(3),args.at(4));
    else
        viewListParam(args.at(2),args.at(3));
 }else if(command=="add"){
    if(args.size()<4){
        cout<<"Error: Needs argument\n";
        displayHelp();
    }
    int s=args.size();
    for(int i=3;i<s;i++){
        addNum(args.at(2),args.at(i));
    }
 }else if(command=="del"){
    if(args.size()<4){
        cout<<"Error: Needs argument\n";
        displayHelp();
    }
    int s=args.size();
    for(int i=3;i<s;i++){
        delNum(args.at(2),args.at(i));
    }
 }
}
CallerXConsole::~CallerXConsole()
{
    //Who cares, i die anyway
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
        }else if(subcmd=="show"){
            cout<< "Usage: show listname\n";
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
        }else if(subcmd=="global"){
            cout<< "Usage: global parameter_name [newvalue]\n\n";
            cout<< " Params:\n";
            cout<< "  phonePrefix yes|no\n";
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
        cout<< "  " << "show    " << " " << "Displays list" << "\n"; 
        cout<< "  " << "addlist " << " " << "Adds a new blacklist" << "\n";
        cout<< "  " << "dellist " << " " << "Deletes blacklist" << "\n";
        cout<< "  " << "param   " << " " << "Displays/Modifies list settings" << "\n";
        cout<< "  " << "global  " << " " << "Displays/Modifies global settings" << "\n";
        cout<< "  " << "add     " << " " << "Adds a new number to specified blacklist" << "\n"; 
        cout<< "  " << "del     " << " " << "Deletes number from specified blacklist" << "\n"; 
        cout<<"\n";
        cout<< " Use \"" << args.at(0).toStdString() << " help command\" to get more help.\n\n";
    }
    exit(0); //This is cruel i know
}

void CallerXConsole::displayStatus()
{
    if(callerx->isAlive()){
        cout<<"Daemon: Running";
    }else{
        cout<<"Daemon: Stopped";
    }
    cout<<"\n";
}

void CallerXConsole::reload()
{
    callerx->reload();
}
void CallerXConsole::displayLists()
{
    QStringList l;
    l=callerx->blockLists();
    foreach(QString list,l){
        cout<<list.toStdString()<<"\n";
    }
}
void CallerXConsole::addList(QString name)
{
    callerx->addList(name);
}
void CallerXConsole::delList(QString arg1)
{
    callerx->delList(arg1);
}
void CallerXConsole::viewParam(QString arg1)
{
    cout << arg1.toStdString() << " : " << config->getGlobal(arg1).toString().toStdString() << "\n";
}
void CallerXConsole::modParam(QString arg1, QString arg2)
{
    config->setGlobal(arg1,arg2);
}
void CallerXConsole::viewListParam(QString arg1, QString arg2)
{
    cout << arg1.toStdString() << "." << arg2.toStdString() << " : " << config->getParam(arg1,arg2).toString().toStdString()<<"\n";
}
void CallerXConsole::modListParam(QString arg1, QString arg2, QString arg3)
{
    config->setParam(arg1,arg2,arg3);
}
void CallerXConsole::addNum(QString arg1, QString arg2)
{
    callerx->addNumber(arg1,arg2);
}

void CallerXConsole::delNum(QString arg1, QString arg2)
{
    callerx->delNumber(arg1,arg2);
}
void CallerXConsole::showList(QString arg1)
{
    QStringList l= callerx->list(arg1);
    foreach(QString ln,l){
        cout <<  ln.toStdString() << "\n";
    }
}

