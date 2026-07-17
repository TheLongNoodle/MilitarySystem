#ifndef LOGISTICS_MISSION_H
#define LOGISTICS_MISSION_H

#include "Mission.h"
#include <vector>

class Equipment;
class Unit;

class Vehicle;

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
