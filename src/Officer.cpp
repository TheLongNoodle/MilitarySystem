#include "Officer.h"
#include "Soldier.h"
#include <iostream>

Officer::Officer(const char* name, const Date& birthDate, const char* role, eRank rank)
    : Soldier(name, birthDate, role, rank), commandedSoldiers(nullptr)
{
    commandedCount = 0;
    commandedCapacity = 4;
    commandedSoldiers = new Soldier*[commandedCapacity];
}

Officer::~Officer()
{
    delete[] commandedSoldiers;
}

int Officer::getCommandedCount() const
{
    return commandedCount;
}

Soldier* Officer::getCommandedSoldier(int index) const
{
    if (index < 0 || index >= commandedCount)
    {
        return nullptr;
    }
    return commandedSoldiers[index];
}

bool Officer::addCommandedSoldier(Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    for (int i = 0; i < commandedCount; ++i)
    {
        if (commandedSoldiers[i] == soldier)
        {
            return false;
        }
    }

    if (commandedCount == commandedCapacity)
    {
        const int newCap = commandedCapacity * 2;
        Soldier** larger = new Soldier*[newCap];
        for (int i = 0; i < commandedCount; ++i)
        {
            larger[i] = commandedSoldiers[i];
        }
        delete[] commandedSoldiers;
        commandedSoldiers = larger;
        commandedCapacity = newCap;
    }
    commandedSoldiers[commandedCount++] = soldier;
    return true;
}

bool Officer::removeCommandedSoldier(const Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    for (int i = 0; i < commandedCount; ++i)
    {
        if (commandedSoldiers[i] == soldier)
        {
            for (int j = i; j < commandedCount - 1; ++j)
            {
                commandedSoldiers[j] = commandedSoldiers[j + 1];
            }
            --commandedCount;
            return true;
        }
    }
    return false;
}

void Officer::printCommandedSoldiers() const
{
    std::cout << "    Commanded soldiers (" << commandedCount << "):" << std::endl;
    for (int i = 0; i < commandedCount; ++i)
    {
        std::cout << "      - " << *commandedSoldiers[i] << std::endl;
    }
}

void Officer::print() const
{
    Soldier::print();
    std::cout << "    -> Officer: commands " << commandedCount
              << " soldier(s)" << std::endl;
}
