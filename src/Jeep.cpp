#include "Jeep.h"
#include "Soldier.h"
#include <iostream>
#include <stdexcept>

Jeep::Jeep(const char* vehicleNumber, int maxPassengers)
    : Vehicle(vehicleNumber), passengers(nullptr)
{
    passengerCount = 0;
    maxPassengers = 0;
    if (maxPassengers < 1)
    {
        throw std::invalid_argument("Jeep: maxPassengers must be >= 1");
    }
    this->maxPassengers = maxPassengers;
    passengers = new Soldier*[maxPassengers];
}

Jeep::~Jeep()
{
    delete[] passengers;
}

int Jeep::getMaxPassengers()  const
{
    return maxPassengers;
}
int Jeep::getPassengerCount() const
{
    return passengerCount;
}

Soldier* Jeep::getPassenger(int index) const
{
    if (index < 0 || index >= passengerCount)
    {
        return nullptr;
    }
    return passengers[index];
}

bool Jeep::setMaxPassengers(int n)
{
    if (n < passengerCount)
    {
        return false;
    }
    if (n < 1)
    {
        return false;
    }
    Soldier** larger = new Soldier*[n];
    for (int i = 0; i < passengerCount; ++i)
    {
        larger[i] = passengers[i];
    }
    delete[] passengers;
    passengers = larger;
    maxPassengers = n;
    return true;
}

bool Jeep::loadPassenger(Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    if (passengerCount >= maxPassengers)
    {
        return false;
    }
    for (int i = 0; i < passengerCount; ++i)
    {
        if (passengers[i] == soldier)
        {
            return false;
        }
    }
    passengers[passengerCount++] = soldier;
    return true;
}

bool Jeep::unloadPassenger(const Soldier* soldier)
{
    if (!soldier)
    {
        return false;
    }
    for (int i = 0; i < passengerCount; ++i)
    {
        if (passengers[i] == soldier)
        {
            for (int j = i; j < passengerCount - 1; ++j)
            {
                passengers[j] = passengers[j + 1];
            }
            --passengerCount;
            return true;
        }
    }
    return false;
}

void Jeep::print() const
{
    std::cout << "  Jeep [" << getVehicleNumber() << "]"
              << " passengers=" << passengerCount << '/' << maxPassengers
              << ", " << (getAvailable() ? "available" : "unavailable")
              << (getNeedsMaintenance() ? " (needs maintenance)" : "")
              << std::endl;
}
