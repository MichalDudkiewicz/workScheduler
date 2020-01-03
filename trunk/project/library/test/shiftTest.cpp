#include <boost/test/unit_test.hpp>
#include "shift.h"
#include <memory>

typedef std::unique_ptr<Shift> shiftPtr;

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct MyGlobalFixture {
        MyGlobalFixture() {
            monday.reset(new Shift(0,5,10));
            tuesday.reset(new Shift(5,10,1));
            monday1.reset(new Shift(1,1,1));
            wednesday.reset(new Shift(20,10,1));
        }
        ~MyGlobalFixture() {}

        static shiftPtr monday;
        static shiftPtr tuesday;
        static shiftPtr monday1;
        static shiftPtr wednesday;
    };
    shiftPtr MyGlobalFixture::monday(new Shift(0,5,10));
    shiftPtr MyGlobalFixture::tuesday(new Shift(5,10,1));
    shiftPtr MyGlobalFixture::monday1(new Shift(1,1,1));
    shiftPtr MyGlobalFixture::wednesday(new Shift(20,10,1));

    BOOST_TEST_GLOBAL_FIXTURE( MyGlobalFixture );

BOOST_AUTO_TEST_CASE(ShiftBothConstructorsCase)
{
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::monday).getEndHour(), 5);
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::monday).getStartHour(), 0);
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::tuesday).getEndHour(), 10);
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::tuesday).getStartHour(), 5);
}

BOOST_AUTO_TEST_CASE(ShiftGetLengthCase)
{
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::tuesday).getLength(), 5);
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::wednesday).getLength(), 14);
}

BOOST_AUTO_TEST_CASE(ShiftShiftInfoCase)
{
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::tuesday).shiftInfo(), "day: 1, 5 - 10");
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::wednesday).shiftInfo(), "day: 1, 20 - 10 (night)");
}

BOOST_AUTO_TEST_CASE(ShiftSetHoursCase)
{
    (*MyGlobalFixture::tuesday).setEndHour(23);
    (*MyGlobalFixture::tuesday).setStartHour(10);
    BOOST_REQUIRE_EQUAL((*MyGlobalFixture::tuesday).shiftInfo(), "day: 1, 10 - 23");
}

BOOST_AUTO_TEST_CASE(ShiftIncludeOperatorCase)
{
    Shift shift2(5,10,1);
    Shift shift3(3,12,1);
    Shift shift4(4,6,1);
    Shift shift5(7,20,1);
    Shift shift6(20,10,1);
    Shift shift7(21,9,1);
    BOOST_REQUIRE_EQUAL(shift2>=shift3, false);
    BOOST_REQUIRE_EQUAL(shift3>=shift2, true);
    BOOST_REQUIRE_EQUAL(shift4>=shift2, false);
    BOOST_REQUIRE_EQUAL(shift5>=shift2, false);
    BOOST_REQUIRE_EQUAL(shift4>=shift5, false);
    BOOST_REQUIRE_EQUAL(shift5>=shift4, false);
    BOOST_REQUIRE_EQUAL(shift6>=shift4, false);
    BOOST_REQUIRE_EQUAL(shift6>=shift3, false);
    BOOST_REQUIRE_EQUAL(shift6>=shift5, false);
    BOOST_REQUIRE_EQUAL(shift6>=shift7, true);
    BOOST_REQUIRE_EQUAL(shift7>=shift6, false);
}

BOOST_AUTO_TEST_CASE(ShiftIsNightShiftCase)
{
    Shift shift6(20,24,1);
    Shift shift7(21,9,1);
    Shift shift8(0,9,1);
    BOOST_REQUIRE_EQUAL(shift6.isNightShift(), false);
    BOOST_REQUIRE_EQUAL(shift7.isNightShift(), true);
    BOOST_REQUIRE_EQUAL(shift8.isNightShift(), false);
}

BOOST_AUTO_TEST_CASE(ShiftPlusOperatorCase)
{
    Shift shift4(0,6,2);
    Shift shift5(20,24,1);
    BOOST_REQUIRE_EQUAL((shift4+shift5).shiftInfo(), "day: 1, 20 - 6 (night)");
    BOOST_REQUIRE_EQUAL((shift5+shift4).shiftInfo(), "day: 1, 20 - 6 (night)");
}

BOOST_AUTO_TEST_CASE(ShiftEqualOperatorCase)
{
    Shift shift1(1,6,1);
    Shift shift2(5,10,1);
    Shift shift4(18,24,1);
    Shift shift5(20,24,1);
    Shift shift6(4,10,1);
    Shift shift3(0,12,2);
    Shift shift7(0,9,2);
    BOOST_REQUIRE_EQUAL(shift1==shift2, true);
    BOOST_REQUIRE_EQUAL(shift2==shift1, true);
    BOOST_REQUIRE_EQUAL(shift6==shift1, true);
    BOOST_REQUIRE_EQUAL(shift1==shift6, true);
    BOOST_REQUIRE_EQUAL((shift4+shift7)==(shift5+shift3), true);
    BOOST_REQUIRE_EQUAL((shift5+shift3)==(shift4+shift7), true);
    BOOST_REQUIRE_EQUAL((shift5+shift7)==(shift4+shift3), true);
    BOOST_REQUIRE_EQUAL((shift4+shift3)==(shift5+shift7), true);
    BOOST_REQUIRE_EQUAL(shift5==(shift4+shift7), true);
    BOOST_REQUIRE_EQUAL(shift4==(shift5+shift7), true);
    BOOST_REQUIRE_EQUAL((shift4+shift7)==shift5, true);
    BOOST_REQUIRE_EQUAL((shift5+shift7)==shift4, true);
    BOOST_REQUIRE_EQUAL(shift1==shift4, false);
    BOOST_REQUIRE_EQUAL(shift4==shift1, false);
    BOOST_REQUIRE_EQUAL((shift5+shift7)==shift1, false);
    BOOST_REQUIRE_EQUAL(shift1==(shift5+shift7), false);
}

BOOST_AUTO_TEST_SUITE_END()