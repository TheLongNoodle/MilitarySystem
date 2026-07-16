#include "Equipment.h"
#include "Utils.h"
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

Equipment::Equipment(const char* name, const char* serialNumber, int quantity, eEquipmentStatus status)
         : name(nullptr), serialNumber(nullptr)
{
    if (!name || name[0] == '\0')
    {
        throw std::invalid_argument("Equipment: name must not be empty");
    }
    if (!serialNumber || serialNumber[0] == '\0')
    {
        throw std::invalid_argument("Equipment: serial number must not be empty");
    }
    if (quantity < 0)
    {
        throw std::invalid_argument("Equipment: quantity must be non-negative");
    }

    this->name = utils::dupString(name);
    try
    {
        this->serialNumber = utils::dupString(serialNumber);
    }
    catch (...)
    {
        delete[] this->name;
        throw;
    }
    this->quantity = quantity;
    this->status = status;
}

Equipment::~Equipment()
{
    delete[] name;
    delete[] serialNumber;
}

const char* Equipment::getName() const
{
    return name;
}

const char* Equipment::getSerialNumber() const
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

bool Equipment::setName(const char* n)
{
    if (!n || n[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(n);
    delete[] name;
    name = tmp;
    return true;
}

bool Equipment::setSerialNumber(const char* sn)
{
    if (!sn || sn[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(sn);
    delete[] serialNumber;
    serialNumber = tmp;
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
    std::cout << "    Equipment '" << name
              << "' (S/N " << serialNumber
              << ") x" << quantity
              << " [" << statusName(status) << "]"
              << std::endl;
}
