#ifndef teamManagerClass
#define teamManagerClass

#include "manager.h"
#include "other/typeDefinitions.h"
#include <fstream>

class TeamManager : public Manager<Team, std::string>
{
private:
  TeamManager() = default;

public:
  static TeamManager& getInstance();
  TeamManager(const TeamManager&) = delete;
  void operator=(const TeamManager&) = delete;
  static void addTeam(const std::string&);
  void remove(const std::string&) override;
  const teamPtr& get(const std::string&) const override;
  std::string info() const override;
  std::list<teamPtr> getAll() const override;
  friend std::ofstream& operator<<(std::ofstream& output,
                                   const TeamManager& manager);
  friend std::ofstream& operator<(std::ofstream& output,
                                  const TeamManager& manager);
};

#endif