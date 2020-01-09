#include "teamManager.h"
#include "teamRepository.h"


void TeamManager::addTeam(const std::string &name)
{
    TeamRepository::getInstance().addTeam(name);
}

void TeamManager::removeTeam(const std::string &name)
{
    TeamRepository::getInstance().removeTeam(name);
}

const teamPtr& TeamManager::getTeamByName(const std::string &name) const
{
    return TeamRepository::getInstance().getTeamByName(name);
}

std::string TeamManager::repositoryInfo() const
{
    return TeamRepository::getInstance().repositoryInfo();
}