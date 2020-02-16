#ifndef WORKSCHEDULER_AUTHORISATION_H
#define WORKSCHEDULER_AUTHORISATION_H

#include "typeDefinitions.h"

namespace authorisation {
    bool isAuthorised(const employeePtr &employee, const positionPtr &position, const teamPtr &team);

    bool positionMatch(const employeePtr &employee, const positionPtr &position);

    bool teamMatch(const employeePtr &employee, const teamPtr &team);
}
#endif //WORKSCHEDULER_AUTHORISATION_H
