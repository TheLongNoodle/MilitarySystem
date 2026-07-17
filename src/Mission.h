#ifndef MISSION_H
#define MISSION_H

#include <string>
#include <vector>

class Unit;
class MissionObserver;

class Mission
{
public:
    enum class eMissionStatus
    {
        NOT_STARTED,
        IN_PROGRESS,
        COMPLETED
    };

    // Shared status-to-text translation for every mission type (previously
    // duplicated in TrainingMission.cpp and LogisticsMission.cpp).
    static const char* statusName(eMissionStatus status);

private:
    static int s_nextMissionId;

    std::string missionName;
    int missionId;
    eMissionStatus status;
    Unit& assignedUnit;

    // Observer pattern: non-owning subscribers notified on status changes.
    std::vector<MissionObserver*> observers;

public:
    Mission(const std::string& missionName, Unit& assignedUnit);
    // Part 3: nothing left to release, but missions are deleted through
    // Mission*, so the destructor must stay virtual.
    virtual ~Mission() = default;

    // Copying stays deleted: the reference member cannot be reseated and a
    // mission has a unique identity (missionId).
    Mission(const Mission& other) = delete;
    Mission& operator=(const Mission& other) = delete;

    const std::string& getMissionName() const;
    int getMissionId() const;
    eMissionStatus getStatus() const;
    const Unit& getAssignedUnit() const;

    bool setMissionName(const std::string& missionName);
    bool setStatus(eMissionStatus newStatus);

    void attach(MissionObserver* observer);
    void detach(MissionObserver* observer);

    virtual void print() const = 0;
};

#endif
