#include "fileStream.h"
#include <sstream>
#include "employeeManager.h"
#include <fstream>
#include "employee.h"
#include "position.h"
#include "shift.h"
#include "employeeType.h"
#include "schedule.h"
#include "teamManager.h"
#include "workScheduler.h"
#include "team.h"


void input::teamSchedule(const std::string &path)
{
    std::vector<std::string> row;
    unsigned int columnNumber=0;
    unsigned int rowNumber=0;
    std::string cell;
    std::ifstream teamScheduleS;
    teamScheduleS.open(path);
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
                    std::string hoursChain = row[i+1];
                    std::vector<unsigned int> shiftHours=cellToRawValues<unsigned int>(hoursChain,'-');
                    if(shiftHours.size()>1)
                        TeamManager::getInstance().getTeamByName(row.front())->addShift(shiftHours.front(),shiftHours.back(),i+1);
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    teamScheduleS.close();
}

void input::teamRepository(const std::string &path)
{
    std::ifstream teamRepositoryS;
    std::vector<std::string> row;
    teamRepositoryS.open(path);
    unsigned int columnNumber=0;
    unsigned int rowNumber=0;
    std::string cell;
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
                std::vector<unsigned int> positions=cellToRawValues<unsigned int>(row[1],';');
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
}

void input::desiredSchedule(const std::string &path)
{
    std::ifstream desSchedStream;
    desSchedStream.open(path);
    std::vector<std::string> row;
    unsigned int columnNumber=0;
    unsigned int rowNumber=0;
    std::string cell;
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
                        std::vector<std::string> shifts= cellToRawValues<std::string>(c, ';');
                        for(auto &shift : shifts)
                        {
                            std::vector<unsigned int> shiftHours= cellToRawValues<unsigned int>(shift, '-');
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
}

void output::employeeRepository(const std::string &path)
{
    std::ofstream empRepoS;
    empRepoS.open(path);
    empRepoS<<"ID,name,wage,points,priority,nonresident,positions,enemies,"<<std::endl;
    for(const auto &employee : EmployeeManager::getInstance().getAll())
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
        empRepoS<<std::endl;
    }
    empRepoS.close();
}


void output::desiredSchedule(const std::string &path)
{
    std::ofstream desiredScheduleStream;
    desiredScheduleStream.open(path);
    desiredScheduleStream << "ID\\day" << ",";
    for(unsigned int day=1;day<=Schedule::getNumberOfDays();++day)
    {
        desiredScheduleStream << day << ",";
    }
    desiredScheduleStream << "1" << "," << std::endl;
    for(const auto &employee : EmployeeManager::getInstance().getAll())
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
        desiredScheduleStream << std::endl;
    }
    desiredScheduleStream.close();
}

void output::schedule(const std::string &path)
{
    std::ofstream scheduleStream;
    scheduleStream.open(path);
    unsigned int numberOfColumns = 1;
    for(const auto &team : TeamManager::getInstance().getAll())
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
    scheduleStream<<std::endl<<",";
    for(const auto &team : TeamManager::getInstance().getAll())
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
    scheduleStream<<std::endl<<",";
    for(const auto &team : TeamManager::getInstance().getAll())
    {
        for(const auto &position : team->getPositions())
        {
            scheduleStream<<position->shortcut()<<",";
        }
    }
    scheduleStream<<std::endl;
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
        scheduleStream<<std::endl;
        ++d;
    }
    scheduleStream.close();
}

void output::teamRepository(const std::string &path)
{
    std::ofstream teamRepositoryStream;
    teamRepositoryStream.open(path);
    teamRepositoryStream<<"team,positions,"<<std::endl;
    for(const auto &team : TeamManager::getInstance().getAll())
    {
        teamRepositoryStream<<team->getName()<<",";
        for(const auto &positon : team->getPositions())
        {
            teamRepositoryStream<<positon->positionID()<<";";
        }
        teamRepositoryStream<<","<<std::endl;
    }
    teamRepositoryStream.close();
}

void output::teamSchedule(const std::string &path)
{
    std::ofstream teamScheduleStream;
    teamScheduleStream.open(path);
    teamScheduleStream<<"team\\day,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday,"<<std::endl;
    for(const auto &team : TeamManager::getInstance().getAll())
    {
        teamScheduleStream<<team->getName()<<",";
        for(const auto &shift : team->getShifts())
        {
            if(shift->isDayOff())
                teamScheduleStream<<"X,";
            else
                teamScheduleStream<<shift->getStartHour()<<"-"<<shift->getEndHour()<<",";
        }
        teamScheduleStream<<std::endl;
    }
    teamScheduleStream.close();
}
