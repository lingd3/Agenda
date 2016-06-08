#include "AgendaService.h"
#include <list>
#include "User.h"
#include "Meeting.h"
#include "Date.h"
#include <string>
#include <functional>
using std::string;
AgendaService::AgendaService() {
    storage_ = Storage::getInstance();
}
AgendaService::~AgendaService() {
   if (storage_) {
   storage_->sync();
   delete storage_;
   }
}
bool AgendaService::userLogIn(std::string userName, std::string password) {
    std::list<User> temp;
    temp = storage_->queryUser([&](const User& u) {
        return u.getName() == userName && u.getPassword() == password;
    });
    if (temp.empty()) return false;
    return true;
}
bool AgendaService::userRegister(std::string userName, std::string password,
                    std::string email, std::string phone) {
    std::list<User> temp;
    temp = storage_->queryUser([&](const User& u) {
        return u.getName() == userName;
    });    
    if (!temp.empty()) return false;
    User user(userName, password, email, phone);
    storage_->createUser(user);
    return true;
}
bool AgendaService::deleteUser(std::string userName, std::string password) {
    if (!userLogIn(userName, password)) return false;
    int a = storage_->deleteMeeting([&](const Meeting& u) {
        return (u.getSponsor() == userName || u.getParticipator() == userName);
    });
    int b = storage_->deleteUser([&](const User& u) {
        return u.getName() == userName && u.getPassword() == password;
    });
    if (b) return true;
    return false;
}
std::list<User> AgendaService::listAllUsers(void) {
    std::list<User> temp;
    temp = storage_->queryUser([&](const User& u) {
        return true;
    });
    return temp;
}
bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate) {
    if (startDate.size() != 16 || endDate.size() != 16) return false;
    if (userName == participator) return false; 
    std::list<User> temp1;
    temp1 = storage_->queryUser([&](const User& u) {
        return u.getName() == userName;
    });
    if (temp1.empty()) return false;
    std::list<User> temp2;
    temp2 = storage_->queryUser([&](const User& u) {
        return u.getName() == participator;
    });
    if (temp2.empty()) return false;
    std::list<Meeting> temp, temp3;
    Date a = Date::stringToDate(startDate);
    Date b = Date::stringToDate(endDate);
    if (!Date::isValid(a) || !Date::isValid(b)) return false;
    if (a >= b) return false;
    temp3 = storage_->queryMeeting([&](const Meeting& u) {
        return u.getTitle() == title;
    });
    if (!temp3.empty()) return false;
    temp = storage_->queryMeeting([&](const Meeting& u) {
        return (u.getSponsor() == userName || u.getParticipator() == userName || u.getSponsor() == participator || u.getParticipator() == participator) && (u.getStartDate() <= a && u.getEndDate() > a || u.getStartDate() < b && u.getEndDate() >= b || u.getStartDate() >= a && u.getEndDate() <= b || u.getStartDate() <= a && u.getEndDate() >= b);
    });
    if (!temp.empty()) return false;
    Meeting aa(userName, participator, a, b, title);
    storage_->createMeeting(aa);
    return true;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    std::list<Meeting> temp;
    temp = storage_->queryMeeting([&](const Meeting& u) {
        return (u.getSponsor() == userName || u.getParticipator() == userName) && u.getTitle() == title;
    });
    return temp;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate, std::string endDate) {
    std::list<Meeting> temp;
    Date a, b;
    a = Date::stringToDate(startDate);
    b = Date::stringToDate(endDate);
    temp = storage_->queryMeeting([&](const Meeting& u) {
        return (u.getSponsor() == userName || u.getParticipator() == userName) && (u.getStartDate() <= a && u.getEndDate() >= a || u.getStartDate() <= b && u.getEndDate() >= b || u.getStartDate() >= a && u.getEndDate() <= b || u.getStartDate() <= a && u.getEndDate() >= b);
    });
    return temp;
}
std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    std::list<Meeting> temp;
    temp = storage_->queryMeeting([&](const Meeting& u) {
        return u.getSponsor() == userName || u.getParticipator() == userName;
    });
    return temp;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    std::list<Meeting> temp;
    temp = storage_->queryMeeting([&](const Meeting& u) {
        return u.getSponsor() == userName;
    });
    return temp;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    std::list<Meeting> temp;
    temp = storage_->queryMeeting([&](const Meeting& u) {
        return u.getParticipator() == userName;
    });
    return temp;
}
bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    int a = storage_->deleteMeeting([&](const Meeting& u) {
        return u.getSponsor() == userName && u.getTitle() == title;
    });
    if (a == 0) return false;
    return true;
}
bool AgendaService::deleteAllMeetings(std::string userName) {
    std::list<User> temp;
    temp = storage_->queryUser([&](const User& u) {
        return u.getName() == userName;
    });    
    if (temp.empty()) return false;
    int a = storage_->deleteMeeting([&](const Meeting& u) {
        return u.getSponsor() == userName;
    });
    if (a == 0) return false;
    return true;
}
void AgendaService::startAgenda(void) {
    storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
    storage_->sync();
    if (storage_) delete storage_;
    storage_ = NULL;
}

