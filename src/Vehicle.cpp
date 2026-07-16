#include "Vehicle.h"
#include "Soldier.h"
#include "Utils.h"
#include <stdexcept>

Vehicle::Vehicle(const char* vehicleNumber) : vehicleNumber(nullptr), driver(nullptr)
{
    available = true;
    needsMaintenance = false;

    if (!vehicleNumber || vehicleNumber[0] == '\0')
    {
        throw std::invalid_argument("Vehicle: vehicle number must not be empty");
    }
    this->vehicleNumber = utils::dupString(vehicleNumber);
}

Vehicle::~Vehicle()
{
    delete[] this->vehicleNumber;
}

bool Vehicle::setVehicleNumber(const char* vn)
{
    if (!vn || vn[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(vn);
    delete[] vehicleNumber;
    vehicleNumber = tmp;
    return true;
}

const char* Vehicle::getVehicleNumber() const
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
