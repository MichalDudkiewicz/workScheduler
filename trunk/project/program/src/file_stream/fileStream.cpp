#include "file_stream/fileStream.h"
#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "managers/employeeManager.h"
#include "managers/positionManager.h"
#include "managers/teamManager.h"
#include "managers/workScheduler.h"
#include "positions/dispatcher.h"
#include "positions/doctor.h"
#include "positions/driverN.h"
#include "positions/driverS.h"
#include "positions/medicalRecorder.h"
#include "positions/position.h"
#include "positions/rescuerN.h"
#include "positions/rescuerS.h"
#include "repositories/employeeRepository.h"
#include "repositories/teamRepository.h"
#include "shift/shift.h"
#include "team/team.h"
#include <boost/filesystem.hpp>
#include <iostream>

FileException::FileException(const std::string& message, std::string path)
    : logic_error(message)
    , path(std::move(path))
{
}

std::string FileException::message() const
{
    std::ostringstream out;
    out << what() << " (path: '" << path << "')" << std::endl;
    return out.str();
}

DataException::DataException(const std::string& message,
    const std::string& path)
    : FileException(message, path)
{
}

std::string DataException::message() const
{
    std::ostringstream out;
    out << "Data does not match its corresponding repository in file: "
        << FileException::message();
    return out.str();
}

PathException::PathException(const std::string& message,
    const std::string& path)
    : FileException(message, path)
{
}

void input::loadPositions()
{
    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> rescuerS = std::make_shared<RescuerS>();
    std::shared_ptr<Position> driverS = std::make_shared<DriverS>();
    std::shared_ptr<Position> rescuerN = std::make_shared<RescuerN>();
    std::shared_ptr<Position> driverN = std::make_shared<DriverN>();
    std::shared_ptr<Position> medicalRecorder = std::make_shared<MedicalRecorder>();
    std::shared_ptr<Position> dispatcher = std::make_shared<Dispatcher>();

    PositionManager::getInstance().add(doctor);
    PositionManager::getInstance().add(rescuerS);
    PositionManager::getInstance().add(driverS);
    PositionManager::getInstance().add(rescuerN);
    PositionManager::getInstance().add(driverN);
    PositionManager::getInstance().add(medicalRecorder);
    PositionManager::getInstance().add(dispatcher);
}

void input::employeeRepository(const std::string& path)
{
    std::ifstream empRepoStream;
    empRepoStream.open(path);
    if (!empRepoStream.is_open())
        throw PathException("File of the path doesn't exist", path);
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
                EmployeeManager::getInstance().add(stoi(row[0]), row[1]);
                EmployeeManager::getInstance()
                    .get(stoi(row[0]))
                    ->setHourlyWage(stoi(row[2]));
                EmployeeManager::getInstance()
                    .get(stoi(row[0]))
                    ->getFactor()
                    ->getRules()
                    .setPoints(stoi(row[3]));
                EmployeeManager::getInstance()
                    .get(stoi(row[0]))
                    ->getFactor()
                    ->getRules()
                    .changeType(stoi(row[4]));
                for (const auto& team : TeamManager::getInstance().getAll()) {
                    EmployeeManager::getInstance()
                        .get(stoi(row[0]))
                        ->getFactor()
                        ->getAuthorisation()
                        .addTeam(team);
                }
                EmployeeManager::getInstance()
                    .get(stoi(row[0]))
                    ->getFactor()
                    ->getRules()
                    .setNonresident(boost::lexical_cast<bool>(row[5]));
                std::vector<unsigned int> positions = cellToRawValues<unsigned int>(row[6], ';');
                for (const auto& positionID : positions) {
                    EmployeeManager::getInstance()
                        .get(stoi(row.front()))
                        ->getFactor()
                        ->getAuthorisation()
                        .addPosition(PositionManager::getInstance().get(positionID));
                }
                std::vector<unsigned int> enemies = cellToRawValues<unsigned int>(row[7], ';');
                for (const auto& enemyID : enemies) {
                    if (enemyID < stoul(row[0])) {
                        EmployeeManager::getInstance()
                            .get(stoi(row[0]))
                            ->getFactor()
                            ->getRelationship()
                            .addEnemy(EmployeeManager::getInstance().get(enemyID));
                    }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    empRepoStream.close();
}

void input::teamSchedule(const std::string& path)
{
    std::vector<std::string> row;
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    std::string cell;
    std::ifstream teamScheduleS;
    teamScheduleS.open(path);
    if (!teamScheduleS.is_open())
        throw PathException("File doesn't exist", path);
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
                            TeamManager::getInstance()
                                .get(row.front())
                                ->addShift(shiftHours.front(), shiftHours.back(), i + 1);
                        } catch (teamNotExist& error) {
                            throw DataException("Team Schedule", path);
                        }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamScheduleS.close();
}

void input::teamRepository(const std::string& path)
{
    std::ifstream teamRepositoryS;
    std::vector<std::string> row;
    teamRepositoryS.open(path);
    if (!teamRepositoryS.is_open())
        throw PathException("File doesn't exist", path);
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
                for (auto& positionID : positions) {
                    TeamManager::getInstance()
                        .get(row.front())
                        ->addPosition(PositionManager::getInstance().get(positionID));
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamRepositoryS.close();
}

void input::desiredSchedule(const std::string& path)
{
    std::ifstream desSchedStream;
    desSchedStream.open(path);
    if (!desSchedStream.is_open())
        throw PathException("File doesn't exist", path);
    std::vector<std::string> row;
    unsigned int columnNumber = 0;
    unsigned int rowNumber = 0;
    std::string cell;
    while (desSchedStream.good()) {
        getline(desSchedStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if (columnNumber == calendar::getNumberOfDays() + 2) {
            getline(desSchedStream, cell, '\n');
            columnNumber = 0;
            if (rowNumber > 0) {
                unsigned int day = 0;
                for (auto& c : row) {
                    if (day > 0) {
                        std::vector<std::string> shifts = cellToRawValues<std::string>(c, ';');
                        for (auto& shift : shifts) {
                            std::vector<unsigned int> shiftHours = cellToRawValues<unsigned int>(shift, '-');
                            try {
                                EmployeeManager::getInstance()
                                    .get(stoi(row[0]))
                                    ->getFactor()
                                    ->getAvailability()
                                    .getDesiredSchedule()
                                    .addShift(shiftHours[0], shiftHours[1], day);
                            } catch (EmployeeNotFound& error) {
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

void output::employeeRepository(const std::string& path)
{
    std::ofstream empRepoS;
    empRepoS.open(path);
    if (!empRepoS.is_open())
        throw PathException(
            "The directory folder doesn't exist or You have no permission", path);
    empRepoS << EmployeeManager::getInstance();
    empRepoS.close();
}

void output::desiredSchedule(const std::string& path)
{
    std::ofstream desiredScheduleStream;
    desiredScheduleStream.open(path);
    if (!desiredScheduleStream.is_open())
        throw PathException(
            "The directory folder doesn't exist or You have no permission", path);
    desiredScheduleStream < EmployeeManager::getInstance();
    desiredScheduleStream.close();
}

void output::schedule(const std::string& path)
{
    std::ofstream scheduleStream;
    scheduleStream.open(path);
    if (!scheduleStream.is_open())
        throw PathException(
            "The directory folder doesn't exist or You have no permission", path);
    scheduleStream << WorkScheduler::getInstance();
    scheduleStream.close();
}

void output::teamRepository(const std::string& path)
{
    std::ofstream teamRepositoryStream;
    teamRepositoryStream.open(path);
    if (!teamRepositoryStream.is_open())
        throw PathException(
            "The directory folder doesn't exist or You have no permission", path);
    teamRepositoryStream << TeamManager::getInstance();
    teamRepositoryStream.close();
}

void output::teamSchedule(const std::string& path)
{
    std::ofstream teamScheduleStream;
    teamScheduleStream.open(path);
    if (!teamScheduleStream.is_open())
        throw PathException(
            "The directory folder doesn't exist or You have no permission", path);
    teamScheduleStream < TeamManager::getInstance();
    teamScheduleStream.close();
}

void input::loadDesiredShifts(const std::string& path)
{
    std::ifstream file;
    boost::filesystem::path p = path;
    std::string line;
    std::vector<std::string> row;
    unsigned int numberOfColumns = 7;
    row.reserve(numberOfColumns);
    std::string cell;
    unsigned int employeeID;
    for (boost::filesystem::directory_iterator it{ p };
         it != boost::filesystem::directory_iterator{}; it++) {
        file.open((*it).path().string());
        employeeID = 0;
        while (file.good()) {
            getline(file, line, '\n');
            std::stringstream s(line);
            while (getline(s, cell, ',')) {
                row.push_back(cell);
            }
            if (row[1] == "propozycja 1") {
                employeeID = stoi(row.front());
            } else if (row[1] != "start") {
                for (unsigned long i = 1; i < row.size(); i += 2) {
                    if (!row[i].empty() and !row[i + 1].empty())
                        EmployeeManager::getInstance()
                            .get(employeeID)
                            ->getFactor()
                            ->getAvailability()
                            .getDesiredSchedule()
                            .addShift(stoi(row[i]), stoi(row[i + 1]), stoi(row.front()));
                }
            }
            row.clear();
        }
        file.close();
    }
}
