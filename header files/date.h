
#ifndef Date_H
#define Date_H
class Date {

public:

    Date();
    Date (int& , int&  , int& , bool&);
    void set_day(int);
    void set_month(int);
    void set_year(int);
    int get_day() const;
    int get_month() const;
    int get_year() const;

private:

    int day;
    int month;
    int year;
};

#endif