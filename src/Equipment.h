#ifndef EQUIPMENT_H
#define EQUIPMENT_H

class Equipment {
public:
    enum class eEquipmentStatus {
        WORKING,
        DAMAGED
    };

private:
    char* name;
    char* serialNumber;
    int quantity;
    eEquipmentStatus status;

public:
    Equipment(const char* name,
              const char* serialNumber,
              int quantity,
              eEquipmentStatus status);
    ~Equipment();

    Equipment(const Equipment& other) = delete;
    Equipment& operator=(const Equipment& other) = delete;

    const char* getName() const;
    const char* getSerialNumber() const;
    int getQuantity() const;
    eEquipmentStatus getStatus() const;

    bool setName(const char* name);
    bool setSerialNumber(const char* serialNumber);
    bool setQuantity(int quantity);
    bool setStatus(eEquipmentStatus status);

    void print() const;
};

#endif // EQUIPMENT_H
