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
