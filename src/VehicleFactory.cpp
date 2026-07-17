#include "VehicleFactory.h"
#include "Jeep.h"
#include "Truck.h"
#include "ArmoredTransport.h"
#include <stdexcept>

Vehicle* VehicleFactory::create(eVehicleType type,
                                const std::string& vehicleNumber,
                                int maxPassengers,
                                double maxWeightKG)
{
    switch (type)
    {
        case eVehicleType::JEEP:
            return new Jeep(vehicleNumber, maxPassengers);
        case eVehicleType::TRUCK:
            return new Truck(vehicleNumber, maxWeightKG);
        case eVehicleType::ARMORED_TRANSPORT:
            return new ArmoredTransport(vehicleNumber, maxPassengers, maxWeightKG);
    }
    throw std::invalid_argument("VehicleFactory: unknown vehicle type");
}
