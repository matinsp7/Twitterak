
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
<<<<<<< HEAD:header files/date.h

private:

    int day;
    int month;
    int year;
=======
    private:
    int day=0;
    int month=0;
    int year=0;
>>>>>>> e1728afadd55aa8f9b102378cb4d16b8436cffc7:Date.h
};

#endif