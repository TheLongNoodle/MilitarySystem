#ifndef REPORT_H
#define REPORT_H

class Report {
private:
    int soldierCount;
    int unitCount;
    int vehicleCount;
    int equipmentCount;
    int activeMissionCount;

public:
    Report(int soldierCount,
           int unitCount,
           int vehicleCount,
           int equipmentCount,
           int activeMissionCount);

    int getSoldierCount() const;
    int getUnitCount() const;
    int getVehicleCount() const;
    int getEquipmentCount() const;
    int getActiveMissionCount() const;

    void print() const;
};

#endif // REPORT_H
