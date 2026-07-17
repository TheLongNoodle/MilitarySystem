#ifndef JEEP_H
#define JEEP_H

#include "Vehicle.h"
#include <vector>

class Soldier;

class Jeep : virtual public Vehicle
{
private:
    std::vector<Soldier*> passengers;

    int maxPassengers;

public:
    Jeep(const std::string& vehicleNumber, int maxPassengers);

    int getMaxPassengers() const;
    int getPassengerCount() const;
    Soldier* getPassenger(int index) const;

    bool setMaxPassengers(int maxPassengers);

    bool loadPassenger(Soldier* soldier);
    bool unloadPassenger(const Soldier* soldier);

    void print() const override;
};

#endif
