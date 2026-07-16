#include "Unit.h"
#include "Soldier.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>

int Unit::s_nextUnitId = 100;

Unit::Unit(const char* unitName) : unitName(nullptr), soldiers(nullptr)
{
    count = 0;

    if (!unitName || unitName[0] == '\0')
    {
        throw std::invalid_argument("Unit: name must not be empty");
    }

    this->unitName = utils::dupString(unitName);
    try
    {
        capacity = 8;
        soldiers = new Soldier*[capacity];
    }
    catch (...)
    {
        delete[] this->unitName;
        throw;
    }
    unitId = s_nextUnitId++;
}

Unit::~Unit()
{
    delete[] unitName;
    delete[] soldiers;
}

const char* Unit::getUnitName() const
{
    return unitName;
}
int Unit::getUnitId() const
{
    return unitId;
}
int Unit::getSoldierCount() const
{
    return count;
}

Soldier* Unit::getSoldier(int index) const
{
    if (index < 0 || index >= count)
    {
        return nullptr;
    }
    return soldiers[index];
}

bool Unit::setUnitName(const char* n)
{
    if (!n || n[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(n);
    delete[] unitName;
    unitName = tmp;
    return true;
}

bool Unit::addSoldier(Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    for (int i = 0; i < count; ++i)
    {
        if (soldiers[i] == soldier)
        {
            return false;
        }
    }

    if (count == capacity)
    {
        const int newCap = capacity * 2;
        Soldier** larger = new Soldier*[newCap];
        for (int i = 0; i < count; ++i)
        {
            larger[i] = soldiers[i];
        }
        delete[] soldiers;
        soldiers = larger;
        capacity = newCap;
    }
    soldiers[count++] = soldier;
    return true;
}

bool Unit::removeSoldier(const Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    for (int i = 0; i < count; ++i)
    {
        if (soldiers[i] == soldier)
        {
            for (int j = i; j < count - 1; ++j)
            {
                soldiers[j] = soldiers[j + 1];
            }
            --count;
            return true;
        }
    }
    return false;
}

void Unit::printSoldiers() const
{
    std::cout << "  Unit [" << unitId << "] '" << unitName
              << "' (" << count << " soldier(s)):" << std::endl;
    for (int i = 0; i < count; ++i)
    {
        std::cout << "    " << *soldiers[i] << std::endl;
    }
}

Unit& Unit::operator+=(Soldier* soldier)
{
    addSoldier(soldier);
    return *this;
}
