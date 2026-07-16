#include "TrainingMission.h"
#include "Unit.h"
#include <iostream>

static const char* trainingTypeName(TrainingMission::eTrainingType t)
{
	switch (t)
	{
		case TrainingMission::eTrainingType::FITNESS:
			return "FITNESS";
		case TrainingMission::eTrainingType::DRIVING:
			return "DRIVING";
		case TrainingMission::eTrainingType::TECHNICAL:
			return "TECHNICAL";
		case TrainingMission::eTrainingType::COMMAND:
			return "COMMAND";
	}
	return "?";
}

static const char* difficultyName(TrainingMission::eDifficultyLevel d)
{
	switch (d)
	{
		case TrainingMission::eDifficultyLevel::EASY:
			return "EASY";
		case TrainingMission::eDifficultyLevel::MEDIUM:
			return "MEDIUM";
		case TrainingMission::eDifficultyLevel::HARD:
			return "HARD";
	}
	return "?";
}

static const char* missionStatusName(Mission::eMissionStatus s)
{
	switch (s)
	{
		case Mission::eMissionStatus::NOT_STARTED:
			return "NOT_STARTED";
		case Mission::eMissionStatus::IN_PROGRESS:
			return "IN_PROGRESS";
		case Mission::eMissionStatus::COMPLETED:
			return "COMPLETED";
	}
	return "?";
}

TrainingMission::TrainingMission(const char* missionName, Unit& unit, eTrainingType type, eDifficultyLevel diff)
		: Mission(missionName, unit), trainingType(type), difficultyLevel(diff)
{
}

TrainingMission::eTrainingType TrainingMission::getTrainingType() const
{
	return trainingType;
}

TrainingMission::eDifficultyLevel TrainingMission::getDifficultyLevel() const
{
	return difficultyLevel;
}

bool TrainingMission::setTrainingType(eTrainingType t)
{
	trainingType = t;
	return true;
}
bool TrainingMission::setDifficultyLevel(eDifficultyLevel d)
{
	difficultyLevel = d;
	return true;
}

bool TrainingMission::improveReadiness()
{
	return getStatus() == eMissionStatus::COMPLETED;
}

void TrainingMission::print() const
{
	std::cout << "  TrainingMission [" << getMissionId() << "] '"
		<< getMissionName() << "'"
		<< " | type: " << trainingTypeName(trainingType)
		<< " | difficulty: " << difficultyName(difficultyLevel)
		<< " | status: " << missionStatusName(getStatus())
		<< " | unit: " << getAssignedUnit().getUnitName()
		<< std::endl;
}
