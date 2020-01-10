#ifndef teamManagerClass
#define teamManagerClass

#include <memory>
#include <string>

class Team;
typedef std::shared_ptr<Team> teamPtr;

class TeamManager
{
private:
    TeamManager()=default;
public:
    static TeamManager& getInstance();
    TeamManager(const TeamManager&)=delete;
    void operator=(const TeamManager&)=delete;
    static void addTeam(const std::string&);
    static void removeTeam(const std::string&);
    const teamPtr& getTeamByName(const std::string&) const;
    std::string repositoryInfo() const;
};

#endif