#include "finalSchedule.h"
#include "employeeRepository.h"
#include "teamRepository.h"
#include "employee.h"
#include "team.h"
#include "position.h"
#include "schedule.h"


FinalSchedule::FinalSchedule(const TeamRepository* teamRepository, const EmployeeRepository* employeeRepository)
{
    for(const auto &team : teamRepository->getAll())
    {
        allQueues.emplace_back(TeamQueues(team,employeeRepository->getAll()));
    }
    for(unsigned int i = 0; i<Schedule::getNumberOfDays()+1; ++i)
    {
        schedule.emplace_back();
        for(const auto & team : teamRepository->getAll())
        {
            schedule[i].emplace_back(team->getPositions().size());
        }
    }
}

void FinalSchedule::makeSchedule()
{
    bool enemiesInTeam;
    unsigned int teamId;
    unsigned int weekDayIterator = Schedule::getWeekDayIterator(Schedule::getStartDate());
    for(unsigned int day=1;day<=Schedule::getNumberOfDays()+1;++day)
    {
        teamId = 0;
        for(TeamQueues d : allQueues)
        {
            for(unsigned long it=0;it<d.getTeam()->getPositions().size();++it)
            {
                d.queueSort(day-1,it);
                shiftPtr newShift(new Shift(d.getTeam()->getShifts()[weekDayIterator]->getStartHour(),d.getTeam()->getShifts()[weekDayIterator]->getEndHour(),day));
                for(const auto &e : d.getTeamQueues()[day-1][it])
                {
                    enemiesInTeam = false;
                    for(const auto &emp : schedule[day-1][teamId])
                    {
                        if(!emp.empty())
                        {
                            if(emp.front()->isEnemyWith(e))
                            {
                                enemiesInTeam = true;
                                break;
                            }
                        }
                    }
                    if(!e->isBusy(newShift) and !enemiesInTeam and e->getShiftsQuantity()<e->getMaxShifts())
                    {
                        schedule[day-1][teamId][it].push_back(e);
                        e->addCurrentShift(newShift);
                        break;
                    }
                }
            }
            ++teamId;
        }
        ++weekDayIterator;
        if(weekDayIterator == 7)
        {
            weekDayIterator = 0;
        }
    }
}

const calendar& FinalSchedule::getSchedule() const
{
    return schedule;
}

std::string FinalSchedule::scheduleInfo() const
{
    std::ostringstream out;
    out<<std::setw(3)<<" ";
    for(const auto &team : allQueues)
    {
        out<<std::setw(team.getTeam()->getPositions().size()*5)<<team.getTeam()->getName();
    }
    out<<std::endl;
    out<<std::setw(3)<<" ";
    for(const auto &team : allQueues)
    {
        for(const auto &p : team.getTeam()->getPositions())
        {
            out<<std::setw(4)<<p->shortcut()<<"|";
        }
    }
    out<<std::endl;
    unsigned int day = 1;
    for(const auto &d : schedule)
    {
        out<<std::setw(2)<<day<<"|";
        for(const auto &t : d)
        {
            for(const auto &e : t)
            {
                if(!e.empty())
                {
                    out<<std::setw(4)<<e.front()->getId()<<"|";
                }
                else
                {
                    out<<std::setw(4)<<" "<<"|";
                }
            }
        }
        ++day;
        if(day>Schedule::getNumberOfDays())
        {
            day=1;
        }
        out<<std::endl;
    }
    return out.str();
}

void FinalSchedule::clear()
{
    for(auto &day : schedule)
    {
        for(auto &teamQueues : day)
        {
            for(auto &teamQueue : teamQueues)
            {
                teamQueue.clear();
            }
        }
    }
}
