#include "Warehouse.h"
#include "Equipment.h"
#include <iostream>
#include <stdexcept>

Warehouse::Warehouse(const std::string& name) : name(name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Warehouse: name must not be empty");
    }
}

Warehouse::~Warehouse()
{
    for (Equipment* equipment : equipmentList)
    {
        delete equipment;
    }
}

const std::string& Warehouse::getName() const
{
    return name;
}

int Warehouse::getEquipmentCount() const
{
    return static_cast<int>(equipmentList.size());
}

Equipment* Warehouse::getEquipment(int index) const
{
    if (index < 0 || index >= static_cast<int>(equipmentList.size()))
    {
        return nullptr;
    }
    return equipmentList[index];
}

bool Warehouse::setName(const std::string& n)
{
    if (n.empty())
    {
        return false;
    }
    name = n;
    return true;
}

bool Warehouse::addEquipment(Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }
    equipmentList.push_back(equipment);
    return true;
}

Equipment* Warehouse::searchEquipment(const std::string& searchName) const
{
    for (Equipment* equipment : equipmentList)
    {
        if (equipment->getName() == searchName)
        {
            return equipment;
        }
    }
    return nullptr;
}

void Warehouse::printEquipment() const
{
    std::cout << "  Warehouse '" << name
    << "' (" << equipmentList.size() << " item(s)):" << std::endl;
    // Indexed access here is deliberate: it exercises operator[], which is
    // the class's own bounds-checked accessor, rather than the raw vector.
    for (int i = 0; i < getEquipmentCount(); ++i)
    {
        std::cout << "    " << (*this)[i] << std::endl;
    }
}

const Equipment& Warehouse::operator[](int index) const
{
    if (index < 0 || index >= static_cast<int>(equipmentList.size()))
    {
        throw std::out_of_range("Warehouse::operator[]: index out of range");
    }
    return *equipmentList[index];
}
