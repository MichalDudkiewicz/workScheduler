#ifndef sTeamClass
#define sTeamClass

#include "ambulance.h"

class STeam : public Ambulance
{
public:
    STeam()= default;
    ~STeam() override = default;
};

#endif