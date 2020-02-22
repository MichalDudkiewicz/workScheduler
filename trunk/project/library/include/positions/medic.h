#ifndef medicClass
#define medicClass

#include "position.h"

class Medic : public Position
{
public:
  Medic() = default;
  ~Medic() override = default;
  std::string positionInfo() const override;
  unsigned int positionID() const override;
  std::string shortcut() const override;
};

#endif