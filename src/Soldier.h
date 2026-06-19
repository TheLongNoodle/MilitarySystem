#ifndef SOLDIER_H
#define SOLDIER_H

#include "Date.h"
#include <iosfwd>

class Unit;

class Soldier {
public:
    enum class eRank {
        PRIVATE,
        CORPORAL,
        SERGEANT,
        LIEUTENANT,
        CAPTAIN,
        MAJOR
    };

private:
    static int s_nextId;
    static int s_nextPersonalNumber;

    char* name;
    int   id;
    Date  birthDate;

    int   personalNumber;
    char* role;
    eRank rank;
    Unit* unit;

public:
    Soldier(const char* name,
            const Date& birthDate,
            const char* role,
            eRank rank);
    virtual ~Soldier();

    Soldier(const Soldier& other) = delete;
    Soldier& operator=(const Soldier& other) = delete;

    const char* getName() const;
    int         getId() const;
    const Date& getBirthDate() const;
    int         getPersonalNumber() const;
    const char* getRole() const;
    eRank       getRank() const;
    Unit*       getUnit() const;

    bool setName(const char* name);
    bool setBirthDate(const Date& birthDate);
    bool setRole(const char* role);
    bool setRank(eRank rank);
    bool setUnit(Unit* newUnit);

    virtual void print() const;
};

// ---- Non-member operators on Soldier ------------------------------------
// Soldier (and through inheritance, Officer) has a unique identity given by
// its personalNumber. operator== reflects that identity-based equality:
// two distinct Soldier objects are never "equal", and the same Soldier
// looked up twice is. operator<< is the streamable equivalent of print()
// and is virtual-dispatched through it, so it polymorphically prints an
// Officer's commanded-soldiers block when called on an Officer reference.
bool operator==(const Soldier& a, const Soldier& b);
std::ostream& operator<<(std::ostream& os, const Soldier& s);

#endif // SOLDIER_H
