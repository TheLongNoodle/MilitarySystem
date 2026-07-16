#include "LogisticsMission.h"
#include "Vehicle.h"
#include "Equipment.h"
#include "Unit.h"
#include <iostream>

static const char* logMissionStatusName(Mission::eMissionStatus s)
{
    switch (s)
    {
        case Mission::eMissionStatus::NOT_STARTED: 
            return "NOT_STARTED";
        case Mission::eMissionStatus::IN_PROGRESS:
            return "IN_PROGRESS";
        case Mission::eMissionStatus::COMPLETED:
            return "COMPLETED";
    }
    return "?";
}

LogisticsMission::LogisticsMission(const char* missionName, Unit& unit)
    : Mission(missionName, unit), assignedVehicle(nullptr), requiredEquipment(nullptr)
{
    requiredCount = 0;
    requiredCapacity = 8;
    requiredEquipment = new Equipment*[requiredCapacity];
}

LogisticsMission::~LogisticsMission()
{
    delete[] requiredEquipment;
}

Vehicle* LogisticsMission::getAssignedVehicle() const
{
    return assignedVehicle;
}

int LogisticsMission::getRequiredEquipmentCount() const
{
    return requiredCount;
}

Equipment* LogisticsMission::getRequiredEquipment(int index) const
{
    if (index < 0 || index >= requiredCount)
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
    for (int i = 0; i < requiredCount; ++i)
    {
        if (requiredEquipment[i] == equipment)
        {
            return false;
        }
    }

    if (requiredCount == requiredCapacity)
    {
        const int newCap = requiredCapacity * 2;
        Equipment** larger = new Equipment*[newCap];
        for (int i = 0; i < requiredCount; ++i)
        {
            larger[i] = requiredEquipment[i];
        }
        delete[] requiredEquipment;
        requiredEquipment = larger;
        requiredCapacity = newCap;
    }
    requiredEquipment[requiredCount++] = equipment;
    return true;
}

bool LogisticsMission::removeEquipment(const Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    for (int i = 0; i < requiredCount; ++i)
    {
        if (requiredEquipment[i] == equipment)
        {
            for (int j = i; j < requiredCount - 1; ++j)
            {
                requiredEquipment[j] = requiredEquipment[j + 1];
            }
            --requiredCount;
            return true;
        }
    }
    return false;
}

void LogisticsMission::print() const
{
    std::cout << "  LogisticsMission [" << getMissionId() << "] '"
              << getMissionName() << "'"
              << " | status: " << logMissionStatusName(getStatus())
              << " | unit: "   << getAssignedUnit().getUnitName()
              << " | vehicle: "
              << (assignedVehicle ? assignedVehicle->getVehicleNumber() : "(none)")
              << " | required equipment: " << requiredCount
              << std::endl;
    for (int i = 0; i < requiredCount; ++i)
    {
        std::cout << "      - " << requiredEquipment[i]->getName()
                  << " (S/N " << requiredEquipment[i]->getSerialNumber() << ")"
                  << std::endl;
    }
}
