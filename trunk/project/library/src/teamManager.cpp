#include "teamManager.h"
#include "teamRepository.h"
#include "position.h"
#include "team.h"
#include "shift.h"

TeamManager &TeamManager::getInstance() {
    static TeamManager instance;
    return instance;
}

void TeamManager::addTeam(const std::string &name) {
    TeamRepository::getInstance().add(name);
}

void TeamManager::removeTeam(const std::string &name) {
    TeamRepository::getInstance().remove(name);
}

const teamPtr &TeamManager::getTeamByName(const std::string &name) const {
    return TeamRepository::getInstance().get(name);
}

std::string TeamManager::repositoryInfo() const {
    return TeamRepository::getInstance().info();
}

const std::vector<teamPtr> &TeamManager::getAll() const {
    return TeamRepository::getInstance().getAll();
}

std::ofstream &operator<<(std::ofstream &output, const TeamManager &manager) {
    output << "team,positions," << std::endl;
    for (const auto &team : manager.getAll()) {
        output << team->getName() << ",";
        for (const auto &positon : team->getPositions()) {
            output << positon->positionID() << ";";
        }
        output << "," << std::endl;
    }
    return output;
}

std::ofstream &operator<(std::ofstream &output, const TeamManager &manager) {
    output << "team\\day,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday," << std::endl;
    for (const auto &team : manager.getAll()) {
        output << team->getName() << ",";
        for (const auto &shift : team->getShifts()) {
            if (shift->isDayOff())
                output << "X,";
            else
                output << shift->getStartHour() << "-" << shift->getEndHour() << ",";
        }
        output << std::endl;
    }
    return output;
}
