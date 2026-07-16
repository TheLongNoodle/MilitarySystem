#include "Warehouse.h"
#include "Equipment.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

Warehouse::Warehouse(const char* name) : name(nullptr), equipmentList(nullptr)
{
    count = 0;

    if (!name || name[0] == '\0')
    {
        throw std::invalid_argument("Warehouse: name must not be empty");
    }

    this->name = utils::dupString(name);
    try
    {
        capacity = 16;
        equipmentList = new Equipment*[capacity];
    }
    catch (...)
    {
        delete[] this->name;
        throw;
    }
}

Warehouse::~Warehouse()
{
    for (int i = 0; i < count; ++i)
    {
        delete equipmentList[i];
    }
    delete[] equipmentList;
    delete[] name;
}

const char* Warehouse::getName() const
{
    return name;
}

int Warehouse::getEquipmentCount() const
{
    return count;
}

Equipment* Warehouse::getEquipment(int index) const
{
    if (index < 0 || index >= count)
    {
        return nullptr;
    }
    return equipmentList[index];
}

bool Warehouse::setName(const char* n)
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

bool Warehouse::addEquipment(Equipment* equipment)
{
    if (!equipment)
    {
        return false;
    }

    if (count == capacity)
    {
        const int newCap = capacity * 2;
        Equipment** larger = new Equipment*[newCap];
        for (int i = 0; i < count; ++i)
        {
            larger[i] = equipmentList[i];
        }
        delete[] equipmentList;
        equipmentList = larger;
        capacity = newCap;
    }
    equipmentList[count++] = equipment;
    return true;
}

Equipment* Warehouse::searchEquipment(const char* searchName) const
{
    if (!searchName)
    {
        return nullptr;
    }
    for (int i = 0; i < count; ++i)
    {
        if (std::strcmp(equipmentList[i]->getName(), searchName) == 0)
        {
            return equipmentList[i];
        }
    }
    return nullptr;
}

void Warehouse::printEquipment() const
{
    std::cout << "  Warehouse '" << name
    << "' (" << count << " item(s)):" << std::endl;
    for (int i = 0; i < count; ++i)
    {
        equipmentList[i]->print();
    }
}

const Equipment& Warehouse::operator[](int index) const
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Warehouse::operator[]: index out of range");
    }
    return *equipmentList[index];
}
