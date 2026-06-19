#ifndef VEHICLE_H
#define VEHICLE_H

class Soldier;

class Vehicle {
private:
    char* vehicleNumber;
    bool  available;
    bool  needsMaintenance;

    Soldier* driver;

    bool setVehicleNumber(const char* vehicleNumber);

public:
    Vehicle(const char* vehicleNumber);
    virtual ~Vehicle();

    Vehicle(const Vehicle& other) = delete;
    Vehicle& operator=(const Vehicle& other) = delete;

    const char* getVehicleNumber() const;
    bool        getAvailable() const;
    bool        getNeedsMaintenance() const;
    Soldier*    getDriver() const;

    bool setAvailability(bool status);
    bool sendToMaintenance();
    bool setDriver(Soldier* driver);

    virtual void print() const = 0;
};

#endif // VEHICLE_H
