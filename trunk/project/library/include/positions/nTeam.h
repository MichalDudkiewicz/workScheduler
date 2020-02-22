#ifndef nTeamClass
#define nTeamClass

#include "ambulance.h"

class NTeam : public Ambulance
{
public:
  NTeam() = default;
  ~NTeam() override = default;
};

#endif