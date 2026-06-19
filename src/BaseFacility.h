#ifndef BASE_FACILITY_H
#define BASE_FACILITY_H

class Vehicle;
class Warehouse;

class BaseFacility {
private:
    Vehicle**   vehicles;
    int         vehicleCount;
    int         vehicleCapacity;

    Warehouse** warehouses;
    int         warehouseCount;
    int         warehouseCapacity;

public:
    BaseFacility();
    ~BaseFacility();

    BaseFacility(const BaseFacility& other) = delete;
    BaseFacility& operator=(const BaseFacility& other) = delete;

    int              getVehicleCount() const;
    const Vehicle*   getVehicle(int index) const;

    int              getWarehouseCount() const;
    const Warehouse* getWarehouse(int index) const;

    bool addVehicle(Vehicle* vehicle);
    bool addWarehouse(Warehouse* warehouse);

    bool addJeep(const char* vehicleNumber, int maxPassengers);
    bool addTruck(const char* vehicleNumber, double maxWeightKG);
    bool addArmoredTransport(const char* vehicleNumber,
                             int maxPassengers,
                             double maxWeightKG);

    const Vehicle*   findVehicle(const char* vehicleNumber) const;
    const Warehouse* findWarehouse(const char* name) const;

    void printVehicles() const;
    void printWarehouses() const;
    void print() const;
};

#endif // BASE_FACILITY_H
