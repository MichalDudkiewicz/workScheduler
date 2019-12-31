#include "schedule.h"
#include <sstream>
    unsigned int Schedule::getNumberOfDays(){
        boost::gregorian::date currentDate(boost::gregorian::day_clock::local_day());;
        boost::gregorian::date nextMonthDate(currentDate);
        nextMonthDate += boost::gregorian::months(1);
        return boost::gregorian::gregorian_calendar::end_of_month_day(nextMonthDate.year(), nextMonthDate.month());
    }

boost::gregorian::date Schedule::getCurrentDate(){
        return boost::gregorian::day_clock::local_day();
    }

    boost::gregorian::date Schedule::getStartDate(){
        boost::gregorian::date currentDate(boost::gregorian::day_clock::local_day());;
        boost::gregorian::date nextMonthDate(currentDate);
        nextMonthDate += boost::gregorian::months(1);
        boost::gregorian::date startDate(nextMonthDate.year(), nextMonthDate.month(), 1);
        return startDate;
    }

    const std::string &Schedule::getWeekDay(unsigned int indeks){
        std::vector<std::string> weekDay{7};
        weekDay[0]="Mon";
        weekDay[1]="Tue";
        weekDay[2]="Wed";
        weekDay[3]="Thu";
        weekDay[4]="Fri";
        weekDay[5]="Sat";
        weekDay[6]="Sun";
        return weekDay[indeks];
    }

    unsigned int Schedule::getWeekDayIterator(const boost::gregorian::date &d){
//        std::ostringstream startWeekDay;
//        startWeekDay << "No";
//        startWeekDay << d.day_of_week();
//        unsigned int weekDayIterator = 0;
//        while (startWeekDay.str() == Schedule::getWeekDay(weekDayIterator)) {
//            ++weekDayIterator;
//        }
//        return weekDayIterator;
int day = d.day_of_week();
return day;
    }

//std::string Schedule::scheduleDate()
//{
//boost::gregorian::date currentDate;
//    std::ostringstream out;
//    boost::gregorian::date nextMonthDate(currentDate);
//    nextMonthDate+=boost::gregorian::months(1);
//    out<<nextMonthDate.month().as_long_string()<< " " <<nextMonthDate.year();
//    return out.str();
//}
