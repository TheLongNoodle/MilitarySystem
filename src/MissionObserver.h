#ifndef MISSION_OBSERVER_H
#define MISSION_OBSERVER_H

class Mission;

// Observer design pattern (part 3, requirement G).
// Anyone interested in mission lifecycle events implements this interface
// and registers itself on a Mission with attach(). The Mission notifies all
// attached observers whenever its status changes, without knowing anything
// about who listens or what they do with the event (e.g. the console
// notifier defined in main.cpp). Observers are not owned by the mission.
class MissionObserver
{
public:
    virtual ~MissionObserver() = default;

    virtual void onMissionStatusChanged(const Mission& mission) = 0;
};

#endif
