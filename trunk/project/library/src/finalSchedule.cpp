#include "finalSchedule.h"
#include "employeeRepository.h"
#include "teamRepository.h"
#include "employee.h"
#include "teamQueues.h"
#include <memory>
#include "team.h"
#include <sstream>
#include "position.h"
#include "schedule.h"

FinalSchedule::FinalSchedule(const teamRepositoryPtr &teamRepository, const empRepositoryPtr &employeeReepository)
{
    for(const auto &team : teamRepository->getAll())
    {
        allQueues.emplace_back(TeamQueues(team,employeeReepository->getAll()));
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

std::string FinalSchedule::makeSchedule() const
{
    std::ostringstream out;
    bool enemiesInTeam;
    unsigned int teamId;
    unsigned int weekDayIterator = Schedule::getWeekDayIterator(Schedule::getStartDate());
    for(unsigned int day=1;day<=Schedule::getNumberOfDays();++day)
    {
        out << "day "<< day<< std::endl;
        teamId = 0;
        for(TeamQueues d : allQueues)
        {
            out << d.getTeam()->getName()<<std::endl;
            for(unsigned long it=0;it<d.getTeam()->getPositions().size();++it)
            {
                out << d.getTeam()->getPositions()[it]->positionInfo()<<": ";
                d.queueSort(day-1,it);
                shiftPtr newShift(new Shift(d.getTeam()->getShifts()[weekDayIterator]->getStartHour(),d.getTeam()->getShifts()[weekDayIterator]->getEndHour(),day));
                for(const auto &e : d.getTeamQueues()[day-1][teamId])
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
                        out << e->getId();
                        schedule[day-1][teamId][it].push_back(e);
                        e->addCurrentShift(newShift);
                        break;
                    }
                }
                out<<std::endl;
            }
            ++teamId;
        }
        ++weekDayIterator;
        if(weekDayIterator == 7)
        {
            weekDayIterator = 0;
        }
        out<<std::endl;
    }
    return out.str();
}