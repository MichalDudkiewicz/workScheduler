#ifndef teamManagerClass
#define teamManagerClass

#include <memory>
#include <string>

class TeamRepository;
class Team;
typedef std::shared_ptr<Team> teamPtr;

class TeamManager
{
private:
    TeamRepository* teamRepository;
public:
    TeamManager();
    void addTeam(const std::string&);
    void removeTeam(const std::string&);
    const teamPtr& getTeamByName(const std::string&) const;
    std::string repositoryInfo() const;
};

#endif