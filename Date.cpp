#include "Date.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Date::Date(){
    
}
Date::Date (int &day , int &month , int &year , bool &flag){
    // Day validation
        try {
            set_day (day);
            flag = 1;
        }
        catch (out_of_range &a) {
            cout <<  a.what() << endl;
        }
    if (flag){
         // month validation
         try {
            set_month (month);
        }
        catch (out_of_range &a) {
            flag = 0;
            cout <<  a.what() << endl;
        }
    }
    if (flag){
        // year validation
        try {
            set_year (year);
        }
        catch (out_of_range &a) {
            flag = 0;
            cout <<  a.what() << endl;
        }
    }
}

void Date::set_day(int day){
    if (day>0 && day<31){
        this->day = day;
    }
    else {
        throw out_of_range(
            "! <Day> input is not correct! Please try again."
        );
    }
}

void Date::set_month(int month){
    if (month>0 && month<13){
        this->month = month;
    }
    else {
    throw out_of_range(
        "! <month> input is not correct! Please try again."
    );
    }
}

void Date::set_year(int year){
    if (year < 1403){
        this->year = year;
    }
    else {
    throw out_of_range(
        "! <Year> input is not correct! Please try again."
    );
    }
}

int Date::get_day() const{
    return day;
}

int Date::get_month() const{
    return month;
}

int Date::get_year() const{
    return year;
}