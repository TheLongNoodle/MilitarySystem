#ifndef JEEP_H
#define JEEP_H

#include "Vehicle.h"

class Soldier;

class Jeep : virtual public Vehicle {
private:
    Soldier** passengers;
    int passengerCount;

    int maxPassengers;

public:
    Jeep(const char* vehicleNumber, int maxPassengers);
    ~Jeep();

    Jeep(const Jeep& other) = delete;
    Jeep& operator=(const Jeep& other) = delete;

    int      getMaxPassengers() const;
    int      getPassengerCount() const;
    Soldier* getPassenger(int index) const;

    bool setMaxPassengers(int maxPassengers);

    bool loadPassenger(Soldier* soldier);
    bool unloadPassenger(const Soldier* soldier);

    void print() const override;
};

#endif // JEEP_H
