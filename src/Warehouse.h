#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Equipment;

class Warehouse {
private:
    char* name;

    Equipment** equipmentList;
    int count;
    int capacity;

public:
    Warehouse(const char* name);
    ~Warehouse();

    Warehouse(const Warehouse& other) = delete;
    Warehouse& operator=(const Warehouse& other) = delete;

    const char* getName() const;
    int         getEquipmentCount() const;
    Equipment*  getEquipment(int index) const;

    bool setName(const char* name);

    bool       addEquipment(Equipment* equipment);
    Equipment* searchEquipment(const char* name) const;
    void       printEquipment() const;
};

#endif // WAREHOUSE_H
