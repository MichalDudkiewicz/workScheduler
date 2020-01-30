#include "positionManager.h"
#include "positionRepository.h"

PositionManager &PositionManager::getInstance() {
    static PositionManager instance;
    return instance;
}

void PositionManager::add(const positionPtr &position) {
    PositionRepository::getInstance().add(position);
}

void PositionManager::remove(const unsigned int &id) {
    PositionManager::getInstance().remove(id);
}

std::string PositionManager::info() const {
    return PositionRepository::getInstance().info();
}

const positionPtr &PositionManager::get(const unsigned int &id) const {
    return PositionRepository::getInstance().get(id);
}

std::vector<positionPtr> PositionManager::getAll() const {
    return PositionRepository::getInstance().getAll();
}
