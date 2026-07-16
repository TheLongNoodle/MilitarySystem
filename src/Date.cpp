#include "Date.h"
#include <iostream>

Date::Date(int day, int month, int year) : day(day), month(month), year(year)
{
}

int Date::getDay()   const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear()  const
{
    return year;
}

bool Date::setDay(int d)
{
    if (d < 1 || d > 31)
    {
        return false;
    }
    day = d;
    return true;
}

bool Date::setMonth(int m)
{
    if (m < 1 || m > 12)
    {
        return false;
    }
    month = m;
    return true;
}

bool Date::setYear(int y)
{
    if (y < 1900 || y > 2100)
    {
        return false;
    }
    year = y;
    return true;
}

bool Date::isValid() const
{
    if (year < 1900 || year  > 2100)
    {
        return false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1)
    {
        return false;
    }

    static const int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int dim = daysInMonth[month - 1];
    if (month == 2)
    {
        const bool leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
        if (leap) dim = 29;
    }
    return day <= dim;
}

void Date::print() const
{
    std::cout << *this;
}

bool operator==(const Date& a, const Date& b)
{
    return a.getDay() == b.getDay() && a.getMonth() == b.getMonth() && a.getYear() == b.getYear();
}

bool operator<(const Date& a, const Date& b)
{
    if (a.getYear() != b.getYear())
    {
        return a.getYear() < b.getYear();
    }
    if (a.getMonth() != b.getMonth())
    {
        return a.getMonth() < b.getMonth();
    }
    return a.getDay() < b.getDay();
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.getDay() << '/' << d.getMonth() << '/' << d.getYear();
    return os;
}
