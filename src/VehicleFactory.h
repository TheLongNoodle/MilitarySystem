#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include <string>

class Vehicle;

// Factory design pattern (part 3, requirement G).
// Creation of concrete vehicle types is centralized here, so the rest of
// the system (BaseFacility, main) works only with the abstract Vehicle and
// never mentions Jeep/Truck/ArmoredTransport by name. Previously the same
// duplicate-check-then-new logic appeared three times in BaseFacility and
// three more times as delegation methods in MilitarySystem.
class VehicleFactory
{
public:
    enum class eVehicleType
    {
        JEEP,
        TRUCK,
        ARMORED_TRANSPORT
    };

    // Returns a heap-allocated vehicle; ownership passes to the caller.
    // Parameters that a type does not need are ignored (e.g. maxWeightKG
    // for a Jeep). Throws std::invalid_argument on invalid parameters,
    // like the vehicle constructors themselves.
    static Vehicle* create(eVehicleType type,
                           const std::string& vehicleNumber,
                           int maxPassengers,
                           double maxWeightKG);

private:
    VehicleFactory() = delete;   // static-only class, never instantiated
};

#endif
