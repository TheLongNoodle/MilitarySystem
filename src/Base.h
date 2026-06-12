#ifndef BASE_H
#define BASE_H

class Unit;
class Vehicle;
class Warehouse;

class Base {
private:
    Unit**      units;
    int         unitCount;
    int         unitCapacity;

    Vehicle**   vehicles;
    int         vehicleCount;
    int         vehicleCapacity;

    Warehouse** warehouses;
    int         warehouseCount;
    int         warehouseCapacity;

public:
    Base();
    ~Base();

    Base(const Base& other) = delete;
    Base& operator=(const Base& other) = delete;

    int        getUnitCount() const;
    Unit*      getUnit(int index) const;

    int        getVehicleCount() const;
    Vehicle*   getVehicle(int index) const;

    int        getWarehouseCount() const;
    Warehouse* getWarehouse(int index) const;

    bool addUnit(Unit* unit);
    bool addVehicle(Vehicle* vehicle);
    bool addWarehouse(Warehouse* warehouse);

    Unit*      findUnit(int unitId) const;
    Vehicle*   findVehicle(const char* vehicleNumber) const;
    Warehouse* findWarehouse(const char* name) const;

    void print() const;
};

#endif // BASE_H
