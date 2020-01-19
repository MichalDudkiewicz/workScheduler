#ifndef rescuerSClass
#define rescuerSClass

#include "sTeam.h"

class RescuerS : public STeam{
public:
    RescuerS() = default;
    ~RescuerS() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
    std::string shortcut() const override;
};

#endif