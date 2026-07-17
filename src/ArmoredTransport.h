#ifndef ARMORED_TRANSPORT_H
#define ARMORED_TRANSPORT_H

#include "Jeep.h"
#include "Truck.h"

class ArmoredTransport : public Jeep, public Truck
{
public:
    ArmoredTransport(const std::string& vehicleNumber, int maxPassengers,
                     double maxWeightKG);

    void print() const override;
};

#endif
