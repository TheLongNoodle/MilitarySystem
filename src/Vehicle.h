#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Soldier;

class Vehicle
{
private:
    std::string vehicleNumber;
    bool available;
    bool needsMaintenance;

    Soldier* driver;

    bool setVehicleNumber(const std::string& vehicleNumber);

public:
    Vehicle(const std::string& vehicleNumber);
    virtual ~Vehicle() = default;

    Vehicle(const Vehicle& other) = delete;
    Vehicle& operator=(const Vehicle& other) = delete;

    const std::string& getVehicleNumber() const;
    bool getAvailable() const;
    bool getNeedsMaintenance() const;
    Soldier* getDriver() const;

    bool setAvailability(bool status);
    bool sendToMaintenance();
    bool setDriver(Soldier* driver);

    virtual void print() const = 0;
};

#endif
