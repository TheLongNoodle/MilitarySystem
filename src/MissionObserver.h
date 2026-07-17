#ifndef MISSION_OBSERVER_H
#define MISSION_OBSERVER_H

class Mission;

// DESIGN PATTERN: OBSERVER
class MissionObserver
{
public:
    virtual ~MissionObserver() = default;

    virtual void onMissionStatusChanged(const Mission& mission) = 0;
};

#endif
