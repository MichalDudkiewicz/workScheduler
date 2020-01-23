#include <iostream>
#include "workScheduler.h"
#include "fileStream.h"

using namespace std;

int main() {
    try {
        //INPUT CSV FILES
        input::employeeRepository("../../../dataset/input/admin/employeeRepository.csv");
        input::desiredSchedule("../../../dataset/input/employees/desiredSchedules.csv");
        input::teamRepository("../../../dataset/input/admin/teamRepository.csv");
        input::teamSchedule("../../../dataset/input/admin/teamSchedule.csv");

        //CREATING AND DISPLAYING SCHEDULE
        WorkScheduler::getInstance().createSchedule();
        cout << WorkScheduler::getInstance().scheduleInfo();

        //SAVING OUTPUT FILES
        output::employeeRepository("../../../dataset/input/admin/employeeRepository.csv");
        output::desiredSchedule("../../../dataset/input/employees/desiredSchedules.csv");
        output::schedule("../../../dataset/output/schedule.csv");
        output::teamRepository("../../../dataset/input/admin/teamRepository.csv");
        output::teamSchedule("../../../dataset/input/admin/teamSchedule.csv");
    }catch(FileException &error){
        cout<<error.message();
    }
    return 0;
}
