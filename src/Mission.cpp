#include "Mission.h"
#include "MissionObserver.h"
#include "Unit.h"
#include <stdexcept>
#include <algorithm>

int Mission::s_nextMissionId = 1;

const char* Mission::statusName(eMissionStatus status)
{
    switch (status)
    {
        case eMissionStatus::NOT_STARTED:
            return "NOT_STARTED";
        case eMissionStatus::IN_PROGRESS:
            return "IN_PROGRESS";
        case eMissionStatus::COMPLETED:
            return "COMPLETED";
    }
    return "?";
}

Mission::Mission(const std::string& missionName, Unit& unit)
    : missionName(missionName), missionId(0),
      status(eMissionStatus::NOT_STARTED), assignedUnit(unit)
{
    if (missionName.empty())
    {
        throw std::invalid_argument("Mission: name must not be empty");
    }
    this->missionId = s_nextMissionId++;
}

const std::string& Mission::getMissionName() const
{
    return missionName;
}

int Mission::getMissionId() const
{
    return missionId;
}

Mission::eMissionStatus Mission::getStatus() const
{
    return status;
}

const Unit& Mission::getAssignedUnit() const
{
    return assignedUnit;
}

bool Mission::setMissionName(const std::string& n)
{
    if (n.empty())
    {
        return false;
    }
    missionName = n;
    return true;
}

bool Mission::setStatus(eMissionStatus newStatus)
{
    if (status == newStatus)
    {
        return true;
    }
    status = newStatus;
    for (MissionObserver* observer : observers)
    {
        observer->onMissionStatusChanged(*this);
    }
    return true;
}

void Mission::attach(MissionObserver* observer)
{
    if (!observer)
    {
        return;
    }
    if (std::find(observers.begin(), observers.end(), observer) == observers.end())
    {
        observers.push_back(observer);
    }
}

void Mission::detach(MissionObserver* observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
        observers.erase(it);
    }
}
