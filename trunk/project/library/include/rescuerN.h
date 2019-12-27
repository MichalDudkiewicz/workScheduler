#ifndef rescuerNClass
#define rescuerNClass

#include "nTeam.h"

class RescuerN : public NTeam
{
public:
    RescuerN() = default;
    ~RescuerN() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
};

#endif