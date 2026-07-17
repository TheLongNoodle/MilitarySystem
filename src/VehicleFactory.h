#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include <string>

class Vehicle;

// DESIGN PATTERN: FACTORY
class VehicleFactory
{
public:
    enum class eVehicleType
    {
        JEEP,
        TRUCK,
        ARMORED_TRANSPORT
    };

    static Vehicle* create(eVehicleType type,
                           const std::string& vehicleNumber,
                           int maxPassengers,
                           double maxWeightKG);

private:
    VehicleFactory() = delete;
};

#endif
