#ifndef SOLDIER_H
#define SOLDIER_H

#include "Person.h"

class Unit;

class Soldier : public Person {
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
    static int s_nextPersonalNumber;

    int   personalNumber;
    char* role;
    eRank rank;
    Unit* unit;

public:
    Soldier(const char* name,
            const Date& birthDate,
            const char* role,
            eRank rank);
    ~Soldier();

    Soldier(const Soldier& other) = delete;
    Soldier& operator=(const Soldier& other) = delete;

    int         getPersonalNumber() const;
    const char* getRole() const;
    eRank       getRank() const;
    Unit*       getUnit() const;

    bool setRole(const char* role);
    bool setRank(eRank rank);
    bool setUnit(Unit* newUnit);

    void print() const override;
};

#endif // SOLDIER_H
