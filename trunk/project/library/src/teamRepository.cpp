#include "teamRepository.h"
#include "team.h"
#include <sstream>


TeamRepository* TeamRepository::instance=nullptr;

TeamRepository* TeamRepository::getInstance()
{
    if(instance==nullptr)
    {
        instance = new TeamRepository;
    }
    return instance;
}

void TeamRepository::addTeam(const teamPtr &team)
{
    teamsRepository.push_back(team);
}

void TeamRepository::addTeam(const std::string &name)
{
    teamPtr team = std::make_shared<Team>(name);
    teamsRepository.push_back(team);
}

void TeamRepository::removeTeam(const std::string &name)
{
    unsigned int it = 0;
    for(const auto &t : teamsRepository)
    {
        if(t->getName()==name)
        {
            teamsRepository.erase(teamsRepository.begin()+it);
            return;
        }
        ++it;
    }
}

const teamPtr& TeamRepository::getTeamByName(const std::string &name) const
{
    for(const auto &t : teamsRepository)
    {
        if(t->getName()==name)
        {
            return t;
        }
    }
    // exepction team doesnt exist
    return teamsRepository[0];
}

const teams& TeamRepository::getAll() const
{
    return teamsRepository;
}

std::string TeamRepository::repositoryInfo() const
{
    std::ostringstream out;
    for(const auto &t : teamsRepository)
    {
        out<<t->teamInfo()<<std::endl;
    }
    return out.str();
}