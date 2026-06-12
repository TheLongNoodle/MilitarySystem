#ifndef MILITARY_SYSTEM_H
#define MILITARY_SYSTEM_H

#include "BaseFacility.h"
#include "Soldier.h"
#include "Equipment.h"
#include "TrainingMission.h"
#include "Report.h"

class Date;
class Unit;
class Vehicle;
class Warehouse;
class Mission;

class MilitarySystem {
private:
    Soldier**   soldiers;
    int         soldiersCount;
    int         soldiersCapacity;

    Unit**      units;
    int         unitsCount;
    int         unitsCapacity;

    Mission**   missions;
    int         missionsCount;
    int         missionsCapacity;

    BaseFacility base;

public:
    MilitarySystem();
    ~MilitarySystem();

    MilitarySystem(const MilitarySystem& other) = delete;
    MilitarySystem& operator=(const MilitarySystem& other) = delete;

    bool addSoldier(const char* name,
                    const Date& birthDate,
                    const char* role,
                    Soldier::eRank rank);
    bool addOfficer(const char* name,
                    const Date& birthDate,
                    const char* role,
                    Soldier::eRank rank);
    const Soldier* findSoldier(int personalNumber) const;

    bool addUnit(const char* unitName);
    const Unit* findUnit(int unitId) const;
    bool assignSoldierToUnit(int personalNumber, int unitId);
    bool transferSoldier(int personalNumber, int newUnitId);

    bool addWarehouse(const char* name);
    const Warehouse* findWarehouse(const char* name) const;
    bool addEquipment(const char* warehouseName,
                      const char* equipmentName,
                      const char* serialNumber,
                      int quantity,
                      Equipment::eEquipmentStatus status);

    Vehicle* findVehicle(const char* vehicleNumber) const;
    bool setVehicleDriver(const char* vehicleNumber, int personalNumber);

    bool addTrainingMission(const char* missionName,
                            int unitId,
                            TrainingMission::eTrainingType trainingType,
                            TrainingMission::eDifficultyLevel difficultyLevel);
    int addLogisticsMission(const char* missionName, int unitId);
    Mission* findMission(int missionId) const;
    bool setMissionVehicle(int missionId, const char* vehicleNumber);
    bool addMissionEquipment(int missionId,
                             const char* warehouseName,
                             const char* equipmentName);

    BaseFacility&       getBase();
    const BaseFacility& getBase() const;

    void printAllUnits() const;
    void printAllMissions() const;
    int  getMissionsCount() const;
    Report generateReport() const;
    void   printAllData() const;
};

#endif // MILITARY_SYSTEM_H
