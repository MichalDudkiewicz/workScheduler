#ifndef medicalRecorderClass
#define medicalRecorderClass

#include "position.h"

class MedicalRecorder : public Position {
public:
    MedicalRecorder() = default;
    ~MedicalRecorder() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
    std::string shortcut() const override;
};

#endif