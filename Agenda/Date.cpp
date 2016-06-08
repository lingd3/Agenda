#include "Date.h"
#include <string>
#include <sstream>
Date::Date() {
    year_ = 0;
    month_ = 0;
    day_ = 0;
    hour_ = 0;
    minute_ = 0;
}
Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}
int Date::getYear(void) const {
    return year_;
}
void Date::setYear(int year) {
    year_ = year;
}
int Date::getMonth(void) const {
    return month_;
}
void Date::setMonth(int month) {
    month_ = month;
}
int Date::getDay(void) const {
    return day_;
}
void Date::setDay(int day) {
    day_ = day;
}
int Date::getHour(void) const {
    return hour_;
}
void Date::setHour(int hour) {
    hour_ = hour;
}
int Date::getMinute(void) const {
    return minute_;
}
void Date::setMinute(int minute) {
    minute_ = minute;
}
bool Date::isValid(Date date) {
    if (date.year_ < 1000 || date.year_ > 9999 || date.month_ < 1 ||
        date.month_ > 12 || date.day_ <= 0 || date.day_ > 31 ||
        date.hour_ < 0 || date.hour_ >= 24 || date.minute_ < 0 ||
        date.minute_ >= 60) return false;
    if ((date.month_ == 4 || date.month_ == 6 || date.month_ == 9 ||
        date.month_ == 11) && date.day_ == 31) return false;
    if (date.month_ == 2) {
      if (date.year_%400 == 0 || date.year_%4 == 0 &&
	  date.year_%100 != 0) {
            if (date.day_ > 29) return false;
        }
        else {
            if (date.day_ > 28) return false;
        }
    }
    return true;
}
Date Date::stringToDate(std::string dateString) {
    Date temp;
    temp.year_ = (dateString[0]-'0')*1000+(dateString[1]-'0')*100+(dateString[2]-'0')*10+(dateString[3]-'0');
    temp.month_ = (dateString[5]-'0')*10+(dateString[6]-'0');
    temp.day_ = (dateString[8]-'0')*10+dateString[9]-'0';
    temp.hour_ = (dateString[11]-'0')*10+(dateString[12]-'0');
    temp.minute_ = (dateString[14]-'0')*10+dateString[15]-'0';
    return temp;
}
std::string Date::dateToString(Date date) {
    std::string a = "", b = "";
    std::stringstream ss;
    ss << date.year_;
    ss >> b;
    a = a+b+"-";
    b = "";
    if (date.month_ < 10) {
        std::stringstream ss;
        ss << date.month_;
        ss >> b;
        a = a+"0"+b+"-";
    }
    else if (date.month_ >= 10) {
        std::stringstream ss;
        ss << date.month_;
        ss >> b;
        a = a+b+"-";
    }
    b = "";
    if (date.day_ < 10) {
        std::stringstream ss;
        ss << date.day_;
        ss >> b;
        a = a+"0"+b+"/";
    }
    else if (date.day_ >= 10) {
        std::stringstream ss;
        ss << date.day_;
        ss >> b;
        a = a+b+"/";
    }
    b = "";
    if (date.hour_ < 10) {
        std::stringstream ss;
        ss << date.hour_;
        ss >> b;
        a = a+"0"+b+":";
    }
    else if (date.hour_ >= 10) {
        std::stringstream ss;
        ss << date.hour_;
        ss >> b;
        a = a+b+":";
    }
    b = "";
    if (date.minute_ < 10) {
        std::stringstream ss;
        ss << date.minute_;
        ss >> b;
        a = a+"0"+b;
    }
    else if (date.minute_ >= 10) {
        std::stringstream ss;
        ss << date.minute_;
        ss >> b;
        a = a+b;
    }
    return a;
}
Date& Date::operator=(const Date& date) {
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
    hour_ = date.hour_;
    minute_ = date.minute_;
    return *this;
}
bool Date::operator==(const Date& date) const {
    if (year_ != date.year_) return false;
    if (month_ != date.month_) return false;
    if (day_ != date.day_) return false;
    if (hour_ != date.hour_) return false;
    if (minute_ != date.minute_) return false;
    return true;
}
bool Date::operator>(const Date& date) const {
    if (year_ > date.year_) return true;
    if (year_ < date.year_) return false;
    else if (year_ == date.year_) {
        if (month_ > date.month_) return true;
        if (month_ < date.month_) return false;
        else if (month_ == date.month_) {
            if (day_ > date.day_) return true;
            if (day_ < date.day_) return false;
            else if (day_ == date.day_) {
                if (hour_ > date.hour_) return true;
                if (hour_ < date.hour_) return false;
                else if (hour_ == date.hour_) {
                    if (minute_ > date.minute_) return true;
                    if (minute_ <= date.minute_) return false;
                }
            }
        }
    }
}
bool Date::operator<(const Date& date) const {
    if (*this == date || *this > date) return false;
    return true;
}
bool Date::operator>=(const Date& date) const {
    if (*this == date || *this > date) return true;
    return false;
}
bool Date::operator<=(const Date& date) const {
    if (*this > date) return false;
    return true;
}

