#include "Storage.h"
#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <iostream>
using std::list;
using std::string;
Storage* Storage::instance_ = NULL;

Storage::Storage() {
    readFromFile("./");
}

bool Storage::readFromFile(const char *fpath) {
    if (fpath == NULL) return false;
    std::ifstream inFile;
    std::string s(fpath);
    inFile.open("User.csv");
    if (!inFile) {
        return false;
    }
    std::string line;
    getline(inFile, line);
    while (getline(inFile, line)) {
        std::string a, b, c, d; 
        int i, j, k, m = 0;
        for (i = 0; i < line.size(); i++ ) {
            if (line[i] == '\"' && m == 0) {
                for (j = i+1; j < line.size(); j++) {
                    if (line[j] == ',' && line[j-1] == '\"') {
                        m++;
                        for (k = i+1; k < j-1; k++) {
                            a.push_back(line[k]);
                        }
                        i = j;
                        break;
                    }
                }
            }
            if (line[i] == '\"' && m == 1) {
                for (j = i+1; j < line.size(); j++) {
                    if (line[j] == ',' && line[j-1] == '\"') {
                        m++;
                        for (k = i+1; k < j-1; k++) {
                            b.push_back(line[k]);
                        }
                        i = j;
                        break;
                    }
                }
            }
            if (line[i] == '\"' && m == 2) {
                for (j = i+1; j < line.size(); j++) {
                    if (line[j] == ',' && line[j-1] == '\"') {
                        m++;
                        for (k = i+1; k < j-1; k++) {
                            c.push_back(line[k]);
                        }
                        i = j;
                        break;
                    }
                }
            }
            if (line[i] == '\"' && m == 3) {
                for (j = i+1; j < line.size(); j++) {
                    if (line[j] == '\"' && j == line.size()-1) {
                        for (k = i+1; k < j; k++) {
                            d.push_back(line[k]);
                        }
                    }
                }
            }
        }
        User user(a, b, c, d);
        createUser(user);
    }
    inFile.close();
    std::ifstream inFile1;
    string ss(fpath);
    inFile1.open("Meeting.csv");
    if (!inFile1) {
        return false;
    }
    std::string line1;
    getline(inFile1, line1);
    while (getline(inFile1, line1)) {
        std::string a1, b1, e1;
        Date c1, d1;
        int i, j, k, l, m = 0;
        for (i = 0; i < line1.size(); i++ ) {
            if (line1[i] == '\"' && m == 0) {
                for (j = i+1; j < line1.size(); j++) {
                    if (line1[j] == ',' && line1[j-1] == '\"') {
                        m++;
                        for (k = i+1; k < j-1; k++) {
                            a1.push_back(line1[k]);
                        }
                        i = j;
                        break;
                    }
                }
            }
            if (line1[i] == '\"' && m == 1) {
                for (j = i+1; j < line1.size(); j++) {
                    if (line1[j] == ',' && line1[j-1] == '\"') {
                        m++;
                        for (k = i+1; k < j-1; k++) {
                            b1.push_back(line1[k]);
                        }
                        i = j;
                        break;
                    }
                }
            }
            if (line1[i] == '\"' && m == 2) {
                char c2[20] = {'\0'};
                for (j = i+1; j < line1.size(); j++) {
                    if (line1[j] == ',' && line1[j-1] == '\"') {
                        m++;
                        l = 0;
                        for (k = i+1; k < j-1; k++) {
                            c2[l] = line1[k];
                            l++;
                        }
                        i = j;
                        break;
                    }
                }
                c1.stringToDate(c2);
            }
            if (line1[i] == '\"' && m == 3) {
                char d2[20] = {'\0'};
                for (j = i+1; j < line1.size(); j++) {
                    if (line1[j] == ',' && line1[j-1] == '\"') {
                        m++;
                        l = 0;
                        for (k = i+1; k < j-1; k++) {
                            d2[l] = line1[k];
                            l++;
                        }
                        i = j;
                        break;
                    }
                }
                d1.stringToDate(d2);
            }
            if (line1[i] == '\"' && m == 4) {
                for (j = i+1; j < line1.size(); j++) {
                    if (line1[j] == '\"' && j == line1.size()-1) {
                        for (k = i+1; k < j; k++) {
                            e1.push_back(line1[k]);
                        }
                    }
                }
            }
        }
        Meeting meeting(a1, b1, c1, d1, e1);
        createMeeting(meeting);
    }
    inFile.close();
}

bool Storage::writeToFile(const char *fpath) {
    std::ofstream outFile;
    string s(fpath);
    outFile.open("User.csv");
    outFile << "\"name\"," << "\"password\"," << "\"email\"," << "\"phone\"\n";
    std::list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); it++) {
        outFile << "\"" << it->getName() << "\"," << "\""
        << it->getPassword() << "\"," << "\"" << it->getEmail()
        << "\"," << "\"" << it->getPhone() << "\"\n";
    }
    outFile.close();
    std::ofstream outFile1;
    string s1(fpath);
    outFile1.open("Meeting.csv");
    if (meetingList_.empty()) return false;
    outFile1 << "\"sponsor\"," << "\"participator\"," << "\"sdate\"," 
            << "\"edate\"," << "\"title\"\n";
    std::list<Meeting>::iterator it1;
    for (it1 = meetingList_.begin(); it1 != meetingList_.end();it1++) {
        string a = it1->getStartDate().dateToString(it1->getStartDate());
        string b = it1->getEndDate().dateToString(it1->getEndDate());
        outFile1 << "\"" << it1->getSponsor() << "\","
                << "\""<< it1->getParticipator() << "\","
                << "\"" << a
                << "\"," << "\"" << b
                << "\"," << "\"" << it1->getTitle() << "\"\n";
    }
    outFile1.close();
}

Storage* Storage::getInstance(void) {
    if (instance_ == NULL) {
        instance_ = new Storage();
    }
    return instance_;
}

Storage::~Storage() {
    sync();
    instance_ = NULL;
}

void Storage::createUser(const User& a) {
    std::list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); it++) {
        if (it->getName() == a.getName()) break;
    }
    if (it == userList_.end()) userList_.push_back(a);
}
std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
    std::list<User> temp;
    std::list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); it++) {
        if (filter(*it)) temp.push_back(*it);
    }
    return temp;
}
int Storage::updateUser(std::function<bool(const User&)> filter,
        std::function<void(User&)> switcher) {
    int count = 0;
    std::list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); it++) {
        if (filter(*it)) {
            switcher(*it);
            count++;
        }
    }
    return count;
}
int Storage::deleteUser(std::function<bool(const User& a)> filter) {
    int count = 0;
    std::list<User>::iterator it, it1;
    for (it = userList_.begin(); it != userList_.end();it++) {
        if (filter(*it)) {
            it1 = it;
            it--;
            userList_.erase(it1);
            count++;
        }
    }
    return count;
}
void Storage::createMeeting(const Meeting& a) {
    meetingList_.push_back(a);
}
std::list<Meeting> Storage::queryMeeting(
                       std::function<bool(const Meeting&)> filter) {
    std::list<Meeting> temp;
    std::list<Meeting>::iterator it;
    for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
        if (filter(*it)) temp.push_back(*it);
    }
    return temp;
};
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
        std::function<void(Meeting&)> switcher) {
    int count = 0;
    std::list<Meeting>::iterator it;
    for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
        if (filter(*it)) {
            switcher(*it);
            count++;
        }
    }
    return count;
}
int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    int count = 0;
    std::list<Meeting>::iterator it, it1;
    for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
        if (filter(*it)) {
            it1 = it;
            it--;
            meetingList_.erase(it1);
            count++;
        }
    }
    return count;
}
bool Storage::sync(void) {
    return writeToFile("./");
}

