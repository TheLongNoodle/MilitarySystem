#include "Officer.h"
#include "Soldier.h"
#include <iostream>

Officer::Officer(const std::string& name, const Date& birthDate,
                 const std::string& role, eRank rank)
    : Soldier(name, birthDate, role, rank)
{
}

int Officer::getCommandedCount() const
{
    int count = 0;
    for (LinkedList<Soldier*>::ConstIterator it = commandedSoldiers.begin();
         it != commandedSoldiers.end(); ++it)
    {
        ++count;
    }
    return count;
}

bool Officer::addCommandedSoldier(Soldier* soldier)
{
    if (!soldier || soldier == this)
    {
        return false;
    }
    for (LinkedList<Soldier*>::ConstIterator it = commandedSoldiers.begin();
         it != commandedSoldiers.end(); ++it)
    {
        if (*it == soldier)
        {
            return false;
        }
    }
    commandedSoldiers.addToEnd(soldier);
    return true;
}

bool Officer::removeCommandedSoldier(Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    return commandedSoldiers.remove(soldier);
}

void Officer::printCommandedSoldiers() const
{
    std::cout << "    Commanded soldiers (" << getCommandedCount() << "):" << std::endl;
    for (LinkedList<Soldier*>::ConstIterator it = commandedSoldiers.begin();
         it != commandedSoldiers.end(); ++it)
    {
        std::cout << "      - " << **it << std::endl;
    }
}

void Officer::print() const
{
    Soldier::print();
    std::cout << "    -> Officer: commands " << getCommandedCount()
              << " soldier(s)" << std::endl;
    if (!commandedSoldiers.isEmpty())
    {
        printCommandedSoldiers();
    }
}
