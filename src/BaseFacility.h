#ifndef BASE_FACILITY_H
#define BASE_FACILITY_H

#include "VehicleFactory.h"
#include <string>
#include <vector>

class Vehicle;
class Warehouse;

// Part 3: the vehicle/warehouse arrays became std::vector. The destructor
// and the deleted copy operations REMAIN: the facility owns the Vehicle and
// Warehouse objects behind its pointers. The three per-type add methods
// (addJeep/addTruck/addArmoredTransport) were replaced by a single
// addVehicle that delegates creation to VehicleFactory.
class BaseFacility
{
private:
    std::vector<Vehicle*> vehicles;
    std::vector<Warehouse*> warehouses;

public:
    BaseFacility() = default;
    ~BaseFacility();

    BaseFacility(const BaseFacility& other) = delete;
    BaseFacility& operator=(const BaseFacility& other) = delete;

    int getVehicleCount() const;
    const Vehicle* getVehicle(int index) const;

    int getWarehouseCount() const;
    const Warehouse* getWarehouse(int index) const;

    bool addVehicle(Vehicle* vehicle);
    bool addWarehouse(Warehouse* warehouse);

    bool addVehicle(VehicleFactory::eVehicleType type,
                    const std::string& vehicleNumber,
                    int maxPassengers,
                    double maxWeightKG);

    const Vehicle* findVehicle(const std::string& vehicleNumber) const;
    const Warehouse* findWarehouse(const std::string& name) const;

    void printVehicles() const;
    void printWarehouses() const;
    void print() const;
};

#endif
