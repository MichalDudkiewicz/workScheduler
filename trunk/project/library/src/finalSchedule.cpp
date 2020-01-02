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
}

std::string FinalSchedule::makeSchedule() const
{
    std::ostringstream out;
//    bool enemiesInTeam;
    Schedule schedule;
    unsigned int weekDayIterator = schedule.getWeekDayIterator(schedule.getStartDate());
    for(unsigned int day=1;day<=schedule.getNumberOfDays();++day)
    {
        out << "day "<< day<< std::endl;
        for(TeamQueues d : allQueues)
        {
            out << d.getTeam()->getName()<<std::endl;
//            enemiesInTeam = false;
            for(unsigned long it=0;it<d.getTeam()->getPositions().size();++it)
            {
                out << d.getTeam()->getPositions()[it]->positionInfo()<<": ";
                std::vector<employeePtr> employeesInTeam;
                d.queueSort(day,it);
                shiftPtr newShift(new Shift(d.getTeam()->getShifts()[weekDayIterator]->getStartHour(),d.getTeam()->getShifts()[weekDayIterator]->getEndHour(),day));
                for(const auto &e : d.getTeamQueues()[day-1][it])
                {
//                    if(!employeesInTeam.empty())
//                    {
//                        if((*employeesInTeam.back()).isEnemyWith(e))
//                            enemiesInTeam=true;
//                    }
                    if(!e->isBusy(newShift))
                    {
                        out << e->getId();
                        employeesInTeam.push_back(e);
                        e->addCurrentShift(newShift);
                        break;
                    }
                }
                out<<std::endl;
            }
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