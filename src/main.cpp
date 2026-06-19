#include "MilitarySystem.h"
#include "Date.h"
#include "Soldier.h"
#include "Equipment.h"
#include "Mission.h"
#include "TrainingMission.h"
#include "LogisticsMission.h"
#include "Vehicle.h"
#include "Report.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int LINE_LEN = 256;

void readPersonInput(const char* namePrompt,
                     char* name,
                     char* role,
                     int& day,
                     int& month,
                     int& year,
                     int& rank) {
    cout << namePrompt;
    cin >> name;
    cout << "Enter birth date:" << endl;
    cout << "Day: ";   cin >> day;
    cout << "Month: "; cin >> month;
    cout << "Year: ";  cin >> year;
    cout << "Role: ";  cin >> role;
    cout << "Rank (0=PRIVATE 1=CORPORAL 2=SERGEANT 3=LIEUTENANT 4=CAPTAIN 5=MAJOR): ";
    cin >> rank;
}

void addSoldier(MilitarySystem& militarySystem) {
    char name[LINE_LEN];
    char role[LINE_LEN];
    int day, month, year, rank;

    readPersonInput("Soldier name: ", name, role, day, month, year, rank);

    if (militarySystem.addSoldier(name, Date(day, month, year), role,
                                  (Soldier::eRank)rank)) {
        cout << "Soldier added." << endl;
    } else {
        cout << "Failed to add soldier." << endl;
    }
}

void addOfficer(MilitarySystem& militarySystem) {
    char name[LINE_LEN];
    char role[LINE_LEN];
    int day, month, year, rank;

    readPersonInput("Officer name: ", name, role, day, month, year, rank);

    if (militarySystem.addOfficer(name, Date(day, month, year), role,
                                  (Soldier::eRank)rank)) {
        cout << "Officer added." << endl;
    } else {
        cout << "Failed to add officer." << endl;
    }
}

void createUnit(MilitarySystem& militarySystem) {
    char unitName[LINE_LEN];
    cout << "Unit name: ";
    cin >> unitName;

    if (militarySystem.addUnit(unitName)) {
        cout << "Unit created." << endl;
    } else {
        cout << "Failed to create unit." << endl;
    }
}

void transferSoldier(MilitarySystem& militarySystem) {
    militarySystem.printAllUnits();

    if (militarySystem.getBase().getUnitCount() == 0) {
        return;
    }

    int personalNumber, newUnitId;
    cout << "Soldier personal number: ";
    cin >> personalNumber;
    cout << "Unit ID: ";
    cin >> newUnitId;

    if (militarySystem.transferSoldier(personalNumber, newUnitId)) {
        cout << "Soldier assigned to unit." << endl;
    } else {
        cout << "Failed to assign soldier to unit." << endl;
    }
}

void addVehicle(MilitarySystem& militarySystem) {
    int vehicleType;
    cout << "Vehicle type (1=Jeep 2=Truck 3=ArmoredTransport): ";
    cin >> vehicleType;

    char vehicleNumber[LINE_LEN];
    cout << "Vehicle number: ";
    cin >> vehicleNumber;

    bool success = false;
    if (vehicleType == 1) {
        int maxPassengers;
        cout << "Max passengers: "; cin >> maxPassengers;
        success = militarySystem.addJeep(vehicleNumber, maxPassengers);
    } else if (vehicleType == 2) {
        double maxWeightKG;
        cout << "Max weight (kg): "; cin >> maxWeightKG;
        success = militarySystem.addTruck(vehicleNumber, maxWeightKG);
    } else if (vehicleType == 3) {
        int maxPassengers;
        double maxWeightKG;
        cout << "Max passengers: "; cin >> maxPassengers;
        cout << "Max weight (kg): "; cin >> maxWeightKG;
        success = militarySystem.addArmoredTransport(vehicleNumber, maxPassengers, maxWeightKG);
    } else {
        cout << "Invalid vehicle type." << endl;
        return;
    }

    if (success) cout << "Vehicle added." << endl;
    else         cout << "Failed to add vehicle." << endl;
}

void addWarehouse(MilitarySystem& militarySystem) {
    char warehouseName[LINE_LEN];
    cout << "Warehouse name: "; 
    cin >> warehouseName;

    if (militarySystem.addWarehouse(warehouseName)) {
        cout << "Warehouse added." << endl;
    } else {
        cout << "Failed to add warehouse." << endl;
    }
}

void addEquipment(MilitarySystem& militarySystem) {
    militarySystem.printAllWarehouses();

    if (militarySystem.getBase().getWarehouseCount() == 0) {
        return;
    }

    char warehouseName[LINE_LEN];
    char equipmentName[LINE_LEN];
    char serialNumber[LINE_LEN];
    int quantity, equipmentStatus;

    cout << "Warehouse name: ";
    cin >> warehouseName;

    if (!militarySystem.warehouseExists(warehouseName)) {
        cout << "Warehouse not found." << endl;
        return;
    }

    cout << "Equipment name: ";
    cin >> equipmentName;
    cout << "Serial number: ";
    cin >> serialNumber;
    cout << "Quantity: ";
    cin >> quantity;
    cout << "Status (0=WORKING 1=DAMAGED): ";
    cin >> equipmentStatus;

    if (militarySystem.addEquipment(warehouseName, equipmentName, serialNumber, quantity,
                                    (Equipment::eEquipmentStatus)equipmentStatus)) {
        cout << "Equipment added." << endl;
    } else {
        cout << "Failed to add equipment." << endl;
    }
}

void createTrainingMission(MilitarySystem& militarySystem) {
    char name[LINE_LEN];
    int unitId, trainingType, difficultyLevel;

    cout << "Mission name: ";   
    cin >> name;
    cout << "Assigned unit ID: "; 
    cin >> unitId;
    cout << "Training type (0=FITNESS 1=DRIVING 2=TECHNICAL 3=COMMAND): "; 
    cin >> trainingType;
    cout << "Difficulty (0=EASY 1=MEDIUM 2=HARD): ";                      
    cin >> difficultyLevel;

    if (militarySystem.addTrainingMission(name, unitId,
                                          (TrainingMission::eTrainingType)trainingType,
                                          (TrainingMission::eDifficultyLevel)difficultyLevel)) {
        cout << "Training mission created." << endl;
    } else {
        cout << "Failed to create training mission." << endl;
    }
}

void createLogisticsMission(MilitarySystem& militarySystem) {
    char name[LINE_LEN];
    int unitId;

    cout << "Mission name: ";
    cin >> name;

    militarySystem.printAllUnits();
    if (militarySystem.getBase().getUnitCount() == 0) {
        return;
    }

    cout << "Assigned unit ID: ";
    cin >> unitId;

    int missionId = militarySystem.addLogisticsMission(name, unitId);
    if (missionId == -1) {
        cout << "Failed to create logistics mission." << endl;
        return;
    }
    cout << "Logistics mission created. Mission ID: " << missionId << endl;

    char answer;
    cout << "Assign a vehicle? (y/n): ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        militarySystem.printAllVehicles();
        if (militarySystem.getBase().getVehicleCount() == 0) {
            cout << "No vehicles in the base." << endl;
        } else {
            char vehicleNumber[LINE_LEN];
            cout << "Vehicle number: ";
            cin >> vehicleNumber;
            if (militarySystem.setMissionVehicle(missionId, vehicleNumber)) {
                cout << "Vehicle assigned." << endl;
            } else {
                cout << "Failed to assign vehicle." << endl;
            }
        }
    }

    while (true) {
        cout << "Add equipment to this mission? (y/n): ";
        cin >> answer;
        if (answer != 'y' && answer != 'Y') break;

        militarySystem.printAllWarehouses();
        if (militarySystem.getBase().getWarehouseCount() == 0) {
            break;
        }

        char warehouseName[LINE_LEN];
        char equipmentName[LINE_LEN];
        cout << "Warehouse name: ";
        cin >> warehouseName;

        if (!militarySystem.warehouseExists(warehouseName)) {
            cout << "Warehouse not found." << endl;
            continue;
        }

        cout << "Equipment name: ";
        cin >> equipmentName;
        if (militarySystem.addMissionEquipment(missionId, warehouseName, equipmentName)) {
            cout << "Equipment added to mission." << endl;
        } else {
            cout << "Failed to add equipment." << endl;
        }
    }
}

void updateMissionStatus(MilitarySystem& militarySystem) {
    int missionId, missionStatus;

    militarySystem.printAllMissions();
    if (militarySystem.getMissionsCount() == 0) {
        return;
    }

    cout << "Mission ID: ";                                       
    cin >> missionId;
    cout << "Status (0=NOT_STARTED 1=IN_PROGRESS 2=COMPLETED): "; 
    cin >> missionStatus;

    Mission* mission = militarySystem.findMission(missionId);
    if (!mission) {
        cout << "Mission not found." << endl;
        return;
    }
    if (mission->setStatus((Mission::eMissionStatus)missionStatus)) {
        cout << "Status updated." << endl;
    } else {
        cout << "Status update rejected." << endl;
    }
}

void markVehicleMaintenance(MilitarySystem& militarySystem) {
    char vehicleNumber[LINE_LEN];
    cout << "Vehicle number: "; 
    cin >> vehicleNumber;

    Vehicle* vehicle = militarySystem.findVehicle(vehicleNumber);
    if (!vehicle) {
        cout << "Vehicle not found." << endl;
        return;
    }
    if (vehicle->sendToMaintenance()) {
        cout << "Vehicle marked for maintenance." << endl;
    } else {
        cout << "Failed." << endl;
    }
}

void printMenu() {
    cout << endl;
    cout << "=== Military Base Management System ===" << endl;
    cout << " 1. Add soldier"                                              << endl;
    cout << " 2. Add officer"                                              << endl;
    cout << " 3. Create unit"                                              << endl;
    cout << " 4. Assign / transfer soldier to unit"                       << endl;
    cout << " 5. Add vehicle (Jeep / Truck / ArmoredTransport)"            << endl;
    cout << " 6. Add warehouse"                                            << endl;
    cout << " 7. Add equipment to warehouse"                               << endl;
    cout << " 8. Create training mission"                                  << endl;
    cout << " 9. Create logistics mission"                                 << endl;
    cout << "10. Update mission status"                                    << endl;
    cout << "11. Mark vehicle for maintenance"                             << endl;
    cout << "12. Print all data"                                           << endl;
    cout << "13. Generate and print report"                                << endl;
    cout << " 0. Exit"                                                     << endl;
}

int main() {
    srand((unsigned)time(nullptr));
    MilitarySystem militarySystem;

    cout << "Welcome to the Military Base Management System." << endl;
    cout << "Note: names are single words (use MainDepot, not Main Depot)." << endl;

    int choice;
    do {
        printMenu();
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:  addSoldier(militarySystem);                       break;
            case 2:  addOfficer(militarySystem);                       break;
            case 3:  createUnit(militarySystem);                       break;
            case 4:  transferSoldier(militarySystem);                  break;
            case 5:  addVehicle(militarySystem);                       break;
            case 6:  addWarehouse(militarySystem);                     break;
            case 7:  addEquipment(militarySystem);                     break;
            case 8:  createTrainingMission(militarySystem);            break;
            case 9:  createLogisticsMission(militarySystem);           break;
            case 10: updateMissionStatus(militarySystem);              break;
            case 11: markVehicleMaintenance(militarySystem);           break;
            case 12: militarySystem.printAllData();                    break;
            case 13: militarySystem.generateReport().print();          break;
            case 0:  cout << "Goodbye." << endl;                       break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
