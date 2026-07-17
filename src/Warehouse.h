#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>

class Equipment;

// Part 3: name became std::string and the equipment array became a
// std::vector. The destructor and the deleted copy operations REMAIN:
// the warehouse owns the Equipment objects behind its pointers, so it must
// delete them and must not be shallow-copied.
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
