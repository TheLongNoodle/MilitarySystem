#include "Truck.h"
#include "Equipment.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

Truck::Truck(const std::string& vehicleNumber, double maxWeightKG)
     : Vehicle(vehicleNumber)
{
    if (maxWeightKG <= 0.0)
    {
        throw std::invalid_argument("Truck: maxWeightKG must be positive");
    }
    this->maxWeightKG = maxWeightKG;
}

int Truck::getLoadedCount() const
{
    return (int)loadedEquipment.size();
}

double Truck::getMaxWeightKG() const
{
    return maxWeightKG;
}

Equipment* Truck::getLoadedEquipment(int index) const
{
    if (index < 0 || index >= (int)loadedEquipment.size())
    {
        return nullptr;
    }
    return loadedEquipment[index];
}

bool Truck::setMaxWeightKG(double w)
{
    if (w <= 0.0)
    {
        return false;
    }
    maxWeightKG = w;
    return true;
}

bool Truck::loadEquipment(Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    if (std::find(loadedEquipment.begin(), loadedEquipment.end(), equipment)
        != loadedEquipment.end())
    {
        return false;
    }
    loadedEquipment.push_back(equipment);
    return true;
}

bool Truck::unloadEquipment(const Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    auto it = std::find(loadedEquipment.begin(), loadedEquipment.end(), equipment);
    if (it == loadedEquipment.end())
    {
        return false;
    }
    loadedEquipment.erase(it);
    return true;
}

void Truck::print() const
{
    std::cout << "  Truck [" << getVehicleNumber() << "]"
              << " maxKG=" << maxWeightKG
              << ", carrying=" << loadedEquipment.size() << " item(s)"
              << ", " << (getAvailable() ? "available" : "unavailable")
              << (getNeedsMaintenance() ? " (needs maintenance)" : "")
              << std::endl;
}
