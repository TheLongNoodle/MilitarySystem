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
#include "MissionObserver.h"
#include "Report.h"
#include <iostream>

MilitarySystem& MilitarySystem::getInstance()
{
    // Meyers singleton: constructed on first use, destroyed automatically
    // at program exit, no dynamic allocation needed.
    static MilitarySystem instance;
    return instance;
}

MilitarySystem::MilitarySystem() : missionObserver(nullptr)
{
}

MilitarySystem::~MilitarySystem()
{
    for (Mission* mission : missions)
    {
        delete mission;
    }
    for (Unit* unit : units)
    {
        delete unit;
    }
    for (Soldier* soldier : soldiers)
    {
        delete soldier;
    }
}

void MilitarySystem::setMissionObserver(MissionObserver* observer)
{
    missionObserver = observer;
}

bool MilitarySystem::isValidPersonInput(const std::string& name,
                                        const Date& birthDate,
                                        const std::string& role)
{
    return !name.empty() && !role.empty() && birthDate.isValid();
}

bool MilitarySystem::addSoldier(const std::string& name, const Date& birthDate,
                                const std::string& role, Soldier::eRank rank)
{
    if (!isValidPersonInput(name, birthDate, role))
    {
        return false;
    }
    soldiers.push_back(new Soldier(name, birthDate, role, rank));
    return true;
}

bool MilitarySystem::addOfficer(const std::string& name, const Date& birthDate,
                                const std::string& role, Soldier::eRank rank)
{
    if (!isValidPersonInput(name, birthDate, role))
    {
        return false;
    }
    soldiers.push_back(new Officer(name, birthDate, role, rank));
    return true;
}

Soldier* MilitarySystem::findSoldierMutable(int personalNumber)
{
    for (Soldier* soldier : soldiers)
    {
        if (soldier->getPersonalNumber() == personalNumber)
        {
            return soldier;
        }
    }
    return nullptr;
}

const Soldier* MilitarySystem::findSoldier(int personalNumber) const
{
    for (const Soldier* soldier : soldiers)
    {
        if (soldier->getPersonalNumber() == personalNumber)
        {
            return soldier;
        }
    }
    return nullptr;
}

bool MilitarySystem::addUnit(const std::string& unitName)
{
    if (unitName.empty())
    {
        return false;
    }
    units.push_back(new Unit(unitName));
    return true;
}

Unit* MilitarySystem::findUnitMutable(int unitId)
{
    for (Unit* unit : units)
    {
        if (unit->getUnitId() == unitId)
        {
            return unit;
        }
    }
    return nullptr;
}

const Unit* MilitarySystem::findUnit(int unitId) const
{
    for (const Unit* unit : units)
    {
        if (unit->getUnitId() == unitId)
        {
            return unit;
        }
    }
    return nullptr;
}

bool MilitarySystem::assignSoldierToUnit(int personalNumber, int unitId)
{
    Soldier* soldier = findSoldierMutable(personalNumber);
    if (!soldier)
    {
        return false;
    }
    Unit* unit = findUnitMutable(unitId);
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
    Soldier* soldier = findSoldierMutable(personalNumber);
    if (!soldier)
    {
        return false;
    }
    Unit* newUnit = findUnitMutable(newUnitId);
    if (!newUnit)
    {
        return false;
    }

    Unit* oldUnit = soldier->getUnit();
    if (oldUnit == newUnit)
    {
        return false;
    }
    if (oldUnit)
    {
        oldUnit->removeSoldier(soldier);
    }

    if (!newUnit->addSoldier(soldier))
    {
        if (oldUnit)
        {
            oldUnit->addSoldier(soldier);
        }
        return false;
    }
    soldier->setUnit(newUnit);
    return true;
}

bool MilitarySystem::assignSoldierToOfficer(int officerPersonalNumber,
                                            int soldierPersonalNumber)
{
    Officer* officer = dynamic_cast<Officer*>(findSoldierMutable(officerPersonalNumber));
    if (!officer)
    {
        return false;
    }
    Soldier* soldier = findSoldierMutable(soldierPersonalNumber);
    if (!soldier)
    {
        return false;
    }
    return officer->addCommandedSoldier(soldier);
}

bool MilitarySystem::addWarehouse(const std::string& name)
{
    if (name.empty())
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

const Warehouse* MilitarySystem::findWarehouse(const std::string& name) const
{
    return base.findWarehouse(name);
}

Warehouse* MilitarySystem::findWarehouseMutable(const std::string& name)
{
    for (int i = 0; i < base.getWarehouseCount(); ++i)
    {
        const Warehouse* warehouse = base.getWarehouse(i);
        if (warehouse->getName() == name)
        {
            // The facility getter is const-only; the system owns the base,
            // so editing the found warehouse is legitimate here.
            return const_cast<Warehouse*>(warehouse);
        }
    }
    return nullptr;
}

bool MilitarySystem::warehouseExists(const std::string& name) const
{
    return base.findWarehouse(name) != nullptr;
}

bool MilitarySystem::addEquipment(const std::string& warehouseName,
                                  const std::string& equipmentName,
                                  const std::string& serialNumber, int quantity,
                                  Equipment::eEquipmentStatus status)
{
    Warehouse* w = findWarehouseMutable(warehouseName);
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

bool MilitarySystem::addVehicle(VehicleFactory::eVehicleType type,
                                const std::string& vehicleNumber,
                                int maxPassengers, double maxWeightKG)
{
    return base.addVehicle(type, vehicleNumber, maxPassengers, maxWeightKG);
}

void MilitarySystem::printAllVehicles()   const
{
    base.printVehicles();
}

void MilitarySystem::printAllWarehouses() const
{
    base.printWarehouses();
}

Vehicle* MilitarySystem::findVehicle(const std::string& vehicleNumber) const
{
    // The facility getter is const-only; the system owns the base, so
    // handing a mutable vehicle to callers (driver/maintenance updates)
    // is legitimate here.
    return const_cast<Vehicle*>(base.findVehicle(vehicleNumber));
}

bool MilitarySystem::setVehicleDriver(const std::string& vehicleNumber, int personalNumber)
{
    Vehicle* v = findVehicle(vehicleNumber);
    if (!v)
    {
        return false;
    }
    Soldier* s = findSoldierMutable(personalNumber);
    if (!s)
    {
        return false;
    }
    return v->setDriver(s);
}

bool MilitarySystem::storeMission(Mission* mission)
{
    if (missionObserver)
    {
        mission->attach(missionObserver);
    }
    missions.push_back(mission);
    return true;
}

bool MilitarySystem::addTrainingMission(const std::string& missionName, int unitId,
                                        TrainingMission::eTrainingType trainingType,
                                        TrainingMission::eDifficultyLevel difficultyLevel)
{
    if (missionName.empty())
    {
        return false;
    }
    Unit* unit = findUnitMutable(unitId);
    if (!unit)
    {
        return false;
    }
    return storeMission(new TrainingMission(missionName, *unit,
                                            trainingType, difficultyLevel));
}

int MilitarySystem::addLogisticsMission(const std::string& missionName, int unitId)
{
    if (missionName.empty())
    {
        return -1;
    }
    Unit* unit = findUnitMutable(unitId);
    if (!unit)
    {
        return -1;
    }
    LogisticsMission* m = new LogisticsMission(missionName, *unit);
    storeMission(m);
    return m->getMissionId();
}

Mission* MilitarySystem::findMission(int missionId) const
{
    for (Mission* mission : missions)
    {
        if (mission->getMissionId() == missionId)
        {
            return mission;
        }
    }
    return nullptr;
}

bool MilitarySystem::setMissionVehicle(int missionId, const std::string& vehicleNumber)
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

bool MilitarySystem::addMissionEquipment(int missionId, const std::string& warehouseName,
                                         const std::string& equipmentName)
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

    Warehouse* w = findWarehouseMutable(warehouseName);
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
    return (int)units.size();
}

int MilitarySystem::getMissionsCount() const
{
    return (int)missions.size();
}

void MilitarySystem::printAllUnits() const
{
    std::cout << "--- Units (" << units.size() << ") ---" << std::endl;
    for (const Unit* unit : units)
    {
        unit->printSoldiers();
    }
}

void MilitarySystem::printAllMissions() const
{
    std::cout << "--- Missions (" << missions.size() << ") ---" << std::endl;
    for (const Mission* mission : missions)
    {
        mission->print();
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
    for (const Mission* mission : missions)
    {
        if (mission->getStatus() != Mission::eMissionStatus::COMPLETED)
        {
            ++activeMissions;
        }
    }
    return Report((int)soldiers.size(), (int)units.size(), base.getVehicleCount(),
                  equipmentCount, activeMissions);
}

void MilitarySystem::printAllData() const
{
    std::cout << "===== Military Base Snapshot =====" << std::endl;
    std::cout << "--- Personnel ("  << soldiers.size() << ") ---" << std::endl;
    for (const Soldier* soldier : soldiers)
    {
        soldier->print();
    }
    printAllUnits();
    printAllVehicles();
    printAllWarehouses();
    printAllMissions();
    std::cout << "==================================" << std::endl;
}
