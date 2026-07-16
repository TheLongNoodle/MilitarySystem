#include "Soldier.h"
#include "Unit.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>

int Soldier::s_nextId = 1;
int Soldier::s_nextPersonalNumber = 100000;

static const char* rankName(Soldier::eRank r)
{
    switch (r)
    {
        case Soldier::eRank::PRIVATE:
            return "PRIVATE";
        case Soldier::eRank::CORPORAL:
            return "CORPORAL";
        case Soldier::eRank::SERGEANT:
            return "SERGEANT";
        case Soldier::eRank::LIEUTENANT: 
            return "LIEUTENANT";
        case Soldier::eRank::CAPTAIN:
            return "CAPTAIN";
        case Soldier::eRank::MAJOR:
            return "MAJOR";
    }
    return "?";
}

Soldier::Soldier(const char* name, const Date& birthDate, const char* role, eRank rank)
    : name(nullptr), birthDate(birthDate), role(nullptr), rank(rank), unit(nullptr)
{
    if (!name || name[0] == '\0')
    {
        throw std::invalid_argument("Soldier: name must not be empty");
    }
    if (!role || role[0] == '\0')
    {
        throw std::invalid_argument("Soldier: role must not be empty");
    }

    this->name = utils::dupString(name);
    try
    {
        this->role = utils::dupString(role);
    }
    catch (...)
    {
        delete[] this->name;
        throw;
    }
    id = s_nextId++;
    personalNumber = s_nextPersonalNumber++;
}

Soldier::~Soldier()
{
    delete[] name;
    delete[] role;
}

const char* Soldier::getName() const
{
    return name;
}

int Soldier::getId() const
{
    return id;
}

const Date& Soldier::getBirthDate() const
{
    return birthDate;
}

int Soldier::getPersonalNumber() const
{
    return personalNumber;
}

const char* Soldier::getRole() const
{
    return role;
}

Soldier::eRank Soldier::getRank() const
{
    return rank;
}

Unit* Soldier::getUnit() const
{
    return unit;
}

bool Soldier::setName(const char* n)
{
    if (!n || n[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(n);
    delete[] name;
    name = tmp;
    return true;
}

bool Soldier::setBirthDate(const Date& bd)
{
    if (!bd.isValid())
    {
        return false;
    }
    birthDate = bd;
    return true;
}

bool Soldier::setRole(const char* r)
{
    if (!r || r[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(r);
    delete[] role;
    role = tmp;
    return true;
}

bool Soldier::setRank(eRank r)
{
    rank = r;
    return true;
}

bool Soldier::setUnit(Unit* newUnit)
{
    unit = newUnit;
    return true;
}

void Soldier::print() const
{
    std::cout << "  Soldier [#" << personalNumber << "] " << name
              << " | role: " << role
              << " | rank: " << rankName(rank)
              << " | born: " << birthDate
              << " | unit: " << (unit ? unit->getUnitName() : "(none)")
              << std::endl;
}

bool operator==(const Soldier& a, const Soldier& b)
{
    return a.getPersonalNumber() == b.getPersonalNumber();
}

std::ostream& operator<<(std::ostream& os, const Soldier& s)
{
    os << "Soldier[#" << s.getPersonalNumber() << ' ' << s.getName()
       << ", " << rankName(s.getRank()) << ']';
    return os;
}
