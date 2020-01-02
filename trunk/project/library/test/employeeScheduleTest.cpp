#include <boost/test/unit_test.hpp>
#include "employeeSchedule.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeScheduleCase)
    {
        EmployeeSchedule schedule;
        BOOST_CHECK_EQUAL(schedule.getSchedule().size(),Schedule::getNumberOfDays()+1);
        std::unique_ptr<Shift> shift1(new Shift(5,10,3));
        std::unique_ptr<Shift> shift2(new Shift(15,20,3));
        std::unique_ptr<Shift> shift3(new Shift(5,10,15));
        std::unique_ptr<Shift> shift4(new Shift(5,15,11));
        std::unique_ptr<Shift> shift5(new Shift(4,15,11));
        std::unique_ptr<Shift> shift6(new Shift(20,24,11));
        std::ostringstream s1,s2,s3,s4,s6;
        s1<<shift1->shiftInfo();
        s2<<shift2->shiftInfo();
        s3<<shift3->shiftInfo();
        s4<<shift4->shiftInfo();
        s6<<shift6->shiftInfo();
        schedule.addShift(shift2);
        schedule.addShift(shift1);
        schedule.addShift(shift3);
        schedule.addShift(shift4);
        schedule.addShift(shift6);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[2][0]->shiftInfo(),s1.str());
        BOOST_CHECK_EQUAL(schedule.getSchedule()[2][1]->shiftInfo(),s2.str());
        BOOST_CHECK_EQUAL(schedule.getSchedule()[14][0]->shiftInfo(),s3.str());
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->shiftInfo(),s4.str());
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10][1]->shiftInfo(),s6.str());
        schedule.removeShift(11,1);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->shiftInfo(),s6.str());
    }

BOOST_AUTO_TEST_SUITE_END()