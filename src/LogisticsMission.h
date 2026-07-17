#ifndef LOGISTICS_MISSION_H
#define LOGISTICS_MISSION_H

#include "Mission.h"
#include <vector>

class Equipment;
class Unit;

class Vehicle;

// Part 3: the required-equipment array became a std::vector of non-owning
// pointers, so the destructor and count/capacity fields were removed. The
// deleted copy operations were removed as redundant - Mission already
// forbids copying.
class LogisticsMission : public Mission
{
private:
    Vehicle* assignedVehicle;

    std::vector<Equipment*> requiredEquipment;

public:
    LogisticsMission(const std::string& missionName, Unit& assignedUnit);

    Vehicle* getAssignedVehicle() const;
    int getRequiredEquipmentCount() const;
    Equipment* getRequiredEquipment(int index) const;

    bool setAssignedVehicle(Vehicle* vehicle);

    bool addEquipment(Equipment* equipment);
    bool removeEquipment(const Equipment* equipment);

    void print() const override;
};

#endif
