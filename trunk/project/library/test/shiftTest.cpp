#include "shift/shift.h"
#include "utils/calendar.h"
#include <boost/test/unit_test.hpp>
#include <memory>

typedef std::unique_ptr<Shift> shiftPtr;

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureShiftTest {
    FixtureShiftTest()
        : monday(new Shift(0, 5, 10))
        , tuesday(new Shift(5, 10, 1))
        , monday1(new Shift(1, 1, 1))
        , wednesday(new Shift(20, 10, 1))
    {
    }

    ~FixtureShiftTest() {}

    shiftPtr monday;
    shiftPtr tuesday;
    shiftPtr monday1;
    shiftPtr wednesday;
};

BOOST_FIXTURE_TEST_CASE(ShiftBothConstructorsCase, FixtureShiftTest)
{
    BOOST_REQUIRE_EQUAL((*monday).getEndHour(), 5);
    BOOST_REQUIRE_EQUAL((*monday).getStartHour(), 0);
    BOOST_REQUIRE_EQUAL((*tuesday).getEndHour(), 10);
    BOOST_REQUIRE_EQUAL((*tuesday).getStartHour(), 5);
}

BOOST_FIXTURE_TEST_CASE(ShiftGetLengthCase, FixtureShiftTest)
{
    BOOST_REQUIRE_EQUAL((*tuesday).getLength(), 5);
    BOOST_REQUIRE_EQUAL((*wednesday).getLength(), 14);
}

BOOST_FIXTURE_TEST_CASE(ShiftShiftInfoCase, FixtureShiftTest)
{
    BOOST_REQUIRE_EQUAL((*tuesday).shiftInfo(), "day: 1, 5 - 10");
    BOOST_REQUIRE_EQUAL((*wednesday).shiftInfo(), "day: 1, 20 - 10 (night)");
}

BOOST_FIXTURE_TEST_CASE(ShiftSetHoursCase, FixtureShiftTest)
{
    (*tuesday).setEndHour(23);
    (*tuesday).setStartHour(10);
    BOOST_REQUIRE_EQUAL((*tuesday).shiftInfo(), "day: 1, 10 - 23");
}

BOOST_FIXTURE_TEST_CASE(ShiftIncludeOperatorCase, FixtureShiftTest)
{
    Shift shift2(5, 10, 1);
    Shift shift3(3, 12, 1);
    Shift shift4(4, 6, 1);
    Shift shift5(7, 20, 1);
    Shift shift6(20, 10, 1);
    Shift shift7(21, 9, 1);
    BOOST_REQUIRE_EQUAL(shift2 >= shift3, false);
    BOOST_REQUIRE_EQUAL(shift3 >= shift2, true);
    BOOST_REQUIRE_EQUAL(shift4 >= shift2, false);
    BOOST_REQUIRE_EQUAL(shift5 >= shift2, false);
    BOOST_REQUIRE_EQUAL(shift4 >= shift5, false);
    BOOST_REQUIRE_EQUAL(shift5 >= shift4, false);
    BOOST_REQUIRE_EQUAL(shift6 >= shift4, false);
    BOOST_REQUIRE_EQUAL(shift6 >= shift3, false);
    BOOST_REQUIRE_EQUAL(shift6 >= shift5, false);
    BOOST_REQUIRE_EQUAL(shift6 >= shift7, true);
    BOOST_REQUIRE_EQUAL(shift7 >= shift6, false);
}

BOOST_FIXTURE_TEST_CASE(ShiftIsNightShiftCase, FixtureShiftTest)
{
    Shift shift6(20, 24, 1);
    Shift shift7(21, 9, 1);
    Shift shift8(0, 9, 1);
    BOOST_REQUIRE_EQUAL(shift6.isNightShift(), false);
    BOOST_REQUIRE_EQUAL(shift7.isNightShift(), true);
    BOOST_REQUIRE_EQUAL(shift8.isNightShift(), false);
}

BOOST_FIXTURE_TEST_CASE(ShiftPlusOperatorCase, FixtureShiftTest)
{
    Shift shift4(0, 6, 2);
    Shift shift5(20, 24, 1);
    BOOST_REQUIRE_EQUAL((shift4 + shift5).shiftInfo(), "day: 1, 20 - 6 (night)");
    BOOST_REQUIRE_EQUAL((shift5 + shift4).shiftInfo(), "day: 1, 20 - 6 (night)");
}

BOOST_FIXTURE_TEST_CASE(ShiftEqualOperatorCase, FixtureShiftTest)
{
    Shift shift1(1, 6, 1);
    Shift shift2(5, 10, 1);
    Shift shift4(18, 24, 1);
    Shift shift5(20, 24, 1);
    Shift shift6(4, 10, 1);
    Shift shift3(0, 12, 2);
    Shift shift7(0, 9, 2);
    BOOST_REQUIRE_EQUAL(shift1 == shift2, true);
    BOOST_REQUIRE_EQUAL(shift2 == shift1, true);
    BOOST_REQUIRE_EQUAL(shift6 == shift1, true);
    BOOST_REQUIRE_EQUAL(shift1 == shift6, true);
    BOOST_REQUIRE_EQUAL((shift4 + shift7) == (shift5 + shift3), true);
    BOOST_REQUIRE_EQUAL((shift5 + shift3) == (shift4 + shift7), true);
    BOOST_REQUIRE_EQUAL((shift5 + shift7) == (shift4 + shift3), true);
    BOOST_REQUIRE_EQUAL((shift4 + shift3) == (shift5 + shift7), true);
    BOOST_REQUIRE_EQUAL(shift5 == (shift4 + shift7), true);
    BOOST_REQUIRE_EQUAL(shift4 == (shift5 + shift7), true);
    BOOST_REQUIRE_EQUAL((shift4 + shift7) == shift5, true);
    BOOST_REQUIRE_EQUAL((shift5 + shift7) == shift4, true);
    BOOST_REQUIRE_EQUAL(shift1 == shift4, false);
    BOOST_REQUIRE_EQUAL(shift4 == shift1, false);
    BOOST_REQUIRE_EQUAL((shift5 + shift7) == shift1, false);
    BOOST_REQUIRE_EQUAL(shift1 == (shift5 + shift7), false);
}

BOOST_AUTO_TEST_CASE(ShiftExpandCase)
{
    Shift shiftFirst(3, 12, 1);
    Shift shiftLast(18, 22, calendar::getNumberOfDays() + 1);
    Shift shift1(3, 12, 10);
    Shift shift2(18, 23, 12);

    Shift shiftFirstExpanded(shiftFirst + 6);
    Shift shiftLastExpanded(shiftLast + 6);
    Shift shift1Expanded(shift1 + 6);
    Shift shift2Expanded(shift2 + 6);
    BOOST_REQUIRE_EQUAL(shiftFirstExpanded.getDay(), 1);
    BOOST_REQUIRE_EQUAL(shiftFirstExpanded.getStartHour(), 0);
    BOOST_REQUIRE_EQUAL(shiftFirstExpanded.getEndHour(), 18);
    BOOST_REQUIRE_EQUAL(shiftLastExpanded.getDay(), calendar::getNumberOfDays() + 1);
    BOOST_REQUIRE_EQUAL(shiftLastExpanded.getStartHour(), 12);
    BOOST_REQUIRE_EQUAL(shiftLastExpanded.getEndHour(), 24);
    BOOST_REQUIRE_EQUAL(shift1Expanded.getDay(), 9);
    BOOST_REQUIRE_EQUAL(shift1Expanded.getStartHour(), 21);
    BOOST_REQUIRE_EQUAL(shift1Expanded.getEndHour(), 18);
    BOOST_REQUIRE_EQUAL(shift2Expanded.getDay(), 12);
    BOOST_REQUIRE_EQUAL(shift2Expanded.getStartHour(), 12);
    BOOST_REQUIRE_EQUAL(shift2Expanded.getEndHour(), 5);
}

BOOST_AUTO_TEST_SUITE_END()