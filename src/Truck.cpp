#include "Truck.h"
#include "Equipment.h"
#include <iostream>
#include <stdexcept>

Truck::Truck(const char* vehicleNumber, double maxWeightKG)
     : Vehicle(vehicleNumber), loadedEquipment(nullptr)
{
    loadedCount = 0;
    if (maxWeightKG <= 0.0)
    {
        throw std::invalid_argument("Truck: maxWeightKG must be positive");
    }
    this->maxWeightKG = maxWeightKG;
    loadedCapacity = 8;
    loadedEquipment = new Equipment*[loadedCapacity];
}

Truck::~Truck()
{
    delete[] loadedEquipment;
}

int Truck::getLoadedCount() const
{
    return loadedCount;
}

double Truck::getMaxWeightKG() const
{
    return maxWeightKG;
}

Equipment* Truck::getLoadedEquipment(int index) const
{
    if (index < 0 || index >= loadedCount)
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
    for (int i = 0; i < loadedCount; ++i)
    {
        if (loadedEquipment[i] == equipment)
        {
            return false;
        }
    }

    if (loadedCount == loadedCapacity)
    {
        const int newCap = loadedCapacity * 2;
        Equipment** larger = new Equipment*[newCap];
        for (int i = 0; i < loadedCount; ++i)
        {
            larger[i] = loadedEquipment[i];
        }
        delete[] loadedEquipment;
        loadedEquipment = larger;
        loadedCapacity = newCap;
    }
    loadedEquipment[loadedCount++] = equipment;
    return true;
}

bool Truck::unloadEquipment(const Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    for (int i = 0; i < loadedCount; ++i)
    {
        if (loadedEquipment[i] == equipment)
        {
            for (int j = i; j < loadedCount - 1; ++j)
            {
                loadedEquipment[j] = loadedEquipment[j + 1];
            }
            --loadedCount;
            return true;
        }
    }
    return false;
}

void Truck::print() const
{
    std::cout << "  Truck [" << getVehicleNumber() << "]"
              << " maxKG=" << maxWeightKG
              << ", carrying=" << loadedCount << " item(s)"
              << ", " << (getAvailable() ? "available" : "unavailable")
              << (getNeedsMaintenance() ? " (needs maintenance)" : "")
              << std::endl;
}
