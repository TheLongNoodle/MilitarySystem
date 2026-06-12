#ifndef TRAINING_MISSION_H
#define TRAINING_MISSION_H

#include "Mission.h"

class TrainingMission : public Mission {
public:
    enum class eTrainingType {
        FITNESS,
        DRIVING,
        TECHNICAL,
        COMMAND
    };

    enum class eDifficultyLevel {
        EASY,
        MEDIUM,
        HARD
    };

private:
    eTrainingType    trainingType;
    eDifficultyLevel difficultyLevel;

public:
    TrainingMission(const char* missionName,
                    Unit* assignedUnit,
                    eTrainingType trainingType,
                    eDifficultyLevel difficultyLevel);

    TrainingMission(const TrainingMission& other) = delete;
    TrainingMission& operator=(const TrainingMission& other) = delete;

    eTrainingType    getTrainingType() const;
    eDifficultyLevel getDifficultyLevel() const;

    bool setTrainingType(eTrainingType trainingType);
    bool setDifficultyLevel(eDifficultyLevel difficultyLevel);

    bool improveReadiness();

    void print() const override;
};

#endif // TRAINING_MISSION_H
