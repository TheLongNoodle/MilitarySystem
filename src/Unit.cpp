#include "Unit.h"
#include "Soldier.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

int Unit::s_nextUnitId = 100;

Unit::Unit(const std::string& unitName) : unitName(unitName)
{
    if (unitName.empty())
    {
        throw std::invalid_argument("Unit: name must not be empty");
    }
    unitId = s_nextUnitId++;
}

const std::string& Unit::getUnitName() const
{
    return unitName;
}
int Unit::getUnitId() const
{
    return unitId;
}
int Unit::getSoldierCount() const
{
    return static_cast<int>(soldiers.size());
}

Soldier* Unit::getSoldier(int index) const
{
    if (index < 0 || index >= static_cast<int>(soldiers.size()))
    {
        return nullptr;
    }
    return soldiers[index];
}

bool Unit::setUnitName(const std::string& n)
{
    if (n.empty())
    {
        return false;
    }
    unitName = n;
    return true;
}

bool Unit::addSoldier(Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    // Compare by domain identity (personal number) via Soldier::operator==,
    // not by address - the same person must never be listed twice.
    auto sameSoldier = [soldier](const Soldier* existing)
                       { return *existing == *soldier; };
    if (std::find_if(soldiers.begin(), soldiers.end(), sameSoldier) != soldiers.end())
    {
        return false;
    }
    soldiers.push_back(soldier);
    return true;
}

bool Unit::removeSoldier(const Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    auto it = std::find(soldiers.begin(), soldiers.end(), soldier);
    if (it == soldiers.end())
    {
        return false;
    }
    soldiers.erase(it);
    return true;
}

void Unit::printSoldiers() const
{
    std::cout << "  Unit [" << unitId << "] '" << unitName
              << "' (" << soldiers.size() << " soldier(s)):" << std::endl;
    for (const Soldier* soldier : soldiers)
    {
        std::cout << "    " << *soldier << std::endl;
    }
}

Unit& Unit::operator+=(Soldier* soldier)
{
    addSoldier(soldier);
    return *this;
}
