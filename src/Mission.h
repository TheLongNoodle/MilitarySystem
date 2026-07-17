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

    static const char* statusName(eMissionStatus status);

private:
    static int s_nextMissionId;

    std::string missionName;
    int missionId;
    eMissionStatus status;
    Unit& assignedUnit;

    std::vector<MissionObserver*> observers;

public:
    Mission(const std::string& missionName, Unit& assignedUnit);
    virtual ~Mission() = default;

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
