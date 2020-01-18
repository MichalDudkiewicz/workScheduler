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

template<typename T>
vector<T> cell_to_raw_values(string &chain, char separator)
{
    vector<T> output;
    std::replace(chain.begin(), chain.end(), separator, ' ');
    stringstream stream(chain);
    T temp;
    while (stream >> temp)
        output.push_back(temp);
    return output;
}

int main()
{
    // positions

    std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
    std::shared_ptr<Position> rescuerS=std::make_shared<RescuerS>();
    std::shared_ptr<Position> driverS=std::make_shared<DriverS>();
    std::shared_ptr<Position> rescuerN=std::make_shared<RescuerN>();
    std::shared_ptr<Position> driverN=std::make_shared<DriverN>();
    std::shared_ptr<Position> medic=std::make_shared<Medic>();
    std::shared_ptr<Position> medicalRecorder=std::make_shared<MedicalRecorder>();
    std::shared_ptr<Position> dispatcher=std::make_shared<Dispatcher>();

    std::vector<positionPtr> allPositions;
    allPositions.push_back(doctor);
    allPositions.push_back(rescuerS);
    allPositions.push_back(driverS);
    allPositions.push_back(rescuerN);
    allPositions.push_back(driverN);
    allPositions.push_back(medic);
    allPositions.push_back(medicalRecorder);
    allPositions.push_back(dispatcher);

    //employee Repository input

    ifstream empRepoStream;
    empRepoStream.open("../../../dataset/input/admin/employeeRepository.csv");
    vector<string> row;
    unsigned int columnNumber=0;
    unsigned int rowNumber=0;
    string cell,employeeID;
    while(empRepoStream.good())
    {
        getline(empRepoStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if(columnNumber==8)
        {
            columnNumber=0;
            if(rowNumber>0)
            {
                EmployeeManager::getInstance().addEmployee(stoi(row[0]),row[1]);
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->setHourlyWage(stoi(row[2]));
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->setPoints(stoi(row[3]));
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->changeType(stoi(row[4]));
                EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->setNonresident(boost::lexical_cast<bool>(row[5]));
                vector<unsigned int> positions=cell_to_raw_values<unsigned int>(row[6],';');
                for(auto &positionID : positions)
                {
                    for(const auto &position : allPositions)
                    {
                        if(position->positionID()==positionID)
                        {
                            EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addPosition(position);
                            break;
                        }
                    }
                }
                vector<unsigned int> enemies=cell_to_raw_values<unsigned int>(row[7],';');
                for(const auto &enemyID : enemies)
                {
                    if(enemyID<stoul(row[0]))
                    {
                        EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addEnemy(EmployeeManager::getInstance().getEmployeeByID(enemyID));
                    }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    empRepoStream.close();


    //desired Schedule input

    ifstream desSchedStream;
    desSchedStream.open("../../../dataset/input/employees/desiredSchedules.csv");
    row.clear();
    columnNumber=0;
    rowNumber=0;
    while(desSchedStream.good())
    {
        getline(desSchedStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if(columnNumber==Schedule::getNumberOfDays()+2)
        {
            columnNumber=0;
            if(rowNumber>0)
            {
                unsigned int day=0;
                for(auto &c : row)
                {
                    if(day>0)
                    {
                        vector<string> shifts=cell_to_raw_values<string>(c,';');
                        for(auto &shift : shifts)
                        {
                            vector<unsigned int> shiftHours=cell_to_raw_values<unsigned int>(shift,'-');
                            EmployeeManager::getInstance().getEmployeeByID(stoi(row[0]))->addDesiredShift(shiftHours[0],shiftHours[1],day);
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


    //team repository input

    ifstream teamRepositoryS;
    teamRepositoryS.open("../../../dataset/input/admin/teamRepository.csv");
    row.clear();
    columnNumber=0;
    rowNumber=0;
    while(teamRepositoryS.good())
    {
        getline(teamRepositoryS, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if(columnNumber==2)
        {
            getline(teamRepositoryS, cell, '\n');
            columnNumber=0;
            if(rowNumber>0)
            {
                TeamManager::getInstance().addTeam(row.front());
                vector<unsigned int> positions=cell_to_raw_values<unsigned int>(row[1],';');
                for(auto &positionID : positions)
                {
                    for(const auto &position : allPositions)
                    {
                        if(position->positionID()==positionID)
                        {
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

    ifstream teamScheduleS;
    teamScheduleS.open("../../../dataset/input/admin/teamSchedule.csv");
    row.clear();
    columnNumber=0;
    rowNumber=0;

    while(teamScheduleS.good())
    {
        getline(teamScheduleS, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if(columnNumber==8)
        {
            getline(teamScheduleS, cell, '\n');
            columnNumber=0;
            if(rowNumber>0)
            {
                for(unsigned int i=0;i<7;++i)
                {
                    string hoursChain = row[i+1];
                    vector<unsigned int> shiftHours=cell_to_raw_values<unsigned int>(hoursChain,'-');
                    if(shiftHours.size()>1)
                        TeamManager::getInstance().getTeamByName(row.front())->addShift(shiftHours.front(),shiftHours.back(),i+1);
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamRepositoryS.close();


    //CREATING AND DISPLAYING SCHEDULE
    WorkScheduler::getInstance().createSchedule();
    cout<<WorkScheduler::getInstance().scheduleInfo();

    //SAVING OUTPUT FILES
    output::employeeRepository("../../../dataset/input/admin/employeeRepository.csv");
    output::desiredSchedule("../../../dataset/input/employees/desiredSchedules.csv");
    output::schedule("../../../dataset/output/schedule.csv");
    output::teamRepository("../../../dataset/input/admin/teamRepository.csv");
    output::teamSchedule("../../../dataset/input/admin/teamSchedule.csv");
    return 0;
}
