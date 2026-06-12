#ifndef PERSON_H
#define PERSON_H

#include "Date.h"

class Person {
private:
    static int s_nextId;

    char* name;
    int   id;
    Date  birthDate;

public:
    Person(const char* name, const Date& birthDate);
    // virtual 
    ~Person();

    Person(const Person& other) = delete;
    Person& operator=(const Person& other) = delete;

    const char* getName() const;
    int         getId() const;
    const Date& getBirthDate() const;

    bool setName(const char* name);
    bool setBirthDate(const Date& birthDate);

    // virtual 
    void print() const = 0;
};

#endif // PERSON_H
