#ifndef teamRepositoryClass
#define teamRepositoryClass

#include <vector>
#include <memory>
#include <string>

class TeamNotExist: public std::logic_error
{
public:
    explicit TeamNotExist(const std::string &message = "Team doesn't exist.");
};

class Team;
typedef std::shared_ptr<Team> teamPtr;
typedef std::vector<teamPtr> teams;

class TeamRepository
{
private:
    teams teamsRepository{};
    TeamRepository()=default;
public:
    static TeamRepository& getInstance();
    TeamRepository(const TeamRepository&)=delete;
    void operator=(const TeamRepository&)=delete;
    void addTeam(const teamPtr&);
    void addTeam(const std::string&);
    void removeTeam(const std::string&);
    const teamPtr& getTeamByName(const std::string&) const;
    const teams& getAll() const;
    std::string repositoryInfo() const;
};

#endif