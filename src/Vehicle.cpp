#include "Vehicle.h"
#include "Soldier.h"
#include <stdexcept>

Vehicle::Vehicle(const std::string& vehicleNumber)
    : vehicleNumber(vehicleNumber), driver(nullptr)
{
    available = true;
    needsMaintenance = false;

    if (vehicleNumber.empty())
    {
        throw std::invalid_argument("Vehicle: vehicle number must not be empty");
    }
}

bool Vehicle::setVehicleNumber(const std::string& vn)
{
    if (vn.empty())
    {
        return false;
    }
    vehicleNumber = vn;
    return true;
}

const std::string& Vehicle::getVehicleNumber() const
{
    return vehicleNumber;
}

bool Vehicle::getAvailable() const
{
    return available;
}

bool Vehicle::getNeedsMaintenance() const
{
    return needsMaintenance;
}

Soldier* Vehicle::getDriver() const
{
    return driver;
}

bool Vehicle::setAvailability(bool status)
{
    available = status;
    return true;
}

bool Vehicle::sendToMaintenance()
{
    needsMaintenance = true;
    available = false;
    return true;
}

bool Vehicle::setDriver(Soldier* d)
{
    driver = d;
    return true;
}
