#include "finalSchedule.h"
#include "employeeRepository.h"
#include "teamRepository.h"

FinalSchedule::FinalSchedule(const teamRepositoryPtr &teamRepository, const empRepositoryPtr &employeeReepository)
{
    for(const auto &team : teamRepository->getAll())
    {
        allQueues.emplace_back(TeamQueues(team,employeeReepository->getAll()));
    }

}