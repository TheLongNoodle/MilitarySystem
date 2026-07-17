#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Soldier;

class Unit
{
private:
    static int s_nextUnitId;

    std::string unitName;
    int unitId;

    std::vector<Soldier*> soldiers;

public:
    Unit(const std::string& unitName);

    Unit(const Unit& other) = delete;
    Unit& operator=(const Unit& other) = delete;

    const std::string& getUnitName() const;
    int getUnitId() const;
    int getSoldierCount() const;
    Soldier* getSoldier(int index) const;

    bool setUnitName(const std::string& name);

    bool addSoldier(Soldier* soldier);
    bool removeSoldier(const Soldier* soldier);
    void printSoldiers() const;

    Unit& operator+=(Soldier* soldier);
};

#endif
