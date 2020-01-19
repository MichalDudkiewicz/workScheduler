#ifndef ambulanceClass
#define ambulanceClass

#include "position.h"

class Ambulance : public Position{
public:
    Ambulance()= default;
    ~Ambulance() override= default;
};

#endif