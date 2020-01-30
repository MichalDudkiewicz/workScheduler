#ifndef teamManagerClass
#define teamManagerClass

#include <fstream>
#include "manager.h"

class Team;
typedef std::shared_ptr<Team> teamPtr;

class TeamManager : public Manager<Team, std::string>{
private:
    TeamManager()=default;
public:
    static TeamManager& getInstance();
    TeamManager(const TeamManager&)=delete;
    void operator=(const TeamManager&)=delete;
    static void addTeam(const std::string&);
    void remove(const std::string&) override;
    const teamPtr& get(const std::string&) const override;
    std::string info() const override;
    std::vector<teamPtr> getAll() const override;
    friend std::ofstream& operator<<(std::ofstream& output, const TeamManager& manager);
    friend std::ofstream& operator<(std::ofstream& output, const TeamManager& manager);
};

#endif