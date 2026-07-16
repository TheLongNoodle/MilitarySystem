#include "ArmoredTransport.h"
#include <iostream>

ArmoredTransport::ArmoredTransport(const char* vehicleNumber, int maxPassengers, double maxWeightKG)
    : Vehicle(vehicleNumber), Jeep(vehicleNumber, maxPassengers), Truck(vehicleNumber, maxWeightKG)
{
}

void ArmoredTransport::print() const
{
    std::cout << "  ArmoredTransport [" << getVehicleNumber() << "]"
              << " passengers=" << getPassengerCount() << '/' << getMaxPassengers()
              << ", maxKG=" << getMaxWeightKG()
              << ", carrying=" << getLoadedCount() << " item(s)"
              << ", " << (getAvailable() ? "available" : "unavailable")
              << (getNeedsMaintenance() ? " (needs maintenance)" : "")
              << std::endl;
}
