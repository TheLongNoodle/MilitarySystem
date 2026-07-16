#ifndef DATE_H
#define DATE_H

#include <iosfwd>

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool setDay(int day);
    bool setMonth(int month);
    bool setYear(int year);

    bool isValid() const;
    void print() const;
};

bool operator==(const Date& a, const Date& b);
bool operator< (const Date& a, const Date& b);
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
