#include "BaseFacility.h"
#include "Vehicle.h"
#include "Warehouse.h"
#include "Equipment.h"
#include <iostream>

BaseFacility::~BaseFacility()
{
    for (Vehicle* vehicle : vehicles)
    {
        delete vehicle;
    }
    for (Warehouse* warehouse : warehouses)
    {
        delete warehouse;
    }
}

int BaseFacility::getVehicleCount()   const
{
    return (int)vehicles.size();
}

int BaseFacility::getWarehouseCount() const
{
    return (int)warehouses.size();
}

const Vehicle* BaseFacility::getVehicle(int index) const
{
    if (index < 0 || index >= (int)vehicles.size())
    {
        return nullptr;
    }
    return vehicles[index];
}

const Warehouse* BaseFacility::getWarehouse(int index) const
{
    if (index < 0 || index >= (int)warehouses.size())
    {
        return nullptr;
    }
    return warehouses[index];
}

bool BaseFacility::addVehicle(Vehicle* vehicle)
{
    if (!vehicle)
    {
        return false;
    }
    vehicles.push_back(vehicle);
    return true;
}

bool BaseFacility::addWarehouse(Warehouse* warehouse)
{
    if (!warehouse)
    {
        return false;
    }
    warehouses.push_back(warehouse);
    return true;
}

bool BaseFacility::addVehicle(VehicleFactory::eVehicleType type,
                              const std::string& vehicleNumber,
                              int maxPassengers,
                              double maxWeightKG)
{
    if (findVehicle(vehicleNumber))
    {
        return false;
    }
    Vehicle* v = VehicleFactory::create(type, vehicleNumber, maxPassengers, maxWeightKG);
    vehicles.push_back(v);
    return true;
}

const Vehicle* BaseFacility::findVehicle(const std::string& vehicleNumber) const
{
    for (const Vehicle* vehicle : vehicles)
    {
        if (vehicle->getVehicleNumber() == vehicleNumber)
        {
            return vehicle;
        }
    }
    return nullptr;
}

const Warehouse* BaseFacility::findWarehouse(const std::string& name) const
{
    for (const Warehouse* warehouse : warehouses)
    {
        if (warehouse->getName() == name)
        {
            return warehouse;
        }
    }
    return nullptr;
}

void BaseFacility::printVehicles() const
{
    std::cout << "--- Vehicles (" << vehicles.size() << ") ---" << std::endl;
    for (const Vehicle* vehicle : vehicles)
    {
        vehicle->print();
    }
}

void BaseFacility::printWarehouses() const
{
    std::cout << "--- Warehouses (" << warehouses.size() << ") ---" << std::endl;
    for (const Warehouse* warehouse : warehouses)
    {
        warehouse->printEquipment();
    }
}

void BaseFacility::print() const
{
    printVehicles();
    printWarehouses();
}
