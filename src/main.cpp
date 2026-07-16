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
#include <stdexcept>
#include <limits>

using namespace std;

const int LINE_LEN = 256;

// Extraction failure (e.g. letters where a number is expected) leaves cin in
// a fail state that silently breaks every read after it, so all numeric input
// goes through these helpers: they recover the stream and re-prompt instead.
void discardBadInput()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const char* prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value))
    {
        discardBadInput();
        cout << "Invalid input, please enter a number." << endl;
        cout << prompt;
    }
    return value;
}

int readIntInRange(const char* prompt, int minValue, int maxValue)
{
    int value = readInt(prompt);
    while (value < minValue || value > maxValue)
    {
        cout << "Value must be between " << minValue << " and "
             << maxValue << "." << endl;
        value = readInt(prompt);
    }
    return value;
}

double readDouble(const char* prompt)
{
    double value;
    cout << prompt;
    while (!(cin >> value))
    {
        discardBadInput();
        cout << "Invalid input, please enter a number." << endl;
        cout << prompt;
    }
    return value;
}

void readPersonInput(const char* namePrompt, char (&name)[LINE_LEN],
                     char (&role)[LINE_LEN], int& day, int& month,
                     int& year, int& rank)
{
    cout << namePrompt;
    cin >> name;
    cout << "Enter birth date:" << endl;
    day   = readInt("Day: ");
    month = readInt("Month: ");
    year  = readInt("Year: ");
    cout << "Role: ";  cin >> role;
    rank = readIntInRange(
        "Rank (0=PRIVATE 1=CORPORAL 2=SERGEANT 3=LIEUTENANT 4=CAPTAIN 5=MAJOR): ",
        0, 5);
}

void addSoldier(MilitarySystem& militarySystem)
{
    char name[LINE_LEN];
    char role[LINE_LEN];
    int day, month, year, rank;

    readPersonInput("Soldier name: ", name, role, day, month, year, rank);

    if (militarySystem.addSoldier(name, Date(day, month, year), role,
                                  (Soldier::eRank)rank))
    {
        cout << "Soldier added." << endl;
    }
    else
    {
        cout << "Failed to add soldier." << endl;
    }
}

void addOfficer(MilitarySystem& militarySystem)
{
    char name[LINE_LEN];
    char role[LINE_LEN];
    int day, month, year, rank;

    readPersonInput("Officer name: ", name, role, day, month, year, rank);

    if (militarySystem.addOfficer(name, Date(day, month, year), role,
                                  (Soldier::eRank)rank))
    {
        cout << "Officer added." << endl;
    }
    else
    {
        cout << "Failed to add officer." << endl;
    }
}

void createUnit(MilitarySystem& militarySystem)
{
    char unitName[LINE_LEN];
    cout << "Unit name: ";
    cin >> unitName;

    if (militarySystem.addUnit(unitName))
    {
        cout << "Unit created." << endl;
    }
    else
    {
        cout << "Failed to create unit." << endl;
    }
}

void transferSoldier(MilitarySystem& militarySystem)
{
    militarySystem.printAllUnits();

    if (militarySystem.getUnitsCount() == 0)
    {
        return;
    }

    int personalNumber = readInt("Soldier personal number: ");
    int newUnitId = readInt("Unit ID: ");

    if (militarySystem.transferSoldier(personalNumber, newUnitId))
    {
        cout << "Soldier assigned to unit." << endl;
    }
    else
    {
        cout << "Failed to assign soldier to unit." << endl;
    }
}

void addVehicle(MilitarySystem& militarySystem)
{
    int vehicleType = readIntInRange("Vehicle type (1=Jeep 2=Truck 3=ArmoredTransport): ", 1, 3);

    char vehicleNumber[LINE_LEN];
    cout << "Vehicle number: ";
    cin >> vehicleNumber;

    bool success = false;
    if (vehicleType == 1)
    {
        int maxPassengers = readInt("Max passengers: ");
        success = militarySystem.addJeep(vehicleNumber, maxPassengers);
    }
    else if (vehicleType == 2)
    {
        double maxWeightKG = readDouble("Max weight (kg): ");
        success = militarySystem.addTruck(vehicleNumber, maxWeightKG);
    }
    else
    {
        int maxPassengers = readInt("Max passengers: ");
        double maxWeightKG = readDouble("Max weight (kg): ");
        success = militarySystem.addArmoredTransport(vehicleNumber, maxPassengers, maxWeightKG);
    }

    if (success) cout << "Vehicle added." << endl;
    else         cout << "Failed to add vehicle." << endl;
}

void addWarehouse(MilitarySystem& militarySystem)
{
    char warehouseName[LINE_LEN];
    cout << "Warehouse name: ";
    cin >> warehouseName;

    if (militarySystem.addWarehouse(warehouseName))
    {
        cout << "Warehouse added." << endl;
    }
    else
    {
        cout << "Failed to add warehouse." << endl;
    }
}

void addEquipment(MilitarySystem& militarySystem)
{
    militarySystem.printAllWarehouses();

    if (militarySystem.getBase().getWarehouseCount() == 0)
    {
        return;
    }

    char warehouseName[LINE_LEN];
    char equipmentName[LINE_LEN];
    char serialNumber[LINE_LEN];
    int quantity, equipmentStatus;

    cout << "Warehouse name: ";
    cin >> warehouseName;

    if (!militarySystem.warehouseExists(warehouseName))
    {
        cout << "Warehouse not found." << endl;
        return;
    }

    cout << "Equipment name: ";
    cin >> equipmentName;
    cout << "Serial number: ";
    cin >> serialNumber;
    quantity = readInt("Quantity: ");
    equipmentStatus = readIntInRange("Status (0=WORKING 1=DAMAGED): ", 0, 1);

    if (militarySystem.addEquipment(warehouseName, equipmentName, serialNumber, quantity,
                                    (Equipment::eEquipmentStatus)equipmentStatus))
    {
        cout << "Equipment added." << endl;
    }
    else
    {
        cout << "Failed to add equipment." << endl;
    }
}

void createTrainingMission(MilitarySystem& militarySystem)
{
    char name[LINE_LEN];

    cout << "Mission name: ";
    cin >> name;
    int unitId = readInt("Assigned unit ID: ");
    int trainingType = readIntInRange(
        "Training type (0=FITNESS 1=DRIVING 2=TECHNICAL 3=COMMAND): ", 0, 3);
    int difficultyLevel = readIntInRange("Difficulty (0=EASY 1=MEDIUM 2=HARD): ", 0, 2);

    if (militarySystem.addTrainingMission(name, unitId,
                                          (TrainingMission::eTrainingType)trainingType,
                                          (TrainingMission::eDifficultyLevel)difficultyLevel))
    {
        cout << "Training mission created." << endl;
    }
    else
    {
        cout << "Failed to create training mission." << endl;
    }
}

void createLogisticsMission(MilitarySystem& militarySystem)
{
    char name[LINE_LEN];

    cout << "Mission name: ";
    cin >> name;

    militarySystem.printAllUnits();
    if (militarySystem.getUnitsCount() == 0)
    {
        return;
    }

    int unitId = readInt("Assigned unit ID: ");

    int missionId = militarySystem.addLogisticsMission(name, unitId);
    if (missionId == -1)
    {
        cout << "Failed to create logistics mission." << endl;
        return;
    }
    cout << "Logistics mission created. Mission ID: " << missionId << endl;

    char answer;
    cout << "Assign a vehicle? (y/n): ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
    {
        militarySystem.printAllVehicles();
        if (militarySystem.getBase().getVehicleCount() == 0)
        {
            cout << "No vehicles in the base." << endl;
        }
        else
        {
            char vehicleNumber[LINE_LEN];
            cout << "Vehicle number: ";
            cin >> vehicleNumber;
            if (militarySystem.setMissionVehicle(missionId, vehicleNumber))
            {
                cout << "Vehicle assigned." << endl;
            }
            else
            {
                cout << "Failed to assign vehicle." << endl;
            }
        }
    }

    while (true)
    {
        cout << "Add equipment to this mission? (y/n): ";
        cin >> answer;
        if (answer != 'y' && answer != 'Y') break;

        militarySystem.printAllWarehouses();
        if (militarySystem.getBase().getWarehouseCount() == 0)
        {
            break;
        }

        char warehouseName[LINE_LEN];
        char equipmentName[LINE_LEN];
        cout << "Warehouse name: ";
        cin >> warehouseName;

        if (!militarySystem.warehouseExists(warehouseName))
        {
            cout << "Warehouse not found." << endl;
            continue;
        }

        cout << "Equipment name: ";
        cin >> equipmentName;
        if (militarySystem.addMissionEquipment(missionId, warehouseName, equipmentName))
        {
            cout << "Equipment added to mission." << endl;
        }
        else
        {
            cout << "Failed to add equipment." << endl;
        }
    }
}

void updateMissionStatus(MilitarySystem& militarySystem)
{
    militarySystem.printAllMissions();
    if (militarySystem.getMissionsCount() == 0)
    {
        return;
    }

    int missionId = readInt("Mission ID: ");
    int missionStatus = readIntInRange(
        "Status (0=NOT_STARTED 1=IN_PROGRESS 2=COMPLETED): ", 0, 2);

    Mission* mission = militarySystem.findMission(missionId);
    if (!mission)
    {
        cout << "Mission not found." << endl;
        return;
    }
    if (mission->setStatus((Mission::eMissionStatus)missionStatus))
    {
        cout << "Status updated." << endl;
    }
    else
    {
        cout << "Status update rejected." << endl;
    }
}

void markVehicleMaintenance(MilitarySystem& militarySystem)
{
    char vehicleNumber[LINE_LEN];
    cout << "Vehicle number: ";
    cin >> vehicleNumber;

    Vehicle* vehicle = militarySystem.findVehicle(vehicleNumber);
    if (!vehicle)
    {
        cout << "Vehicle not found." << endl;
        return;
    }
    if (vehicle->sendToMaintenance())
    {
        cout << "Vehicle marked for maintenance." << endl;
    }
    else
    {
        cout << "Failed." << endl;
    }
}

void printMenu()
{
    cout << endl;
    cout << "=== Military Base Management System ===" << endl;
    cout << " 1. Add soldier" << endl;
    cout << " 2. Add officer" << endl;
    cout << " 3. Create unit" << endl;
    cout << " 4. Assign / transfer soldier to unit" << endl;
    cout << " 5. Add vehicle (Jeep / Truck / ArmoredTransport)" << endl;
    cout << " 6. Add warehouse" << endl;
    cout << " 7. Add equipment to warehouse" << endl;
    cout << " 8. Create training mission" << endl;
    cout << " 9. Create logistics mission" << endl;
    cout << "10. Update mission status" << endl;
    cout << "11. Mark vehicle for maintenance" << endl;
    cout << "12. Print all data" << endl;
    cout << "13. Generate and print report" << endl;
    cout << " 0. Exit" << endl;
}

int main()
{
    MilitarySystem militarySystem;

    cout << "Welcome to the Military Base Management System." << endl;
    cout << "Note: names are single words (use MainDepot, not Main Depot)." << endl;

    int choice;
    do
    {
        printMenu();
        choice = readInt("Choice: ");

        try
        {
            switch (choice)
            {
                case 1:  
                    addSoldier(militarySystem);
                    break;
                case 2:  
                    addOfficer(militarySystem);
                    break;
                case 3:  
                    createUnit(militarySystem);
                    break;
                case 4:  
                    transferSoldier(militarySystem);
                    break;
                case 5:
                    addVehicle(militarySystem);
                    break;
                case 6:
                    addWarehouse(militarySystem);
                    break;
                case 7:
                    addEquipment(militarySystem);
                    break;
                case 8:  
                    createTrainingMission(militarySystem);
                    break;
                case 9:
                    createLogisticsMission(militarySystem);
                    break;
                case 10:
                    updateMissionStatus(militarySystem);
                    break;
                case 11:
                    markVehicleMaintenance(militarySystem);
                    break;
                case 12:
                    militarySystem.printAllData();
                    break;
                case 13:
                    militarySystem.generateReport().print();
                    break;
                case 0:
                    cout << "Goodbye." << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
            }
        }
        catch (const std::exception& e)
        {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 0);

    return 0;
}
