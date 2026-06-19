#ifndef LOGISTICS_MISSION_H
#define LOGISTICS_MISSION_H

#include "Mission.h"
class Equipment;

class Vehicle;

class LogisticsMission : public Mission {
private:
    Vehicle* assignedVehicle;

    Equipment** requiredEquipment;
    int requiredCount;
    int requiredCapacity;

public:
    LogisticsMission(const char* missionName, Unit* assignedUnit);
    ~LogisticsMission();

    LogisticsMission(const LogisticsMission& other) = delete;
    LogisticsMission& operator=(const LogisticsMission& other) = delete;

    Vehicle*   getAssignedVehicle() const;
    int        getRequiredEquipmentCount() const;
    Equipment* getRequiredEquipment(int index) const;

    bool setAssignedVehicle(Vehicle* vehicle);

    bool addEquipment(Equipment* equipment);
    bool removeEquipment(const Equipment* equipment);

    void print() const override;
};

#endif // LOGISTICS_MISSION_H
