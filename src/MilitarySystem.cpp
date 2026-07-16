#include "MilitarySystem.h"
#include "Date.h"
#include "Soldier.h"
#include "Officer.h"
#include "Unit.h"
#include "Vehicle.h"
#include "Warehouse.h"
#include "Equipment.h"
#include "Mission.h"
#include "TrainingMission.h"
#include "LogisticsMission.h"
#include "Report.h"
#include <iostream>

MilitarySystem::MilitarySystem() : soldiers(nullptr), units(nullptr), missions(nullptr), base()
{
    soldiersCount = 0;
    soldiersCapacity = 16;
    unitsCount = 0;
    unitsCapacity = 8;
    missionsCount = 0;
    missionsCapacity = 8;

    soldiers = new Soldier*[soldiersCapacity];
    try
    {
        units = new Unit*[unitsCapacity];
        try
        {
            missions = new Mission*[missionsCapacity];
        }
        catch (...)
        {
            delete[] units;
            throw;
        }
    }
    catch (...)
    {
        delete[] soldiers;
        throw;
    }
}

MilitarySystem::~MilitarySystem()
{
    for (int i = 0; i < missionsCount; ++i)
    {
        delete missions[i];
    }
    delete[] missions;

    for (int i = 0; i < unitsCount; ++i)
    {
        delete units[i];
    }
    delete[] units;

    for (int i = 0; i < soldiersCount; ++i)
    {
        delete soldiers[i];
    }
    delete[] soldiers;
}

bool MilitarySystem::addSoldier(const char* name, const Date& birthDate,
                                const char* role, Soldier::eRank rank)
{
    if (!name || name[0] == '\0')
    {
        return false;
    }
    if (!role || role[0] == '\0')
    {
        return false;
    }
    if (!birthDate.isValid())
    {
        return false;
    }

    Soldier* s = new Soldier(name, birthDate, role, rank);
    if (soldiersCount == soldiersCapacity)
    {
        const int newCap = soldiersCapacity * 2;
        Soldier** larger = new Soldier*[newCap];
        for (int i = 0; i < soldiersCount; ++i)
        {
            larger[i] = soldiers[i];
        }
        delete[] soldiers;
        soldiers = larger;
        soldiersCapacity = newCap;
    }
    soldiers[soldiersCount++] = s;
    return true;
}

bool MilitarySystem::addOfficer(const char* name, const Date& birthDate,
                                const char* role, Soldier::eRank rank)
{
    if (!name || name[0] == '\0')
    {
        return false;
    }
    if (!role || role[0] == '\0')
    {
        return false;
    }
    if (!birthDate.isValid())
    {
        return false;
    }

    Officer* o = new Officer(name, birthDate, role, rank);
    if (soldiersCount == soldiersCapacity)
    {
        const int newCap = soldiersCapacity * 2;
        Soldier** larger = new Soldier*[newCap];
        for (int i = 0; i < soldiersCount; ++i)
        {
            larger[i] = soldiers[i];
        }
        delete[] soldiers;
        soldiers = larger;
        soldiersCapacity = newCap;
    }
    soldiers[soldiersCount++] = o;
    return true;
}

const Soldier* MilitarySystem::findSoldier(int personalNumber) const
{
    for (int i = 0; i < soldiersCount; ++i)
    {
        if (soldiers[i]->getPersonalNumber() == personalNumber)
        {
            return soldiers[i];
        }
    }
    return nullptr;
}

bool MilitarySystem::addUnit(const char* unitName)
{
    if (!unitName || unitName[0] == '\0')
    {
        return false;
    }

    Unit* u = new Unit(unitName);
    if (unitsCount == unitsCapacity)
    {
        const int newCap = unitsCapacity * 2;
        Unit** larger = new Unit*[newCap];
        for (int i = 0; i < unitsCount; ++i)
        {
            larger[i] = units[i];
        }
        delete[] units;
        units = larger;
        unitsCapacity = newCap;
    }
    units[unitsCount++] = u;
    return true;
}

const Unit* MilitarySystem::findUnit(int unitId) const
{
    for (int i = 0; i < unitsCount; ++i)
    {
        if (units[i]->getUnitId() == unitId)
        {
            return units[i];
        }
    }
    return nullptr;
}

bool MilitarySystem::assignSoldierToUnit(int personalNumber, int unitId)
{
    Soldier* soldier = const_cast<Soldier*>(findSoldier(personalNumber));
    if (!soldier)
    {
        return false;
    }
    Unit* unit = const_cast<Unit*>(findUnit(unitId));
    if (!unit)
    {
        return false;
    }
    if (soldier->getUnit() != nullptr)
    {
        return false;
    }

    if (!unit->addSoldier(soldier))
    {
        return false;
    }
    soldier->setUnit(unit);

    return true;
}

bool MilitarySystem::transferSoldier(int personalNumber, int newUnitId)
{
    Soldier* soldier = const_cast<Soldier*>(findSoldier(personalNumber));
    if (!soldier)
    {
        return false;
    }
    Unit* newUnit = const_cast<Unit*>(findUnit(newUnitId));
    if (!newUnit)
    {
        return false;
    }

    Unit* oldUnit = soldier->getUnit();
    if (oldUnit == newUnit)
    {
        return false;
    }
    if (oldUnit) oldUnit->removeSoldier(soldier);

    if (!newUnit->addSoldier(soldier))
    {
        if (oldUnit) oldUnit->addSoldier(soldier);
        {
            return false;
        }
    }
    soldier->setUnit(newUnit);
    return true;
}

bool MilitarySystem::addWarehouse(const char* name)
{
    if (!name || name[0] == '\0')
    {
        return false;
    }
    if (warehouseExists(name))
    {
        return false;
    }
    Warehouse* w = new Warehouse(name);
    if (!base.addWarehouse(w))
    {
        delete w;
        return false;
    }
    return true;
}

const Warehouse* MilitarySystem::findWarehouse(const char* name) const
{
    return base.findWarehouse(name);
}

bool MilitarySystem::warehouseExists(const char* name) const
{
    return base.findWarehouse(name) != nullptr;
}

bool MilitarySystem::addEquipment(const char* warehouseName, const char* equipmentName,
                                  const char* serialNumber, int quantity,
                                  Equipment::eEquipmentStatus status)
{
    Warehouse* w = const_cast<Warehouse*>(base.findWarehouse(warehouseName));
    if (!w)
    {
        return false;
    }

    Equipment* eq = new Equipment(equipmentName, serialNumber, quantity, status);
    if (!w->addEquipment(eq))
    {
        delete eq;
        return false;
    }
    return true;
}

bool MilitarySystem::addJeep(const char* vehicleNumber, int maxPassengers)
{
    return base.addJeep(vehicleNumber, maxPassengers);
}

bool MilitarySystem::addTruck(const char* vehicleNumber, double maxWeightKG)
{
    return base.addTruck(vehicleNumber, maxWeightKG);
}

bool MilitarySystem::addArmoredTransport(const char* vehicleNumber,
                                         int maxPassengers, double maxWeightKG)
{
    return base.addArmoredTransport(vehicleNumber, maxPassengers, maxWeightKG);
}

void MilitarySystem::printAllVehicles()   const
{
    base.printVehicles();
}

void MilitarySystem::printAllWarehouses() const
{
    base.printWarehouses();
}

Vehicle* MilitarySystem::findVehicle(const char* vehicleNumber) const
{
    return const_cast<Vehicle*>(base.findVehicle(vehicleNumber));
}

bool MilitarySystem::setVehicleDriver(const char* vehicleNumber, int personalNumber)
{
    Vehicle* v = findVehicle(vehicleNumber);
    if (!v)
    {
        return false;
    }
    Soldier* s = const_cast<Soldier*>(findSoldier(personalNumber));
    if (!s)
    {
        return false;
    }
    return v->setDriver(s);
}

bool MilitarySystem::addTrainingMission(const char* missionName, int unitId,
                                        TrainingMission::eTrainingType trainingType,
                                        TrainingMission::eDifficultyLevel difficultyLevel)
{
    if (!missionName || missionName[0] == '\0')
    {
        return false;
    }
    Unit* unit = const_cast<Unit*>(findUnit(unitId));
    if (!unit)
    {
        return false;
    }

    TrainingMission* m = new TrainingMission(missionName, *unit, trainingType, difficultyLevel);

    if (missionsCount == missionsCapacity)
    {
        const int newCap = missionsCapacity * 2;
        Mission** larger = new Mission*[newCap];
        for (int i = 0; i < missionsCount; ++i)
        {
            larger[i] = missions[i];
        }
        delete[] missions;
        missions = larger;
        missionsCapacity = newCap;
    }
    missions[missionsCount++] = m;
    return true;
}

int MilitarySystem::addLogisticsMission(const char* missionName, int unitId)
{
    if (!missionName || missionName[0] == '\0')
    {
        return -1;
    }
    Unit* unit = const_cast<Unit*>(findUnit(unitId));
    if (!unit)
    {
        return -1;
    }

    LogisticsMission* m = new LogisticsMission(missionName, *unit);

    if (missionsCount == missionsCapacity)
    {
        const int newCap = missionsCapacity * 2;
        Mission** larger = new Mission*[newCap];
        for (int i = 0; i < missionsCount; ++i)
        {
            larger[i] = missions[i];
        }
        delete[] missions;
        missions = larger;
        missionsCapacity = newCap;
    }
    missions[missionsCount++] = m;
    return m->getMissionId();
}

Mission* MilitarySystem::findMission(int missionId) const
{
    for (int i = 0; i < missionsCount; ++i)
    {
        if (missions[i]->getMissionId() == missionId)
        {
            return missions[i];
        }
    }
    return nullptr;
}

bool MilitarySystem::setMissionVehicle(int missionId, const char* vehicleNumber)
{
    Mission* m = findMission(missionId);
    if (!m)
    {
        return false;
    }
    LogisticsMission* lm = dynamic_cast<LogisticsMission*>(m);
    if (!lm)
    {
        return false;
    }
    Vehicle* v = findVehicle(vehicleNumber);
    if (!v)
    {
        return false;
    }
    return lm->setAssignedVehicle(v);
}

bool MilitarySystem::addMissionEquipment(int missionId, const char* warehouseName,
                                         const char* equipmentName)
{
    Mission* m = findMission(missionId);
    if (!m)
    {
        return false;
    }
    LogisticsMission* lm = dynamic_cast<LogisticsMission*>(m);
    if (!lm)
    {
        return false;
    }

    Warehouse* w = const_cast<Warehouse*>(base.findWarehouse(warehouseName));
    if (!w)
    {
        return false;
    }
    Equipment* eq = w->searchEquipment(equipmentName);
    if (!eq)
    {
        return false;
    }
    return lm->addEquipment(eq);
}

BaseFacility& MilitarySystem::getBase()
{
    return base;
}

const BaseFacility& MilitarySystem::getBase() const
{
    return base;
}

int MilitarySystem::getUnitsCount() const
{
    return unitsCount;
}

int MilitarySystem::getMissionsCount() const
{
    return missionsCount;
}

void MilitarySystem::printAllUnits() const
{
    std::cout << "--- Units (" << unitsCount << ") ---" << std::endl;
    for (int i = 0; i < unitsCount; ++i)
    {
        units[i]->printSoldiers();
    }
}

void MilitarySystem::printAllMissions() const
{
    std::cout << "--- Missions (" << missionsCount << ") ---" << std::endl;
    for (int i = 0; i < missionsCount; ++i)
    {
        missions[i]->print();
    }
}

Report MilitarySystem::generateReport() const
{
    int equipmentCount = 0;
    for (int i = 0; i < base.getWarehouseCount(); ++i)
    {
        equipmentCount += base.getWarehouse(i)->getEquipmentCount();
    }
    int activeMissions = 0;
    for (int i = 0; i < missionsCount; ++i)
    {
        if (missions[i]->getStatus() != Mission::eMissionStatus::COMPLETED)
        {
            ++activeMissions;
        }
    }
    return Report(soldiersCount, unitsCount, base.getVehicleCount(),
                  equipmentCount, activeMissions);
}

void MilitarySystem::printAllData() const
{
    std::cout << "===== Military Base Snapshot =====" << std::endl;
    std::cout << "--- Personnel ("  << soldiersCount << ") ---" << std::endl;
    for (int i = 0; i < soldiersCount; ++i)
    {
        soldiers[i]->print();
    }
    printAllUnits();
    printAllVehicles();
    printAllWarehouses();
    printAllMissions();
    std::cout << "==================================" << std::endl;
}
