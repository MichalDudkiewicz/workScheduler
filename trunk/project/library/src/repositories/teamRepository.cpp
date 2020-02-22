#include "repositories/teamRepository.h"
#include "shift/shift.h"
#include "team/team.h"
#include <sstream>

teamNotExist::teamNotExist(const std::string& message)
  : logic_error(message)
{}

teamWithThisNameExists::teamWithThisNameExists(const std::string& message)
  : logic_error(message)
{}

void
TeamRepository::checkTeamName(const std::string& name)
{
  auto search = teamsRepository.find(name);
  if (search != teamsRepository.end()) {
    throw teamWithThisNameExists();
  } else {
    return;
  }
}

TeamRepository&
TeamRepository::getInstance()
{
  static TeamRepository instance;
  return instance;
}

void
TeamRepository::add(const teamPtr& team)
{
  checkTeamName(team->getName());
  teamsRepository.insert(std::make_pair(team->getName(), team));
}

void
TeamRepository::add(const std::string& name)
{
  checkTeamName(name);
  teamsRepository.emplace(std::make_pair(name, std::make_shared<Team>(name)));
}

void
TeamRepository::remove(const std::string& name)
{
  teamsRepository.erase(name);
}

const teamPtr&
TeamRepository::get(const std::string& name) const
{
  try {
    return teamsRepository.at(name);
  } catch (std::out_of_range& error) {
    throw teamNotExist();
  }
}

teams
TeamRepository::getAll() const
{
  teams allTeams;
  for (const auto& team : teamsRepository) {
    allTeams.push_front(team.second);
  }
  return allTeams;
}

std::string
TeamRepository::info() const
{
  std::ostringstream out;
  for (const auto& team : teamsRepository) {
    out << team.second->teamInfo() << std::endl;
  }
  return out.str();
}
