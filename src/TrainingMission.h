#ifndef TRAINING_MISSION_H
#define TRAINING_MISSION_H

#include "Mission.h"

class Unit;

class TrainingMission : public Mission
{
public:
    enum class eTrainingType
    {
        FITNESS,
        DRIVING,
        TECHNICAL,
        COMMAND
    };

    enum class eDifficultyLevel
    {
        EASY,
        MEDIUM,
        HARD
    };

private:
    eTrainingType trainingType;
    eDifficultyLevel difficultyLevel;

public:
    TrainingMission(const std::string& missionName, Unit& assignedUnit,
                    eTrainingType trainingType, eDifficultyLevel difficultyLevel);

    eTrainingType getTrainingType() const;
    eDifficultyLevel getDifficultyLevel() const;

    bool setTrainingType(eTrainingType trainingType);
    bool setDifficultyLevel(eDifficultyLevel difficultyLevel);

    bool improveReadiness();

    void print() const override;
};

#endif
