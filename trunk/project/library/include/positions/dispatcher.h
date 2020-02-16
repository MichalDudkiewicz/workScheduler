#ifndef dispatcherClass
#define dispatcherClass

#include "position.h"

class Dispatcher : public Position{
public:
    Dispatcher() = default;
    ~Dispatcher() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
    std::string shortcut() const override;
};

#endif