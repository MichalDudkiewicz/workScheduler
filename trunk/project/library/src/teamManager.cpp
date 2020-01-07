#include "teamManager.h"
#include "teamRepository.h"

TeamManager::TeamManager() : teamRepository(TeamRepository::getInstance())
{}

void TeamManager::addTeam(const std::string &name)
{
    teamRepository->addTeam(name);
}

void TeamManager::removeTeam(const std::string &name)
{
    teamRepository->removeTeam(name);
}

const teamPtr& TeamManager::getTeamByName(const std::string &name) const
{
    return teamRepository->getTeamByName(name);
}

std::string TeamManager::repositoryInfo() const
{
    return teamRepository->repositoryInfo();
}