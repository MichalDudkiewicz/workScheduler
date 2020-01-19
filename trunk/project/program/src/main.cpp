#include <iostream>
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include <memory>
#include "employeeManager.h"
#include "teamManager.h"
#include "rescuerS.h"
#include "driverS.h"
#include "rescuerN.h"
#include "driverN.h"
#include "medicalRecorder.h"
#include "dispatcher.h"
#include "shift.h"
#include <fstream>
#include "employeeType.h"
#include "schedule.h"
#include <boost/lexical_cast.hpp>
#include "workScheduler.h"
#include "fileStream.h"

using namespace std;

int main() {
    // positions

    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> rescuerS = std::make_shared<RescuerS>();
    std::shared_ptr<Position> driverS = std::make_shared<DriverS>();
    std::shared_ptr<Position> rescuerN = std::make_shared<RescuerN>();
    std::shared_ptr<Position> driverN = std::make_shared<DriverN>();
    std::shared_ptr<Position> medic = std::make_shared<Medic>();
    std::shared_ptr<Position> medicalRecorder = std::make_shared<MedicalRecorder>();
    std::shared_ptr<Position> dispatcher = std::make_shared<Dispatcher>();

    input::allPositions.push_back(doctor);
    input::allPositions.push_back(rescuerS);
    input::allPositions.push_back(driverS);
    input::allPositions.push_back(rescuerN);
    input::allPositions.push_back(driverN);
    input::allPositions.push_back(medic);
    input::allPositions.push_back(medicalRecorder);
    input::allPositions.push_back(dispatcher);

    //employee Repository input
    ifstream empRepoStream;
    empRepoStream.open("../../../dataset/input/admin/employeeRepository.csv");
    vector<string> row;
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    string cell, employeeID;
    while (empRepoStream.good()) {
        getline(empRepoStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if (columnNumber == 8) {
            columnNumber = 0;
            if (rowNumber > 0) {
                EmployeeManager::getInstance().addEmployee(stoi(row[0]), row[1]);
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->setHourlyWage(stoi(row[2]));
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->setPoints(stoi(row[3]));
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->changeType(stoi(row[4]));
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->setNonresident(
                        boost::lexical_cast<bool>(row[5]));
                vector<unsigned int> positions = cellToRawValues<unsigned int>(row[6], ';');
                for (auto &positionID : positions) {
                    for (const auto &position : input::allPositions) {
                        if (position->positionID() == positionID) {
                            EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addPosition(position);
                            break;
                        }
                    }
                }
                vector<unsigned int> enemies = cellToRawValues<unsigned int>(row[7], ';');
                for (const auto &enemyID : enemies) {
                    if (enemyID < stoul(row[0])) {
                        EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addEnemy(
                                EmployeeManager::getInstance().getEmployeeByID(enemyID));
                    }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    empRepoStream.close();

    //desired Schedule input
    input::desiredSchedule("../../../dataset/input/employees/desiredSchedules.csv");

    //team repository input
    ifstream teamRepositoryS;
    teamRepositoryS.open("../../../dataset/input/admin/teamRepository.csv");
    row.clear();
    columnNumber = 0;
    rowNumber = 0;
    while (teamRepositoryS.good()) {
        getline(teamRepositoryS, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if (columnNumber == 2) {
            getline(teamRepositoryS, cell, '\n');
            columnNumber = 0;
            if (rowNumber > 0) {
                TeamManager::getInstance().addTeam(row.front());
                vector<unsigned int> positions = cellToRawValues<unsigned int>(row[1], ';');
                for (auto &positionID : positions) {
                    for (const auto &position : input::allPositions) {
                        if (position->positionID() == positionID) {
                            TeamManager::getInstance().getAll().back()->addPosition(position);
                            break;
                        }
                    }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamRepositoryS.close();

    // team schedule input
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
    return 0;
}
