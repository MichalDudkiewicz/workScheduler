#ifndef positionManagerClass
#define positionManagerClass

#include "manager.h"

class Position;
typedef std::shared_ptr<Position> positionPtr;
typedef std::list<positionPtr> positions;

class PositionManager : public Manager<Position, unsigned int> {
private:
    PositionManager()=default;
public:
    static PositionManager& getInstance();
    PositionManager(const PositionManager&)=delete;
    void operator=(const PositionManager&)=delete;
    static void add(const positionPtr &position);
    void remove(const unsigned int&) override;
    std::string info() const override;
    const positionPtr& get(const unsigned int &) const override;
    std::list<positionPtr> getAll() const override;
};


#endif
