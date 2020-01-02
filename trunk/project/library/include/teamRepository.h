#ifndef teamRepositoryClass
#define teamRepositoryClass

#include <vector>
#include <memory>
#include <string>

class Team;
typedef std::shared_ptr<Team> teamPtr;
typedef std::vector<teamPtr> teams;

class TeamRepository
{
private:
    teams teamsRepository{};
public:
    void addTeam(const teamPtr&);
    void removeTeam(std::string);
    const teamPtr& getTeamByName(std::string) const;
    const teams& getAll() const;
    std::string repositoryInfo() const;
};

#endif