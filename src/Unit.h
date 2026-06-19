#ifndef UNIT_H
#define UNIT_H

class Soldier;

class Unit {
private:
    static int s_nextUnitId;

    char* unitName;
    int   unitId;

    Soldier** soldiers;
    int count;
    int capacity;

public:
    Unit(const char* unitName);
    ~Unit();

    Unit(const Unit& other) = delete;
    Unit& operator=(const Unit& other) = delete;

    const char* getUnitName() const;
    int         getUnitId() const;
    int         getSoldierCount() const;
    Soldier*    getSoldier(int index) const;

    bool setUnitName(const char* name);

    bool addSoldier(Soldier* soldier);
    bool removeSoldier(const Soldier* soldier);
    void printSoldiers() const;
};

#endif // UNIT_H
