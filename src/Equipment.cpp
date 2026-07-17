#include "Equipment.h"
#include <iostream>
#include <stdexcept>

static const char* statusName(Equipment::eEquipmentStatus s)
{
    switch (s)
    {
        case Equipment::eEquipmentStatus::WORKING:
            return "WORKING";
        case Equipment::eEquipmentStatus::DAMAGED:
            return "DAMAGED";
    }
    return "?";
}

Equipment::Equipment(const std::string& name, const std::string& serialNumber,
                     int quantity, eEquipmentStatus status)
         : name(name), serialNumber(serialNumber), quantity(quantity), status(status)
{
    if (name.empty())
    {
        throw std::invalid_argument("Equipment: name must not be empty");
    }
    if (serialNumber.empty())
    {
        throw std::invalid_argument("Equipment: serial number must not be empty");
    }
    if (quantity < 0)
    {
        throw std::invalid_argument("Equipment: quantity must be non-negative");
    }
}

const std::string& Equipment::getName() const
{
    return name;
}

const std::string& Equipment::getSerialNumber() const
{
    return serialNumber;
}

int Equipment::getQuantity() const
{
    return quantity;
}

Equipment::eEquipmentStatus Equipment::getStatus() const
{
    return status;
}

bool Equipment::setName(const std::string& n)
{
    if (n.empty())
    {
        return false;
    }
    name = n;
    return true;
}

bool Equipment::setSerialNumber(const std::string& sn)
{
    if (sn.empty())
    {
        return false;
    }
    serialNumber = sn;
    return true;
}

bool Equipment::setQuantity(int q)
{
    if (q < 0)
    {
        return false;
    }
    quantity = q;
    return true;
}

bool Equipment::setStatus(eEquipmentStatus s)
{
    status = s;
    return true;
}

void Equipment::print() const
{
    std::cout << "    " << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Equipment& e)
{
    os << "Equipment '" << e.getName()
       << "' (S/N " << e.getSerialNumber()
       << ") x" << e.getQuantity()
       << " [" << statusName(e.getStatus()) << "]";
    return os;
}
