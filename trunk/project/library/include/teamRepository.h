#ifndef teamRepositoryClass
#define teamRepositoryClass

#include <vector>
#include <memory>
#include <string>
#include "repository.h"

class TeamNotExist: public std::logic_error
{
public:
    explicit TeamNotExist(const std::string &message = "Team doesn't exist.");
};

class Team;
typedef std::shared_ptr<Team> teamPtr;
typedef std::vector<teamPtr> teams;

class TeamRepository : Repository<Team,std::string>
{
private:
    teams teamsRepository{};
    TeamRepository()=default;
public:
    static TeamRepository& getInstance();
    TeamRepository(const TeamRepository&)=delete;
    void operator=(const TeamRepository&)=delete;
    void add(const teamPtr&) override;
    void add(const std::string&);
    void remove(const std::string&) override;
    const teamPtr& get(const std::string&) const override;
    const teams& getAll() const override;
    std::string info() const override;
};

#endif