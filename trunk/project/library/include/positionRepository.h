#ifndef positionRepositoryClass
#define positionRepositoryClass

#include "repository.h"
#include <unordered_map>

class Position;
typedef std::shared_ptr<Position> positionPtr;
typedef std::vector<positionPtr> positions;

class PositionRepository : public Repository<Position, unsigned int>{
private:
    std::unordered_map<unsigned int, positionPtr> positionsRepository{};
    PositionRepository()=default;
public:
    static PositionRepository& getInstance();
    PositionRepository(const PositionRepository&)=delete;
    void operator=(const PositionRepository&)=delete;
    void add(const positionPtr&) override;
    void remove(const unsigned int&) override;
    const positionPtr& get(const unsigned int&) const override;
    positions getAll() const override;
    std::string info() const override;
};


#endif
