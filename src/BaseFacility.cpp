#include "BaseFacility.h"
#include "Vehicle.h"
#include "Warehouse.h"
#include "Jeep.h"
#include "Truck.h"
#include "ArmoredTransport.h"
#include "Equipment.h"
#include <iostream>
#include <cstring>

BaseFacility::BaseFacility() : vehicles(nullptr),  vehicleCount(0), vehicleCapacity(0),
                               warehouses(nullptr), warehouseCount(0), warehouseCapacity(0)
{
    vehicleCapacity = 8;
    vehicles = new Vehicle*[vehicleCapacity];
    try
    {
        warehouseCapacity = 4;
        warehouses = new Warehouse*[warehouseCapacity];
    }
    catch (...)
    {
        delete[] vehicles;
        throw;
    }
}

BaseFacility::~BaseFacility()
{
    for (int i = 0; i < vehicleCount; ++i)
    {
        delete vehicles[i];
    }
    delete[] vehicles;
    for (int i = 0; i < warehouseCount; ++i)
    {
        delete warehouses[i];
    }
    delete[] warehouses;
}

int BaseFacility::getVehicleCount()   const
{
    return vehicleCount;
}

int BaseFacility::getWarehouseCount() const
{
    return warehouseCount;
}

const Vehicle* BaseFacility::getVehicle(int index) const
{
    if (index < 0 || index >= vehicleCount)
    {
        return nullptr;
    }
    return vehicles[index];
}

const Warehouse* BaseFacility::getWarehouse(int index) const
{
    if (index < 0 || index >= warehouseCount)
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
    if (vehicleCount == vehicleCapacity)
    {
        const int newCap = vehicleCapacity * 2;
        Vehicle** larger = new Vehicle*[newCap];
        for (int i = 0; i < vehicleCount; ++i)
        {
            larger[i] = vehicles[i];
        }
        delete[] vehicles;
        vehicles = larger;
        vehicleCapacity = newCap;
    }
    vehicles[vehicleCount++] = vehicle;
    return true;
}

bool BaseFacility::addWarehouse(Warehouse* warehouse)
{
    if (!warehouse)
    {
        return false;
    }
    if (warehouseCount == warehouseCapacity)
    {
        const int newCap = warehouseCapacity * 2;
        Warehouse** larger = new Warehouse*[newCap];
        for (int i = 0; i < warehouseCount; ++i)
        {
            larger[i] = warehouses[i];
        }
        delete[] warehouses;
        warehouses = larger;
        warehouseCapacity = newCap;
    }
    warehouses[warehouseCount++] = warehouse;
    return true;
}

bool BaseFacility::addJeep(const char* vehicleNumber, int maxPassengers)
{
    if (findVehicle(vehicleNumber))
    {
        return false;
    }
    Vehicle* v = new Jeep(vehicleNumber, maxPassengers);
    if (!addVehicle(v))
    {
        delete v;
        return false;
    }
    return true;
}

bool BaseFacility::addTruck(const char* vehicleNumber, double maxWeightKG)
{
    if (findVehicle(vehicleNumber))
    {
        return false;
    }
    Vehicle* v = new Truck(vehicleNumber, maxWeightKG);
    if (!addVehicle(v))
    {
        delete v;
        return false;
    }
    return true;
}

bool BaseFacility::addArmoredTransport(const char* vehicleNumber, int maxPassengers,
                                       double maxWeightKG)
{
    if (findVehicle(vehicleNumber))
    {
        return false;
    }
    Vehicle* v = new ArmoredTransport(vehicleNumber, maxPassengers, maxWeightKG);
    if (!addVehicle(v))
    {
        delete v;
        return false;
    }
    return true;
}

const Vehicle* BaseFacility::findVehicle(const char* vehicleNumber) const
{
    if (!vehicleNumber)
    {
        return nullptr;
    }
    for (int i = 0; i < vehicleCount; ++i)
    {
        if (std::strcmp(vehicles[i]->getVehicleNumber(), vehicleNumber) == 0)
        {
            return vehicles[i];
        }
    }
    return nullptr;
}

const Warehouse* BaseFacility::findWarehouse(const char* name) const
{
    if (!name)
    {
        return nullptr;
    }
    for (int i = 0; i < warehouseCount; ++i)
    {
        if (std::strcmp(warehouses[i]->getName(), name) == 0)
        {
            return warehouses[i];
        }
    }
    return nullptr;
}

void BaseFacility::printVehicles() const
{
    std::cout << "--- Vehicles (" << vehicleCount << ") ---" << std::endl;
    for (int i = 0; i < vehicleCount; ++i)
    {
        vehicles[i]->print();
    }
}

void BaseFacility::printWarehouses() const
{
    std::cout << "--- Warehouses (" << warehouseCount << ") ---" << std::endl;
    for (int i = 0; i < warehouseCount; ++i)
    {
        warehouses[i]->printEquipment();
    }
}

void BaseFacility::print() const
{
    printVehicles();
    printWarehouses();
}
