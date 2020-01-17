#include <iostream>
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include <memory>
#include "employeeRepository.h"
#include "teamRepository.h"
#include "finalSchedule.h"
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

using namespace std;

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
                EmployeeRepository::getInstance().addEmployee(stoi(row[0]),row[1]);
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->setHourlyWage(stoi(row[2]));
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->setPoints(stoi(row[3]));
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->changeType(stoi(row[4]));
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->setNonresident(boost::lexical_cast<bool>(row[5]));

                vector<unsigned int> positions;
                std::replace(row[6].begin(), row[6].end(), ';', ' ');
                stringstream p(row[6]);
                unsigned int tempP;
                while (p >> tempP)
                    positions.push_back(tempP);
                for(auto &positionID : positions)
                {
                    for(const auto &position : allPositions)
                    {
                        if(position->positionID()==positionID)
                        {
                            EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->addPosition(position);
                            break;
                        }
                    }
                }

                vector<int> enemies;
                std::replace(row[7].begin(), row[7].end(), ';', ' ');
                stringstream e(row[7]);
                int tempE;
                while (e >> tempE)
                    enemies.push_back(tempE);
                for(const auto &enemyID : enemies)
                {
                    if(enemyID<stoi(row[0]))
                    {
                        EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->addEnemy(EmployeeRepository::getInstance().getEmployeeByID(enemyID));
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
                        vector<string> shifts;
                        std::replace(c.begin(), c.end(), ';', ' ');
                        stringstream p(c);
                        string tempP;
                        while (p >> tempP)
                        {
                            shifts.push_back(tempP);
                        }
                        for(auto &shift : shifts)
                        {

                            vector<unsigned int> shiftHours;
                            std::replace(shift.begin(), shift.end(), '-', ' ');
                            stringstream s(shift);
                            unsigned int tempS;
                            while (s >> tempS)
                            {
                                shiftHours.push_back(tempS);
                            }
                            EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->addDesiredShift(shiftHours[0],shiftHours[1],day);
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
                TeamRepository::getInstance().addTeam(row.front());
                vector<unsigned int> positions;
                std::replace(row[1].begin(), row[1].end(), ';', ' ');
                stringstream p(row[1]);
                unsigned int tempP;
                while (p >> tempP)
                    positions.push_back(tempP);
                for(auto &positionID : positions)
                {
                    for(const auto &position : allPositions)
                    {
                        if(position->positionID()==positionID)
                        {
                            TeamRepository::getInstance().getAll().back()->addPosition(position);
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

                    vector<unsigned int> shiftHours;
                    string hoursChain = row[i+1];
                    std::replace(hoursChain.begin(), hoursChain.end(), '-', ' ');
                    stringstream p(hoursChain);
                    unsigned int tempP;
                    while (p >> tempP)
                    {
                        shiftHours.push_back(tempP);
                    }
                    if(shiftHours.size()>1)
                        TeamRepository::getInstance().getTeamByName(row.front())->addShift(shiftHours.front(),shiftHours.back(),i+1);
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamRepositoryS.close();


//schedule
    WorkScheduler::getInstance().createSchedule();
    cout<<WorkScheduler::getInstance().scheduleInfo();

//    output employeeRepository
    ofstream empRepoS;
    empRepoS.open("../../../dataset/input/admin/employeeRepository.csv");
    empRepoS<<"ID,name,wage,points,priority,nonresident,positions,enemies,"<<endl;
    for(const auto &employee : EmployeeRepository::getInstance().getAll())
    {
        empRepoS<<employee->getId()<<","<<employee->getName()<<","<<employee->getHourlyWage()<<","<<employee->getPoints()<<","<<employee->getType()->getPriority()<<","<<employee->isNonresident()<<",";
        for(const auto &position : employee->getPositions())
        {
            empRepoS<<position->positionID()<<";";
        }
        empRepoS<<",";
        for(const auto &enemy : employee->getMyEnemies())
        {
            empRepoS<<enemy->getId()<<";";
        }
        empRepoS<<",";
        empRepoS<<endl;
    }
    empRepoS.close();

//    output desiredSchedules
    ofstream desiredScheduleStream;
    desiredScheduleStream.open("../../../dataset/input/employees/desiredSchedules.csv");
    desiredScheduleStream << "ID\\day" << ",";
    for(unsigned int day=1;day<=Schedule::getNumberOfDays();++day)
    {
        desiredScheduleStream << day << ",";
    }
    desiredScheduleStream << "1" << "," << endl;
    for(const auto &employee : EmployeeRepository::getInstance().getAll())
    {
        desiredScheduleStream << employee->getId() << ",";
        for(const auto &shifts : employee->getDesiredSchedule())
        {
            for(const auto &shift : shifts)
            {
                desiredScheduleStream << shift->getStartHour() << "-" << shift->getEndHour() << ";";
            }
            desiredScheduleStream << ",";
        }
        desiredScheduleStream << endl;
    }
    desiredScheduleStream.close();


    // schedule output
    ofstream scheduleStream;
    scheduleStream.open("../../../dataset/output/schedule.csv");
    unsigned int numberOfColumns = 1;
    for(const auto &team : TeamRepository::getInstance().getAll())
    {
        numberOfColumns+=team->getPositions().size();
    }
    for(unsigned int i=0;i<numberOfColumns/2-3;++i)
    {
        scheduleStream<<",";
    }
    scheduleStream<<Schedule::scheduleDate()<<" work schedule";
    for(unsigned int i=numberOfColumns/2-3;i<numberOfColumns;++i)
    {
        scheduleStream<<",";
    }
    scheduleStream<<endl<<",";
    for(const auto &team : TeamRepository::getInstance().getAll())
    {
        for(unsigned long i=0;i<team->getPositions().size()/2;++i)
        {
            scheduleStream<<",";
        }
        scheduleStream<<team->getName();
        for(unsigned long i=team->getPositions().size()/2;i<team->getPositions().size();++i)
        {
            scheduleStream<<",";
        }
    }
    scheduleStream<<endl<<",";
    for(const auto &team : TeamRepository::getInstance().getAll())
    {
        for(const auto &position : team->getPositions())
        {
            scheduleStream<<position->shortcut()<<",";
        }
    }
    scheduleStream<<endl;
    unsigned int d = 1;
    for(const auto &day : WorkScheduler::getInstance().getSchedule())
    {
        if(d>Schedule::getNumberOfDays())
            d=1;
        scheduleStream<<d<<",";
        for(const auto &team : day)
        {
            for(const auto &position : team)
            {
                if(position.empty())
                    scheduleStream<<",";
                else
                {
                    scheduleStream<<position.front()->getId()<<",";
                }
            }
        }
        scheduleStream<<endl;
        ++d;
    }
    scheduleStream.close();



    // team REpo output

    ofstream teamRepositoryStream;
    teamRepositoryStream.open("../../../dataset/input/admin/teamRepository.csv");
    teamRepositoryStream<<"team,positions,"<<endl;
    for(const auto &team : TeamRepository::getInstance().getAll())
    {
        teamRepositoryStream<<team->getName()<<",";
        for(const auto &positon : team->getPositions())
        {
            teamRepositoryStream<<positon->positionID()<<";";
        }
        teamRepositoryStream<<","<<endl;
    }
    teamRepositoryStream.close();

    // team schedule output

    ofstream teamScheduleStream;
    teamScheduleStream.open("../../../dataset/input/admin/teamSchedule.csv");
    teamScheduleStream<<"team\\day,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday,"<<endl;
    for(const auto &team : TeamRepository::getInstance().getAll())
    {
        teamScheduleStream<<team->getName()<<",";
        for(const auto &shift : team->getShifts())
        {
            if(shift->isDayOff())
                teamScheduleStream<<"X,";
            else
                teamScheduleStream<<shift->getStartHour()<<"-"<<shift->getEndHour()<<",";
        }
        teamScheduleStream<<endl;
    }
    teamScheduleStream.close();

    return 0;
}
