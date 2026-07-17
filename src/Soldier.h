#ifndef SOLDIER_H
#define SOLDIER_H

#include "Date.h"
#include <string>
#include <iosfwd>

class Unit;

class Soldier
{
public:
    enum class eRank
    {
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

    std::string name;
    int id;
    Date birthDate;

    int personalNumber;
    std::string role;
    eRank rank;
    Unit* unit;

public:
    Soldier(const std::string& name, const Date& birthDate,
            const std::string& role, eRank rank);
    // Part 3: string members freed the destructor of any work, but the class
    // is a polymorphic base (Officer), so a virtual destructor must remain.
    virtual ~Soldier() = default;

    // Copying stays deleted: a Soldier has a unique identity (personal
    // number) and a back-pointer from its Unit; a copy would break both.
    Soldier(const Soldier& other) = delete;
    Soldier& operator=(const Soldier& other) = delete;

    const std::string& getName() const;
    int getId() const;
    const Date& getBirthDate() const;
    int getPersonalNumber() const;
    const std::string& getRole() const;
    eRank getRank() const;
    Unit* getUnit() const;

    bool setName(const std::string& name);
    bool setBirthDate(const Date& birthDate);
    bool setRole(const std::string& role);
    bool setRank(eRank rank);
    bool setUnit(Unit* newUnit);

    virtual void print() const;
};

bool operator==(const Soldier& a, const Soldier& b);
std::ostream& operator<<(std::ostream& os, const Soldier& s);

#endif
