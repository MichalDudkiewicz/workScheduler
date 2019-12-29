#include "teamRepository.h"
#include "team.h"
#include <sstream>

void TeamRepository::addTeam(const teamPtr &team)
{
    teamsRepository.push_back(team);
}

void TeamRepository::removeTeam(std::string name)
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

const teamPtr& TeamRepository::getTeamByName(std::string name) const
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