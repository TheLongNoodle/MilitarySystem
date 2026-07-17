#include "MilitarySystem.h"
#include "Date.h"
#include "Soldier.h"
#include "Equipment.h"
#include "Mission.h"
#include "MissionObserver.h"
#include "TrainingMission.h"
#include "LogisticsMission.h"
#include "Vehicle.h"
#include "VehicleFactory.h"
#include "Report.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

class ConsoleMissionNotifier : public MissionObserver
{
public:
    void onMissionStatusChanged(const Mission& mission) override
    {
        cout << "[NOTIFICATION] Mission '" << mission.getMissionName()
             << "' (ID " << mission.getMissionId() << ") is now "
             << Mission::statusName(mission.getStatus()) << "." << endl;
    }
};

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

string readWord(const char* prompt)
{
    string value;
    cout << prompt;
    cin >> value;
    return value;
}

void readPersonInput(const char* namePrompt, string& name,
                     string& role, int& day, int& month,
                     int& year, int& rank)
{
    name = readWord(namePrompt);
    cout << "Enter birth date:" << endl;
    day   = readInt("Day: ");
    month = readInt("Month: ");
    year  = readInt("Year: ");
    role = readWord("Role: ");
    rank = readIntInRange(
        "Rank (0=PRIVATE 1=CORPORAL 2=SERGEANT 3=LIEUTENANT 4=CAPTAIN 5=MAJOR): ",
        0, 5);
}

void addSoldier(MilitarySystem& militarySystem)
{
    string name, role;
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
    string name, role;
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
    string unitName = readWord("Unit name: ");

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

void assignSoldierToOfficer(MilitarySystem& militarySystem)
{
    int officerNumber = readInt("Officer personal number: ");
    int soldierNumber = readInt("Soldier personal number: ");

    if (militarySystem.assignSoldierToOfficer(officerNumber, soldierNumber))
    {
        cout << "Soldier assigned to officer's command." << endl;
    }
    else
    {
        cout << "Failed to assign soldier to officer." << endl;
    }
}

void addVehicle(MilitarySystem& militarySystem)
{
    int vehicleType = readIntInRange("Vehicle type (1=Jeep 2=Truck 3=ArmoredTransport): ", 1, 3);

    string vehicleNumber = readWord("Vehicle number: ");

    int maxPassengers = 0;
    double maxWeightKG = 0.0;
    VehicleFactory::eVehicleType type;

    if (vehicleType == 1)
    {
        type = VehicleFactory::eVehicleType::JEEP;
        maxPassengers = readInt("Max passengers: ");
    }
    else if (vehicleType == 2)
    {
        type = VehicleFactory::eVehicleType::TRUCK;
        maxWeightKG = readDouble("Max weight (kg): ");
    }
    else
    {
        type = VehicleFactory::eVehicleType::ARMORED_TRANSPORT;
        maxPassengers = readInt("Max passengers: ");
        maxWeightKG = readDouble("Max weight (kg): ");
    }

    if (militarySystem.addVehicle(type, vehicleNumber, maxPassengers, maxWeightKG))
    {
        cout << "Vehicle added." << endl;
    }
    else
    {
        cout << "Failed to add vehicle." << endl;
    }
}

void addWarehouse(MilitarySystem& militarySystem)
{
    string warehouseName = readWord("Warehouse name: ");

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

    string warehouseName = readWord("Warehouse name: ");

    if (!militarySystem.warehouseExists(warehouseName))
    {
        cout << "Warehouse not found." << endl;
        return;
    }

    string equipmentName = readWord("Equipment name: ");
    string serialNumber = readWord("Serial number: ");
    int quantity = readInt("Quantity: ");
    int equipmentStatus = readIntInRange("Status (0=WORKING 1=DAMAGED): ", 0, 1);

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
    string name = readWord("Mission name: ");
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
    string name = readWord("Mission name: ");

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
            string vehicleNumber = readWord("Vehicle number: ");
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

        string warehouseName = readWord("Warehouse name: ");

        if (!militarySystem.warehouseExists(warehouseName))
        {
            cout << "Warehouse not found." << endl;
            continue;
        }

        string equipmentName = readWord("Equipment name: ");
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
    string vehicleNumber = readWord("Vehicle number: ");

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

// Create mock data
void createMockData(MilitarySystem& militarySystem)
{
    static int s_mockBatch = 0;
    ++s_mockBatch;
    const string tag = "-M" + to_string(s_mockBatch);

    const int pnBase = 100000 + militarySystem.generateReport().getSoldierCount();
    const int unitBase = 100 + militarySystem.getUnitsCount();
    const int missionBase = 1 + militarySystem.getMissionsCount();

    cout << "Creating mock data (batch " << s_mockBatch << ")..." << endl;

    // personnel: 4 soldiers (pnBase..+3) and 2 officers (+4, +5)
    militarySystem.addSoldier("Avi" + tag,  Date(12, 3, 2001), "Rifleman", Soldier::eRank::PRIVATE);
    militarySystem.addSoldier("Ben" + tag,  Date(30, 7, 2000), "Medic",    Soldier::eRank::CORPORAL);
    militarySystem.addSoldier("Chen" + tag, Date(15, 1, 2002), "Driver",   Soldier::eRank::PRIVATE);
    militarySystem.addSoldier("Dana" + tag, Date(9, 11, 1999), "Sniper",   Soldier::eRank::SERGEANT);
    militarySystem.addOfficer("Gadi" + tag, Date(2, 6, 1993),  "Commander", Soldier::eRank::CAPTAIN);
    militarySystem.addOfficer("Noa" + tag,  Date(21, 9, 1990), "OpsOfficer", Soldier::eRank::MAJOR);

    // units and assignments
    militarySystem.addUnit("Alpha" + tag);   // unitBase
    militarySystem.addUnit("Bravo" + tag);   // unitBase + 1
    militarySystem.assignSoldierToUnit(pnBase,     unitBase);      // Avi  - Alpha
    militarySystem.assignSoldierToUnit(pnBase + 1, unitBase);      // Ben  - Alpha
    militarySystem.assignSoldierToUnit(pnBase + 4, unitBase);      // Gadi - Alpha
    militarySystem.assignSoldierToUnit(pnBase + 2, unitBase + 1);  // Chen - Bravo
    militarySystem.assignSoldierToUnit(pnBase + 3, unitBase + 1);  // Dana - Bravo

    // officer command (linked list)
    militarySystem.assignSoldierToOfficer(pnBase + 4, pnBase);      // Gadi commands Avi
    militarySystem.assignSoldierToOfficer(pnBase + 4, pnBase + 1);  // Gadi commands Ben
    militarySystem.assignSoldierToOfficer(pnBase + 5, pnBase + 2);  // Noa commands Chen

    // vehicles via the factory
    militarySystem.addVehicle(VehicleFactory::eVehicleType::JEEP,  "J" + tag, 4, 0.0);
    militarySystem.addVehicle(VehicleFactory::eVehicleType::TRUCK, "T" + tag, 0, 500.0);
    militarySystem.addVehicle(VehicleFactory::eVehicleType::ARMORED_TRANSPORT,
                              "A" + tag, 8, 1200.0);
    militarySystem.setVehicleDriver("J" + tag, pnBase + 2);         // Chen drives the jeep

    // warehouse with equipment
    militarySystem.addWarehouse("Depot" + tag);
    militarySystem.addEquipment("Depot" + tag, "Radio", "SN-R" + tag, 5,
                                Equipment::eEquipmentStatus::WORKING);
    militarySystem.addEquipment("Depot" + tag, "Tent", "SN-T" + tag, 2,
                                Equipment::eEquipmentStatus::WORKING);
    militarySystem.addEquipment("Depot" + tag, "Generator", "SN-G" + tag, 1,
                                Equipment::eEquipmentStatus::DAMAGED);

    // missions
    militarySystem.addTrainingMission("Drill" + tag, unitBase,       // missionBase
                                      TrainingMission::eTrainingType::DRIVING,
                                      TrainingMission::eDifficultyLevel::HARD);
    int logisticsId = militarySystem.addLogisticsMission("Supply" + tag, unitBase + 1);
    militarySystem.setMissionVehicle(logisticsId, "T" + tag);
    militarySystem.addMissionEquipment(logisticsId, "Depot" + tag, "Radio");
    militarySystem.addMissionEquipment(logisticsId, "Depot" + tag, "Tent");

    // a status change so the observer notification is demonstrated
    Mission* drill = militarySystem.findMission(missionBase);
    if (drill)
    {
        drill->setStatus(Mission::eMissionStatus::IN_PROGRESS);
    }

    cout << "Mock data ready:" << endl;
    cout << "  Soldiers " << pnBase << "-" << pnBase + 3
         << ", officers " << pnBase + 4 << " (Gadi) and " << pnBase + 5 << " (Noa)" << endl;
    cout << "  Units " << unitBase << " (Alpha" << tag << ") and "
         << unitBase + 1 << " (Bravo" << tag << ")" << endl;
    cout << "  Vehicles J" << tag << ", T" << tag << ", A" << tag
         << " | warehouse Depot" << tag << endl;
    cout << "  Missions " << missionBase << " (Drill" << tag << ", in progress) and "
         << logisticsId << " (Supply" << tag << ")" << endl;
    cout << "Use option 12 to see everything." << endl;
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
    cout << "14. Assign soldier to officer's command" << endl;
    cout << "15. Create mock data (demo scenario)" << endl;
    cout << " 0. Exit" << endl;
}

int main()
{
    MilitarySystem& militarySystem = MilitarySystem::getInstance();

    ConsoleMissionNotifier notifier;
    militarySystem.setMissionObserver(&notifier);

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
                case 14:
                    assignSoldierToOfficer(militarySystem);
                    break;
                case 15:
                    createMockData(militarySystem);
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
