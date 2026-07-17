#include "Jeep.h"
#include "Soldier.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

Jeep::Jeep(const std::string& vehicleNumber, int maxPassengers)
    : Vehicle(vehicleNumber)
{
    if (maxPassengers < 1)
    {
        throw std::invalid_argument("Jeep: maxPassengers must be >= 1");
    }
    this->maxPassengers = maxPassengers;
}

int Jeep::getMaxPassengers()  const
{
    return maxPassengers;
}
int Jeep::getPassengerCount() const
{
    return (int)passengers.size();
}

Soldier* Jeep::getPassenger(int index) const
{
    if (index < 0 || index >= (int)passengers.size())
    {
        return nullptr;
    }
    return passengers[index];
}

bool Jeep::setMaxPassengers(int n)
{
    if (n < (int)passengers.size() || n < 1)
    {
        return false;
    }
    maxPassengers = n;
    return true;
}

bool Jeep::loadPassenger(Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    if ((int)passengers.size() >= maxPassengers)
    {
        return false;
    }
    if (std::find(passengers.begin(), passengers.end(), soldier) != passengers.end())
    {
        return false;
    }
    passengers.push_back(soldier);
    return true;
}

bool Jeep::unloadPassenger(const Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    auto it = std::find(passengers.begin(), passengers.end(), soldier);
    if (it == passengers.end())
    {
        return false;
    }
    passengers.erase(it);
    return true;
}

void Jeep::print() const
{
    std::cout << "  Jeep [" << getVehicleNumber() << "]"
              << " passengers=" << passengers.size() << '/' << maxPassengers
              << ", " << (getAvailable() ? "available" : "unavailable")
              << (getNeedsMaintenance() ? " (needs maintenance)" : "")
              << std::endl;
}
