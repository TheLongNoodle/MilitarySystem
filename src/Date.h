#ifndef DATE_H
#define DATE_H

#include <iosfwd>

class Date {
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

// ---- Non-member operators on Date (value type) --------------------------
// Date is a value type with no resources to own, no virtual methods and no
// invariants outside its three integer fields, so non-member relational
// and stream operators are the idiomatic C++ choice. operator< compares
// chronologically (year, then month, then day). operator<< replaces print()
// at call sites that want streamed output (e.g. inside Soldier's operator<<).
bool operator==(const Date& a, const Date& b);
bool operator< (const Date& a, const Date& b);
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif // DATE_H
