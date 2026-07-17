#ifndef OFFICER_H
#define OFFICER_H

#include "Soldier.h"
#include "LinkedList.h"

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
