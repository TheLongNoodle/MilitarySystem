#include "LogisticsMission.h"
#include "Vehicle.h"
#include "Equipment.h"
#include "Unit.h"
#include <iostream>
#include <algorithm>

LogisticsMission::LogisticsMission(const std::string& missionName, Unit& unit)
    : Mission(missionName, unit), assignedVehicle(nullptr)
{
}

Vehicle* LogisticsMission::getAssignedVehicle() const
{
    return assignedVehicle;
}

int LogisticsMission::getRequiredEquipmentCount() const
{
    return (int)requiredEquipment.size();
}

Equipment* LogisticsMission::getRequiredEquipment(int index) const
{
    if (index < 0 || index >= (int)requiredEquipment.size())
    {
        return nullptr;
    }
    return requiredEquipment[index];
}

bool LogisticsMission::setAssignedVehicle(Vehicle* v)
{
    assignedVehicle = v;
    return true;
}

bool LogisticsMission::addEquipment(Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    if (std::find(requiredEquipment.begin(), requiredEquipment.end(), equipment)
        != requiredEquipment.end())
    {
        return false;
    }
    requiredEquipment.push_back(equipment);
    return true;
}

bool LogisticsMission::removeEquipment(const Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    auto it = std::find(requiredEquipment.begin(), requiredEquipment.end(), equipment);
    if (it == requiredEquipment.end())
    {
        return false;
    }
    requiredEquipment.erase(it);
    return true;
}

void LogisticsMission::print() const
{
    std::cout << "  LogisticsMission [" << getMissionId() << "] '"
              << getMissionName() << "'"
              << " | status: " << Mission::statusName(getStatus())
              << " | unit: "   << getAssignedUnit().getUnitName()
              << " | vehicle: "
              << (assignedVehicle ? assignedVehicle->getVehicleNumber() : "(none)")
              << " | required equipment: " << requiredEquipment.size()
              << std::endl;
    for (const Equipment* equipment : requiredEquipment)
    {
        std::cout << "      - " << equipment->getName()
                  << " (S/N " << equipment->getSerialNumber() << ")"
                  << std::endl;
    }
}
