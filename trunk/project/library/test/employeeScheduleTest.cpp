#include <boost/test/unit_test.hpp>
#include "employeeSchedule.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeScheduleCase)
    {
        EmployeeSchedule schedule;
        BOOST_CHECK_EQUAL(schedule.getSchedule().size(),schedule.getNumberOfDays()+1);
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

    BOOST_AUTO_TEST_CASE(EmployeeScheduleAddShiftsCase)
    {
        EmployeeSchedule schedule;
        BOOST_CHECK_EQUAL(schedule.getSchedule().size(),schedule.getNumberOfDays()+1);
        std::unique_ptr<Shift> shift1(new Shift(1,3,11));
        std::unique_ptr<Shift> shift2(new Shift(5,8,11));
        std::unique_ptr<Shift> shift3(new Shift(2,6,11));
        std::unique_ptr<Shift> shift4(new Shift(10,12,11));
        std::unique_ptr<Shift> shift5(new Shift(11,15,11));
        std::unique_ptr<Shift> shift6(new Shift(20,5,11));
        std::unique_ptr<Shift> shift7(new Shift(18,21,11));
        std::unique_ptr<Shift> shift8(new Shift(17,3,11));
        schedule.addShift(shift2);
        schedule.addShift(shift1);
        schedule.addShift(shift3);
        schedule.addShift(shift4);
        schedule.addShift(shift8);
        schedule.addShift(shift7);
        schedule.addShift(shift5);
        schedule.addShift(shift6);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10].size(),3);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->shiftInfo(),"day: 11, 1 - 8");
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10][1]->shiftInfo(),"day: 11, 10 - 15");
        BOOST_CHECK_EQUAL(schedule.getSchedule()[10][2]->shiftInfo(),"day: 11, 17 - 5 (night)");
    }

BOOST_AUTO_TEST_SUITE_END()