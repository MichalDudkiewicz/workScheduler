#include <iostream>
#include "managers/workScheduler.h"
#include "file_stream/fileStream.h"
#include <chrono>

using namespace std;

int main() {
    auto start = chrono::steady_clock::now();
    input::loadPositions();
    try {
        //INPUT CSV FILES
        input::teamRepository("../../../dataset/input/admin/teamRepository.csv");
        input::teamSchedule("../../../dataset/input/admin/teamSchedule.csv");
        input::employeeRepository("../../../dataset/input/admin/employeeRepository.csv");
        input::desiredSchedule("../../../dataset/input/employees/desiredSchedules.csv");

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
    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in nanoseconds : "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " ns" << endl;

    cout << "Elapsed time in microseconds : "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs" << endl;

    cout << "Elapsed time in milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;

    cout << "Elapsed time in seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count()
         << " sec";
    return 0;
}
