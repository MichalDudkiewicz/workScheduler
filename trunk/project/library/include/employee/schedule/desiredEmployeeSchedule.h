#ifndef WORKSCHEDULER_DESIREDEMPLOYEESCHEDULE_H
#define WORKSCHEDULER_DESIREDEMPLOYEESCHEDULE_H

#include "utils/schedule.h"
#include "utils/typeDefinitions.h"
#include <string>

class DesiredEmployeeSchedule : public Schedule<shifts> {
    void addShift(shiftPtr&);

public:
    void addShift(unsigned int, unsigned int, unsigned int);
    void removeShift(unsigned int, unsigned int);
    std::string scheduleInfo() const override;
};

#endif //WORKSCHEDULER_DESIREDEMPLOYEESCHEDULE_H
