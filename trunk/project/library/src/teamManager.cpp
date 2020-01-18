#include "teamManager.h"
#include "teamRepository.h"

TeamManager& TeamManager::getInstance()
{
    static TeamManager instance;
    return instance;
}

void TeamManager::addTeam(const std::string &name)
{
    TeamRepository::getInstance().add(name);
}

void TeamManager::removeTeam(const std::string &name)
{
    TeamRepository::getInstance().remove(name);
}

const teamPtr& TeamManager::getTeamByName(const std::string &name) const
{
    return TeamRepository::getInstance().get(name);
}

std::string TeamManager::repositoryInfo() const
{
    return TeamRepository::getInstance().info();
}

const std::vector<teamPtr> &TeamManager::getAll() const {
    return TeamRepository::getInstance().getAll();
}
