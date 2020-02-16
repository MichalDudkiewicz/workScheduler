#include "repositories/positionRepository.h"
#include "positions/position.h"
#include <sstream>
#include <algorithm>

PositionRepository &PositionRepository::getInstance() {
    static PositionRepository instance;
    return instance;
}

void PositionRepository::add(const positionPtr &position) {
    positionsRepository.insert(std::make_pair(position->positionID(), position));
}

void PositionRepository::remove(const unsigned int &id) {
    positionsRepository.erase(id);
}

const positionPtr &PositionRepository::get(const unsigned int &id) const {
    try
    {
        return positionsRepository.at(id);
    } catch(std::out_of_range &error)
    {
        throw error;
    }
}

positions PositionRepository::getAll() const {
    positions allPositions;
    for(const auto &position : positionsRepository)
    {
        allPositions.push_front(position.second);
    }
    allPositions.sort(comparePositionID());
    return allPositions;
}

std::string PositionRepository::info() const {
    std::ostringstream out;
    for (const auto &position : positionsRepository) {
        out << position.second->positionInfo() << std::endl;
    }
    return out.str();
}
