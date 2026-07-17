#ifndef JEEP_H
#define JEEP_H

#include "Vehicle.h"
#include <vector>

class Soldier;

// Part 3: the passengers array became a std::vector of non-owning pointers,
// so the destructor was removed. maxPassengers is a domain rule (seating
// capacity), not container bookkeeping, so it remains a field. The deleted
// copy operations were removed as redundant - Vehicle already forbids copying.
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
