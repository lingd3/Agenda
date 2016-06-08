#include "AgendaUI.h"
#include "AgendaService.h"
#include <iostream>
#include <string>
#include <iomanip>
using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::left;
AgendaUI::AgendaUI() {
    userName_ = "";
    userPassword_ = "";
    agendaService_.startAgenda();
}
void AgendaUI::OperationLoop(void) {
    startAgenda();
    string a = getOperation();
    executeOperation(a);
}
void AgendaUI::startAgenda(void) {
    cout << "--------------------------Agenda------------------------" << endl;
    cout << "Action :" << endl;
    cout << "l   - log in Agenda by user name and password" << endl;
    cout << "r   - register an Agenda account" << endl;
    cout << "q   - quit Agenda" << endl;
    cout << "-------------------------------------------------------" << endl << endl << endl;
    cout << "Agenda : ~$ ";
    string a = getOperation();
    if (!executeOperation(a)) {
        cout << "Byebye" << endl;
    }
    
}
std::string AgendaUI::getOperation() {
    string a;
    cin >> a;
    return a;
}
bool AgendaUI::executeOperation(std::string op) {
    if (op == "l") {
        system("clear");
        userLogIn();
    }
    else if (op == "r")  { userRegister(); return true;}
    else if (op == "dc") { deleteUser(); return true;}
    else if (op == "lu") { listAllUsers(); return true;}
    else if (op == "cm") { createMeeting(); return true;}
    else if (op == "la") { listAllMeetings(); return true;}
    else if (op == "las") { listAllSponsorMeetings(); return true;}
    else if (op == "lap") { listAllParticipateMeetings(); return true;}
    else if (op == "qm") { queryMeetingByTitle(); return true;}
    else if (op == "qt") { queryMeetingByTimeInterval(); return true;}
    else if (op == "dm") { deleteMeetingByTitle(); return true;}
    else if (op == "da") { deleteAllMeetings(); return true;}
    else if (op == "o") { userLogOut(); return true;}
    else if (op == "q") { quitAgenda(); return false;}
    return false;
}
void AgendaUI::userLogIn(void) {
    string a, b, c;
    cout << "[log in] [user name] [password]" << endl;
    cout << "[log in] ";
    cin >> a >> b;
    userName_ = a;
    userPassword_ = b;
    if (!agendaService_.userLogIn(a, b)) {
        cout << "[error] log in fail!" << endl << endl;
        cout << "Agenda : ~$ ";
        cout << "--------------------------Agenda------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o   - log out Agenda" << endl;
        cout << "dc  - delete Agenda account" << endl;
        cout << "lu  - list all Agenda user" << endl;
        cout << "cm  - create a meeting" << endl;
        cout << "la  - list all meetings" << endl;
        cout << "las - list all sponsor meetings" << endl;
        cout << "lap - list all participate meetings" << endl;
        cout << "qm  - query meeting by title" << endl;
        cout << "qt  - query meeting by time interval" << endl;
        cout << "dm  - delete meeting by title" << endl;
        cout << "da  - delete all meeting" << endl;
        cout << "--------------------------------------------------------" << endl << endl;
        string a = getOperation();
        executeOperation(a);
    }
    else {
        system("clear");
        cout << "[log in] succeed!" << endl << endl;
        cout << "--------------------------Agenda------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o   - log out Agenda" << endl;
        cout << "dc  - delete Agenda account" << endl;
        cout << "lu  - list all Agenda user" << endl;
        cout << "cm  - create a meeting" << endl;
        cout << "la  - list all meetings" << endl;
        cout << "las - list all sponsor meetings" << endl;
        cout << "lap - list all participate meetings" << endl;
        cout << "qm  - query meeting by title" << endl;
        cout << "qt  - query meeting by time interval" << endl;
        cout << "dm  - delete meeting by title" << endl;
        cout << "da  - delete all meeting" << endl;
        cout << "--------------------------------------------------------" << endl << endl;
        cout << "Agenda@pear : # ";
        string aa = getOperation();
        executeOperation(aa);
    }
}
void AgendaUI::userRegister(void) {
    string a, b, c, d;
    cout << endl << endl;
    cout << "[register] [user name] [password] [email] [phone]" << endl;
    cout << "[register] ";
    cin >> a >> b >> c >> d;
    if (!agendaService_.userRegister(a, b, c, d)) {
         cout << "[error] register fail!" << endl;
         cout << "Agenda : ~$ ";
         string aa = getOperation();
         executeOperation(aa);
    }
    else {
        system("clear");
        cout << "succeed!" << endl;
        startAgenda();
    }
}
void AgendaUI::quitAgenda(void) {
    userName_ = "";
    userPassword_ = "";
    agendaService_.quitAgenda();
}
void AgendaUI::userLogOut(void) {
    cout << endl << endl;
    startAgenda();
}
void AgendaUI::deleteUser(void) {
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        cout << "[delete agenda account] succeed" << endl << endl;
        startAgenda();
    }
}
void AgendaUI::listAllUsers(void) {
    system("clear");
    cout << "--------------------------Agenda------------------------" << endl;
    cout << "Action :" << endl;
    cout << "o   - log out Agenda" << endl;
    cout << "dc  - delete Agenda account" << endl;
    cout << "lu  - list all Agenda user" << endl;
    cout << "cm  - create a meeting" << endl;
    cout << "la  - list all meetings" << endl;
    cout << "las - list all sponsor meetings" << endl;
    cout << "lap - list all participate meetings" << endl;
    cout << "qm  - query meeting by title" << endl;
    cout << "qt  - query meeting by time interval" << endl;
    cout << "dm  - delete meeting by title" << endl;
    cout << "da  - delete all meeting" << endl;
    cout << "--------------------------------------------------------" << endl << endl;
    std::list<User> temp = agendaService_.listAllUsers();
    cout << endl << "[list all users]" << endl;
    cout << left << setw(12) << "name" << left << setw(20) << "email" << left << setw(20) << "phone" << endl;
    std::list<User>::iterator it;
    for (it = temp.begin(); it != temp.end(); it++) {
        cout << left << setw(12) << it->getName() << left << setw(20) <<  it->getEmail() << left << setw(20) << it->getPhone() << endl;
    }
    cout << endl;
    cout << "Agenda@pear : # ";
    string aaa = getOperation();
    executeOperation(aaa);
}
void AgendaUI::createMeeting(void) {
    string a, b, c, d;
    cout << endl;
    cout << "[create meeting] [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] ";
    cin >> a >> b >> c >> d;
    if (agendaService_.createMeeting(userName_, a, b, c, d)) {
        cout << "[create meeting] succeed!" << endl;
        cout << "Agenda@pear : # ";
        string aaa = getOperation();
        executeOperation(aaa);
    }
    else {
        cout << "[error] create meeting fail!" << endl;
        cout << "Agenda@pear : # ";
        string aa = getOperation();
        executeOperation(aa);
    }
}
void AgendaUI::listAllMeetings(void) {
    cout << endl;
    cout << "[list all meetings]" << endl << endl;
    cout << left << setw(12) << "title" << left << setw(20) << "sponsor" << left << setw(20) << "participator" << left << setw(25) << "start time" << left << setw(25) << "end time" << endl;
    std::list<Meeting> temp = agendaService_.listAllMeetings(userName_);
    std::list<Meeting>::iterator it;
    for (it = temp.begin(); it != temp.end(); it++) {
        string a = Date::dateToString(it->getStartDate());
        string b = Date::dateToString(it->getEndDate());
        cout << left << setw(12) << it->getTitle() << left << setw(20) << it->getSponsor() << left << setw(20) << it->getParticipator() << setw(25) <<  a << setw(25) << b << endl;
    }
    cout << "Agenda@pear : # ";
    string aa = getOperation();
    executeOperation(aa);    
}
void AgendaUI::listAllSponsorMeetings(void) {
    cout << endl;
    cout << "[list all sponsor meetings]" << endl << endl;
    cout << left << setw(12) << "title" << left << setw(20) << "sponsor" << left << setw(20) << "participator" << left << setw(25) << "start time" << left << setw(25) << "end time" << endl;
    std::list<Meeting> temp = agendaService_.listAllSponsorMeetings(userName_);
    std::list<Meeting>::iterator it;
    for (it = temp.begin(); it != temp.end(); it++) {
        string a = Date::dateToString(it->getStartDate());
        string b = Date::dateToString(it->getEndDate());
        cout << left << setw(12) << it->getTitle() << left << setw(20) << it->getSponsor() << left << setw(20) << it->getParticipator() << left << setw(25) <<  a << setw(25) << b << endl;
    }
    cout << "Agenda@pear : # ";
    string aa = getOperation();
    executeOperation(aa); 
}
void AgendaUI::listAllParticipateMeetings(void) {
    cout << endl << endl;
    cout << "list all participate meetings]" << endl << endl;
    cout << left << setw(12) << "title" << left << setw(15) << "sponsor" << left << setw(15) << "participator" << left << setw(25) << "start time" << left << setw(25) << "end time" << endl;
    std::list<Meeting> temp = agendaService_.listAllParticipateMeetings(userName_);
    std::list<Meeting>::iterator it;
    for (it = temp.begin(); it != temp.end(); it++) {
        string a = Date::dateToString(it->getStartDate());
        string b = Date::dateToString(it->getEndDate());
        cout << left << setw(12) << it->getTitle() << left << setw(15) << it->getSponsor() << left << setw(15) << it->getParticipator() << left << setw(25) <<  a << setw(25) << b << endl;
    }
    cout << "Agenda@pear : # ";
    string aa = getOperation();
    executeOperation(aa); 
}
void AgendaUI::queryMeetingByTitle(void) {
    string a;
    cout << endl << endl;
    cout << "[query meeting] [title]" << endl;
    cout << "[query meeting] ";
    cin >> a;
    cout << endl;
    cout << left << setw(15) << "sponsor" << left << setw(15) << "participator" << left << setw(25) << "start time" << left << setw(25) << "end time" << endl;
    std::list<Meeting> temp = agendaService_.meetingQuery(userName_, a);
    std::list<Meeting>::iterator it;
    for (it = temp.begin(); it != temp.end(); it++) {
        string a = Date::dateToString(it->getStartDate());
        string b = Date::dateToString(it->getEndDate());
        cout << left << setw(15) << it->getSponsor() << left << setw(15) << it->getParticipator() << left << setw(25) <<  a << left << setw(25) << b << endl;
    }
    cout << endl;
    cout << "Agenda@pear : # ";
    string aa = getOperation();
    executeOperation(aa); 
}
void AgendaUI::queryMeetingByTimeInterval(void) {
    string a, b;
    cout << endl << endl;
    cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meeting] ";
    cin >> a >> b;
    cout << endl;
    cout << "[query meetings]" << endl;
    cout << left << setw(15) << "sponsor" << left << setw(15) << "participator" << left << setw(25) << "start time" << left << setw(25) << "end time" << endl;
    std::list<Meeting> temp = agendaService_.meetingQuery(userName_, a, b);
    std::list<Meeting>::iterator it;
    for (it = temp.begin(); it != temp.end(); it++) {
        string aa = Date::dateToString(it->getStartDate());
        string bb = Date::dateToString(it->getEndDate());
        cout << left << setw(15) << it->getSponsor() << left << setw(15) << it->getParticipator() << left << setw(25) <<  a << left << setw(25) << b << endl;
    }
    cout << endl;
    cout << "Agenda@pear : # ";
    string aa = getOperation();
    executeOperation(aa); 
}
void AgendaUI::deleteMeetingByTitle(void) {
    cout << endl << endl;
    string a;
    cout << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    cin >> a;
    cout << endl;
    if (agendaService_.deleteMeeting(userName_, a)) {
        cout << "[delete meeting by title] succeed!" << endl;
        cout << "Agenda@pear : # ";
        string aa = getOperation();
        executeOperation(aa); 
    }
    else {
        cout << "[error] delete meeting fail!" << endl;
        cout << "Agenda@pear : # ";
        string aa = getOperation();
        executeOperation(aa); 
    }
}
void AgendaUI::deleteAllMeetings(void) {
    cout << endl;
    if (agendaService_.deleteAllMeetings(userName_))
        cout << "[delete all meeting] succeed!" << endl;
    cout << "Agenda@pear : # ";
    string aa = getOperation();
    executeOperation(aa);
}
void AgendaUI::printMeetings(std::list<Meeting> meetings) {}

