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
//    for(unsigned int i = 0; i<Schedule::getNumberOfDays()+1; ++i)
//    {
//        schedule.emplace_back();
//        for(unsigned long j=0;j<teamRepository->getAll().size();++j)
//        {
//            schedule[i].emplace_back();
//            for(unsigned long k=0;k<teamRepository->getAll()[j]->getPositions().size();++k)
//            {
//                schedule[i][j].emplace_back();
//
//            }
//        }
//    }
}

std::string FinalSchedule::makeSchedule() const
{
    std::ostringstream out;
    std::vector<employeePtr> employeesInTeam;
    bool enemiesInTeam;
    unsigned int weekDayIterator = Schedule::getWeekDayIterator(Schedule::getStartDate());
    for(unsigned int day=1;day<=Schedule::getNumberOfDays();++day)
    {
        out << "day "<< day<< std::endl;
        for(TeamQueues d : allQueues)
        {
            out << d.getTeam()->getName()<<std::endl;
            employeesInTeam.clear();
            for(unsigned long it=0;it<d.getTeam()->getPositions().size();++it)
            {
                out << d.getTeam()->getPositions()[it]->positionInfo()<<": ";
                d.queueSort(day-1,it);
                shiftPtr newShift(new Shift(d.getTeam()->getShifts()[weekDayIterator]->getStartHour(),d.getTeam()->getShifts()[weekDayIterator]->getEndHour(),day));
                for(const auto &e : d.getTeamQueues()[day-1][it])
                {
                    enemiesInTeam = false;
                    for(const auto &emp : employeesInTeam)
                    {
                        if(emp->isEnemyWith(e))
                        {
                            enemiesInTeam = true;
                            break;
                        }
                    }
                    if(!e->isBusy(newShift) and !enemiesInTeam and e->getShiftsQuantity()<e->getMaxShifts())
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