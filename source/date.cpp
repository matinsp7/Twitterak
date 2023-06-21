#include <stdexcept>
#include "../include/date.h"
#include "../include/terminal.h"

using namespace std;

Date::Date () {
    //defult constructor
}

Date::Date (int d , int m , int y , Terminal t){
    try {
        set_day (d);
        set_month (m);
        set_year (y);
        t.sendSuccessMessage ("Your birthdate has been successfully changed.");
    }
    catch (out_of_range &err){
        t.throwError(err.what());
    }
}

void Date::set_day(int day){
    if (day>0 && day<31){
        this->day = day;
    }
    else {
        throw out_of_range(
            "<Day> input is not correct."
        );
    }
}

void Date::set_month(int month){
    if (month>0 && month<13){
        this->month = month;
    }
    else {
        throw out_of_range(
            "<month> input is not correct."
        );
    }
}

void Date::set_year(int year){
    if (year < 2024){
        this->year = year;
    }
    else {
        throw out_of_range(
            "<Year> input is not correct."
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
