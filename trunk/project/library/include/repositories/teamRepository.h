#ifndef teamRepositoryClass
#define teamRepositoryClass

#include "other/typeDefinitions.h"
#include "repositories/repository.h"
#include <unordered_map>

class teamNotExist : public std::logic_error
{
public:
  explicit teamNotExist(const std::string& message = "Team doesn't exist.");
};
class teamWithThisNameExists : public std::logic_error
{
public:
  explicit teamWithThisNameExists(
    const std::string& message = "Team with this name already exists.");
};

class TeamRepository : Repository<Team, std::string>
{
private:
  std::unordered_map<std::string, teamPtr> teamsRepository{};
  TeamRepository() = default;
  void checkTeamName(const std::string&);

public:
  static TeamRepository& getInstance();
  TeamRepository(const TeamRepository&) = delete;
  void operator=(const TeamRepository&) = delete;
  void add(const teamPtr&) override;
  void add(const std::string&);
  void remove(const std::string&) override;
  const teamPtr& get(const std::string&) const override;
  teams getAll() const override;
  std::string info() const override;
};

#endif