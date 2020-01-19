#include "teamRepository.h"
#include "team.h"
#include <sstream>
#include <random>
#include "shift.h"

teamNotExist::teamNotExist(const std::string &message)
        : logic_error(message)
{}
teamWithThisNameExists::teamWithThisNameExists(const std::string &message)
        : logic_error(message)
{}
void TeamRepository::checkTeamName(std::string name){
    int i = 0;
    bool flag = false;
    while(i<(int)teamsRepository.size() && !flag){
        if(teamsRepository[i]->getName()==name){
            flag = true;
            throw teamWithThisNameExists();
        }
        i++;
    }
}

TeamRepository& TeamRepository::getInstance()
{
    static TeamRepository instance;
    return instance;
}

void TeamRepository::add(const teamPtr &team)
{
    checkTeamName(team->getName());
    teamsRepository.push_back(team);
}

void TeamRepository::add(const std::string &name)
{
    teamPtr team = std::make_shared<Team>(name);
    checkTeamName(name);
    teamsRepository.push_back(team);
}

void TeamRepository::remove(const std::string &name)
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

const teamPtr& TeamRepository::get(const std::string &name) const
{
    for(const auto &t : teamsRepository)
    {
        if(t->getName()==name)
        {
            return t;
        }
    }
    throw teamNotExist();
}

const teams& TeamRepository::getAll() const
{
    return teamsRepository;
}

std::string TeamRepository::info() const
{
    std::ostringstream out;
    for(const auto &t : teamsRepository)
    {
        out<<t->teamInfo()<<std::endl;
    }
    return out.str();
}


