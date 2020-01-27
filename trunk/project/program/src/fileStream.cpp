#include "fileStream.h"
#include "employeeManager.h"
#include "teamRepository.h"
#include "employeeRepository.h"
#include "employee.h"
#include "position.h"
#include "shift.h"
#include "employeeType.h"
#include "schedule.h"
#include "teamManager.h"
#include "workScheduler.h"
#include "team.h"
#include "rescuerS.h"
#include "driverS.h"
#include "rescuerN.h"
#include "medicalRecorder.h"
#include "dispatcher.h"
#include "driverN.h"
#include "doctor.h"
#include "medic.h"

FileException::FileException(const std::string &message, std::string path) : logic_error(message), path(std::move(path))
{}

std::string FileException::message() const
{
    std::ostringstream out;
    out << what() << " (path: '" << path << "')" << std::endl;
    return out.str();
}

DataException::DataException(const std::string &message, const std::string &path) : FileException(message, path)
{}

std::string DataException::message() const
{
    std::ostringstream out;
    out << "Data does not match its corresponding repository in file: " << FileException::message();
    return out.str();
}

PathException::PathException(const std::string &message, const std::string &path) : FileException(message, path)
{}


std::vector<positionPtr> input::loadPositions()
{
    std::vector<positionPtr> allPositions;
    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> rescuerS = std::make_shared<RescuerS>();
    std::shared_ptr<Position> driverS = std::make_shared<DriverS>();
    std::shared_ptr<Position> rescuerN = std::make_shared<RescuerN>();
    std::shared_ptr<Position> driverN = std::make_shared<DriverN>();
    std::shared_ptr<Position> medic = std::make_shared<Medic>();
    std::shared_ptr<Position> medicalRecorder = std::make_shared<MedicalRecorder>();
    std::shared_ptr<Position> dispatcher = std::make_shared<Dispatcher>();

    allPositions.push_back(doctor);
    allPositions.push_back(rescuerS);
    allPositions.push_back(driverS);
    allPositions.push_back(rescuerN);
    allPositions.push_back(driverN);
    allPositions.push_back(medic);
    allPositions.push_back(medicalRecorder);
    allPositions.push_back(dispatcher);
    return allPositions;
}

void input::employeeRepository(const std::string &path){
    std::ifstream empRepoStream;
    empRepoStream.open(path);
    if(!empRepoStream.is_open()) throw PathException("File of the path doesn't exist",path);
    std::vector<std::string> row;
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    std::string cell, employeeID;
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
                std::vector<unsigned int> positions = cellToRawValues<unsigned int>(row[6], ';');
                for (auto &positionID : positions) {
                    for (const auto &position : loadPositions()) {
                        if (position->positionID() == positionID) {
                            EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addPosition(position);
                            break;
                        }
                    }
                }
                std::vector<unsigned int> enemies = cellToRawValues<unsigned int>(row[7], ';');
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
}

void input::teamSchedule(const std::string &path) {
    std::vector<std::string> row;
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    std::string cell;
    std::ifstream teamScheduleS;
    teamScheduleS.open(path);
    if(!teamScheduleS.is_open()) throw PathException("File doesn't exist",path);
    columnNumber = 0;
    rowNumber = 0;
    while (teamScheduleS.good()) {
        getline(teamScheduleS, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if (columnNumber == 8) {
            getline(teamScheduleS, cell, '\n');
            columnNumber = 0;
            if (rowNumber > 0) {
                for (unsigned int i = 0; i < 7; ++i) {
                    std::string hoursChain = row[i + 1];
                    std::vector<unsigned int> shiftHours = cellToRawValues<unsigned int>(hoursChain, '-');
                    if (shiftHours.size() > 1)
                        try {
                            TeamManager::getInstance().getTeamByName(row.front())->addShift(shiftHours.front(),
                                                                                            shiftHours.back(), i + 1);
                        }catch(teamNotExist &error){
                            throw DataException("Team Schedule",path);
                        }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamScheduleS.close();
}

void input::teamRepository(const std::string &path) {
    std::ifstream teamRepositoryS;
    std::vector<std::string> row;
    teamRepositoryS.open(path);
    if(!teamRepositoryS.is_open()) throw PathException("File doesn't exist",path);
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    std::string cell;
    while (teamRepositoryS.good()) {
        getline(teamRepositoryS, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if (columnNumber == 2) {
            getline(teamRepositoryS, cell, '\n');
            columnNumber = 0;
            if (rowNumber > 0) {
                TeamManager::getInstance().addTeam(row.front());
                std::vector<unsigned int> positions = cellToRawValues<unsigned int>(row[1], ';');
                for (auto &positionID : positions) {
                    for (const auto &position : loadPositions()) {
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
}

void input::desiredSchedule(const std::string &path) {
    std::ifstream desSchedStream;
    desSchedStream.open(path);
    if(!desSchedStream.is_open()) throw PathException("File doesn't exist",path);
    std::vector<std::string> row;
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    std::string cell;
    while (desSchedStream.good()) {
        getline(desSchedStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if (columnNumber == Schedule::getNumberOfDays() + 2) {
            columnNumber = 0;
            if (rowNumber > 0) {
                unsigned int day = 0;
                for (auto &c : row) {
                    if (day > 0) {
                        std::vector<std::string> shifts = cellToRawValues<std::string>(c, ';');
                        for (auto &shift : shifts) {
                            std::vector<unsigned int> shiftHours = cellToRawValues<unsigned int>(shift, '-');
                            try {
                                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addDesiredShift(shiftHours[0],
                                                                                                              shiftHours[1],
                                                                                                              day);
                            }catch(EmployeeNotFound &error) {
                                throw DataException("Desired Schedule", path);
                            }
                        }
                    }
                    ++day;
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    desSchedStream.close();
}

void output::employeeRepository(const std::string &path) {
    std::ofstream empRepoS;
    empRepoS.open(path);
    if(!empRepoS.is_open()) throw PathException("The directory folder doesn't exist or You have no permission",path);
    empRepoS << EmployeeManager::getInstance();
    empRepoS.close();
}


void output::desiredSchedule(const std::string &path) {
    std::ofstream desiredScheduleStream;
    desiredScheduleStream.open(path);
    if(!desiredScheduleStream.is_open()) throw PathException("The directory folder doesn't exist or You have no permission",path);
    desiredScheduleStream < EmployeeManager::getInstance();
    desiredScheduleStream.close();
}

void output::schedule(const std::string &path) {
    std::ofstream scheduleStream;
    scheduleStream.open(path);
    if(!scheduleStream.is_open()) throw PathException("The directory folder doesn't exist or You have no permission",path);
    scheduleStream << WorkScheduler::getInstance();
    scheduleStream.close();
}

void output::teamRepository(const std::string &path) {
    std::ofstream teamRepositoryStream;
    teamRepositoryStream.open(path);
    if(!teamRepositoryStream.is_open()) throw PathException("The directory folder doesn't exist or You have no permission",path);
    teamRepositoryStream << TeamManager::getInstance();
    teamRepositoryStream.close();
}

void output::teamSchedule(const std::string &path) {
    std::ofstream teamScheduleStream;
    teamScheduleStream.open(path);
    if(!teamScheduleStream.is_open()) throw PathException("The directory folder doesn't exist or You have no permission",path);
    teamScheduleStream < TeamManager::getInstance();
    teamScheduleStream.close();
}
