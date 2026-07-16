#include "Mission.h"
#include "Unit.h"
#include "Utils.h"
#include <stdexcept>

int Mission::s_nextMissionId = 1;

Mission::Mission(const char* missionName, Unit& unit) : missionName(nullptr),
                 missionId(0), status(eMissionStatus::NOT_STARTED), assignedUnit(unit)
{
    if (!missionName || missionName[0] == '\0')
    {
        throw std::invalid_argument("Mission: name must not be empty");
    }
    this->missionName = utils::dupString(missionName);
    this->missionId = s_nextMissionId++;
}

Mission::~Mission()
{
    delete[] missionName;
}

const char* Mission::getMissionName() const
{
    return missionName;
}

int Mission::getMissionId() const
{
    return missionId;
}

Mission::eMissionStatus  Mission::getStatus() const
{
    return status;
}

const Unit& Mission::getAssignedUnit() const
{
    return assignedUnit;
}

bool Mission::setMissionName(const char* n)
{
    if (!n || n[0] == '\0')
    {
        return false;
    }
    char* tmp = utils::dupString(n);
    delete[] missionName;
    missionName = tmp;
    return true;
}

bool Mission::setStatus(eMissionStatus newStatus)
{
    status = newStatus;
    return true;
}
