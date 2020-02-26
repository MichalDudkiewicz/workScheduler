#ifndef doctorClass
#define doctorClass

#include "sTeam.h"

class Doctor : public STeam {
public:
    Doctor() = default;
    ~Doctor() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
    std::string shortcut() const override;
};

#endif