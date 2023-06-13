
#ifndef Date_H
#define Date_H

#include "terminal.h"

class Date {

public:

    Date();
    Date (int& , int&  , int& , bool&, Terminal t);
    void set_day(int);
    void set_month(int);
    void set_year(int);
    int get_day() const;
    int get_month() const;
    int get_year() const;

private:
    int day=0;
    int month=0;
    int year=0;
};

#endif