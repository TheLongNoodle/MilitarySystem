#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <iosfwd>

class Equipment
{
public:
    enum class eEquipmentStatus
    {
        WORKING,
        DAMAGED
    };

private:
    std::string name;
    std::string serialNumber;
    int quantity;
    eEquipmentStatus status;

public:
    Equipment(const std::string& name, const std::string& serialNumber,
              int quantity, eEquipmentStatus status);

    const std::string& getName() const;
    const std::string& getSerialNumber() const;
    int getQuantity() const;
    eEquipmentStatus getStatus() const;

    bool setName(const std::string& name);
    bool setSerialNumber(const std::string& serialNumber);
    bool setQuantity(int quantity);
    bool setStatus(eEquipmentStatus status);

    void print() const;
};

std::ostream& operator<<(std::ostream& os, const Equipment& e);

#endif
