#include "Report.h"
#include <iostream>

Report::Report(int s, int u, int v, int e, int m) : soldierCount(s),
        unitCount(u), vehicleCount(v), equipmentCount(e), activeMissionCount(m)
{
}

int Report::getSoldierCount() const
{
    return soldierCount;
}

int Report::getUnitCount() const
{
    return unitCount;
}

int Report::getVehicleCount() const
{
    return vehicleCount;
}

int Report::getEquipmentCount() const
{
    return equipmentCount;
}

int Report::getActiveMissionCount() const
{
    return activeMissionCount;
}

void Report::print() const
{
    std::cout << "===== Base Report =====" << std::endl;
    std::cout << "  Soldiers (incl. officers): " << soldierCount << std::endl;
    std::cout << "  Units                    : " << unitCount << std::endl;
    std::cout << "  Vehicles                 : " << vehicleCount << std::endl;
    std::cout << "  Equipment items          : " << equipmentCount << std::endl;
    std::cout << "  Missions (not completed) : " << activeMissionCount << std::endl;
    std::cout << "=======================" << std::endl;
}
