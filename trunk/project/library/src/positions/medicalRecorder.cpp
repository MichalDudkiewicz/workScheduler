#include "positions/medicalRecorder.h"

std::string MedicalRecorder::positionInfo() const
{
    return "medical recorder";
}

unsigned int MedicalRecorder::positionID() const
{
    return 7;
}

std::string MedicalRecorder::shortcut() const
{
    return "RE";
}