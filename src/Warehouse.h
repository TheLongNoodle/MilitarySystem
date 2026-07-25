#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>

class Equipment;

class Warehouse
{
private:
    std::string name;

    std::vector<Equipment*> equipmentList;

public:
    Warehouse(const std::string& name);
    ~Warehouse();

    Warehouse(const Warehouse& other) = delete;
    Warehouse& operator=(const Warehouse& other) = delete;

    const std::string& getName() const;
    int getEquipmentCount() const;
    Equipment* getEquipment(int index) const;

    bool setName(const std::string& name);

    bool addEquipment(Equipment* equipment);
    Equipment* searchEquipment(const std::string& name) const;
    void printEquipment() const;

    const Equipment& operator[](int index) const;
};

#endif
