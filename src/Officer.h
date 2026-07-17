#ifndef OFFICER_H
#define OFFICER_H

#include "Soldier.h"
#include "LinkedList.h"

// Part 3: the dynamic Soldier** array was replaced with the generic
// LinkedList (requirement B), which removed the manual count/capacity
// bookkeeping and the destructor. Copying is already deleted in Soldier,
// so the redundant deleted copy operations were removed as well.
class Officer : public Soldier
{
private:
    LinkedList<Soldier*> commandedSoldiers;

public:
    Officer(const std::string& name, const Date& birthDate,
            const std::string& role, eRank rank);

    int getCommandedCount() const;

    bool addCommandedSoldier(Soldier* soldier);
    bool removeCommandedSoldier(Soldier* soldier);
    void printCommandedSoldiers() const;

    void print() const override;
};

#endif
