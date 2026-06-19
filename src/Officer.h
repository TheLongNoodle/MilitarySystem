#ifndef OFFICER_H
#define OFFICER_H

#include "Soldier.h"

class Officer : public Soldier {
private:
    Soldier** commandedSoldiers;
    int commandedCount;
    int commandedCapacity;

public:
    Officer(const char* name,
            const Date& birthDate,
            const char* role,
            eRank rank);
    ~Officer();

    Officer(const Officer& other) = delete;
    Officer& operator=(const Officer& other) = delete;

    int getCommandedCount() const;
    Soldier* getCommandedSoldier(int index) const;

    bool addCommandedSoldier(Soldier* soldier);
    bool removeCommandedSoldier(const Soldier* soldier);
    void printCommandedSoldiers() const;

    void print() const override;
};

#endif // OFFICER_H
