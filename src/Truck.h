#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"
#include <vector>

class Equipment;

class Truck : virtual public Vehicle
{
private:
    std::vector<Equipment*> loadedEquipment;

    double maxWeightKG;

public:
    Truck(const std::string& vehicleNumber, double maxWeightKG);

    int getLoadedCount() const;
    Equipment* getLoadedEquipment(int index) const;
    double getMaxWeightKG() const;

    bool setMaxWeightKG(double maxWeightKG);

    bool loadEquipment(Equipment* equipment);
    bool unloadEquipment(const Equipment* equipment);

    void print() const override;
};

#endif
