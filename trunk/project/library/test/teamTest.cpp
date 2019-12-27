#include <boost/test/unit_test.hpp>
#include "doctor.h"
#include "medic.h"
#include "position.h"
#include "team.h"
#include <memory>
#include <vector>
#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include "shift.h"
#include "employee.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

BOOST_AUTO_TEST_CASE(TeamConstructionCase)
{
        boost::test_tools::output_test_stream shiftsCopy, shiftsOriginal, positionsCopy, positionsOriginal;
        shiftsPtr shifts(new std::vector<shiftPtr>);
        positionsPtr positions(new std::vector<positionPtr>);
        const std::shared_ptr<Doctor> doctor(new Doctor);
        const std::shared_ptr<Medic> medic(new Medic);
        std::unique_ptr<Shift> monday;
        std::unique_ptr<Shift> tuesday;
        std::unique_ptr<Shift> wednesday;
        std::unique_ptr<Shift> thursday;
        std::unique_ptr<Shift> friday;
        std::unique_ptr<Shift> saturday;
        std::unique_ptr<Shift> sunday;

        monday.reset(new Shift(1, 2, 1));
        tuesday.reset(new Shift(2, 5, 2));
        wednesday.reset(new Shift(10, 12, 3));
        thursday.reset(new Shift(0, 7, 4));
        friday.reset(new Shift(1, 5, 5));
        saturday.reset(new Shift(8, 16, 6));
        sunday.reset(new Shift(20, 23, 7));

        (*positions).push_back(doctor);
        (*positions).push_back(medic);

        (*shifts).push_back(move(monday));
        (*shifts).push_back(move(tuesday));
        (*shifts).push_back(move(wednesday));
        (*shifts).push_back(move(thursday));
        (*shifts).push_back(move(friday));
        (*shifts).push_back(move(saturday));
        (*shifts).push_back(move(sunday));

        for (const auto &shift : *shifts) {
            shiftsCopy << shift->shiftInfo() << std::endl;
        }

        for (const auto &position : *positions) {
            shiftsCopy << position->positionInfo() << std::endl;
        }

        Team *team = new Team("S1");
    (*team).addShift((*shifts)[0]);
    (*team).addShift((*shifts)[1]);
    (*team).addShift((*shifts)[5]);
    (*team).addShift((*shifts)[6]);
    (*team).addShift((*shifts)[2]);
    (*team).addShift((*shifts)[3]);
    (*team).addShift((*shifts)[4]);
    (*team).addPosition(medic);
    (*team).addPosition(doctor);

    for(const auto &shift : (*team).getShifts())
    {
        shiftsOriginal << shift -> shiftInfo() << std::endl;
    }

    for(const auto &position : (*team).getPositions())
    {
        shiftsOriginal << position -> positionInfo() << std::endl;
    }
    BOOST_TEST(shiftsOriginal.is_equal(shiftsCopy.str()));
    BOOST_TEST(positionsOriginal.is_equal(positionsCopy.str()));
    BOOST_CHECK_EQUAL((*team).getName(), "S1");
}

BOOST_AUTO_TEST_CASE(TeamSetNameCase)
{
    shiftsPtr shifts(new std::vector<shiftPtr>);
    positionsPtr positions(new std::vector<positionPtr>);
    const std::shared_ptr<Doctor> doctor(new Doctor);
    const std::shared_ptr<Medic> medic(new Medic);
    std::unique_ptr<Shift> monday(new Shift(1,2,1));
    std::unique_ptr<Shift> tuesday(new Shift(2, 5, 2));
    std::unique_ptr<Shift> wednesday(new Shift(10, 12, 3));
    std::unique_ptr<Shift> thursday(new Shift(0, 7, 4));
    std::unique_ptr<Shift> friday(new Shift(1,5,5));
    std::unique_ptr<Shift> saturday(new Shift(8, 16, 6));
    std::unique_ptr<Shift> sunday(new Shift(20,23, 7));

    (*shifts).push_back(move(monday));
    (*shifts).push_back(move(tuesday));
    (*shifts).push_back(move(wednesday));
    (*shifts).push_back(move(thursday));
    (*shifts).push_back(move(friday));
    (*shifts).push_back(move(saturday));
    (*shifts).push_back(move(sunday));

    Team *team = new Team("S1");
    (*team).addShift((*shifts)[0]);
    (*team).addShift((*shifts)[1]);
    (*team).addShift((*shifts)[5]);
    (*team).addShift((*shifts)[6]);
    (*team).addShift((*shifts)[2]);
    (*team).addShift((*shifts)[3]);
    (*team).addShift((*shifts)[4]);
    (*team).addPosition(doctor);
    (*team).addPosition(medic);
    (*team).setName("S2");
    BOOST_CHECK_EQUAL((*team).getName(), "S2");
}

BOOST_AUTO_TEST_CASE(TeamAddPositionCase)
{
    shiftsPtr shifts(new std::vector<shiftPtr>);
    positionsPtr positions(new std::vector<positionPtr>);
    std::shared_ptr<Doctor> doctor(new Doctor);
    std::unique_ptr<Shift> monday(new Shift(1,2,1));
    std::unique_ptr<Shift> tuesday(new Shift(2, 5, 2));
    std::unique_ptr<Shift> wednesday(new Shift(10, 12, 3));
    std::unique_ptr<Shift> thursday(new Shift(0, 7, 4));
    std::unique_ptr<Shift> friday(new Shift(1,5,5));
    std::unique_ptr<Shift> saturday(new Shift(8, 16, 6));
    std::unique_ptr<Shift> sunday(new Shift(20,23, 7));


    std::shared_ptr<Medic> medic(new Medic);

    (*shifts).push_back(move(monday));
    (*shifts).push_back(move(tuesday));
    (*shifts).push_back(move(wednesday));
    (*shifts).push_back(move(thursday));
    (*shifts).push_back(move(friday));
    (*shifts).push_back(move(saturday));
    (*shifts).push_back(move(sunday));

    Team *team = new Team("S1");
    (*team).addShift((*shifts)[0]);
    (*team).addShift((*shifts)[1]);
    (*team).addShift((*shifts)[5]);
    (*team).addShift((*shifts)[6]);
    (*team).addShift((*shifts)[2]);
    (*team).addShift((*shifts)[3]);
    (*team).addShift((*shifts)[4]);

    (*team).addPosition(doctor);
    (*team).addPosition(medic);
    BOOST_CHECK_EQUAL((*team).getPositions().size(), 2);
    BOOST_CHECK_EQUAL((*team).getPositions()[0]->positionID(), 1);
    BOOST_CHECK_EQUAL((*team).getPositions()[1]->positionID(), 6);
}

BOOST_AUTO_TEST_CASE(TeamEditShiftCase)
{
    shiftsPtr shifts(new std::vector<shiftPtr>);
    positionsPtr positions(new std::vector<positionPtr>);
    const std::shared_ptr<Doctor> doctor(new Doctor);
    std::unique_ptr<Shift> monday(new Shift(1,2,1));
    std::unique_ptr<Shift> tuesday(new Shift(2, 5, 2));
    std::unique_ptr<Shift> wednesday(new Shift(10, 12, 3));
    std::unique_ptr<Shift> thursday(new Shift(0, 7, 4));
    std::unique_ptr<Shift> friday(new Shift(1,5,5));
    std::unique_ptr<Shift> saturday(new Shift(8, 16, 6));
    std::unique_ptr<Shift> sunday(new Shift(20,23, 7));

    const std::shared_ptr<Medic> medic(new Medic);

    (*shifts).push_back(move(monday));
    (*shifts).push_back(move(tuesday));
    (*shifts).push_back(move(wednesday));
    (*shifts).push_back(move(thursday));
    (*shifts).push_back(move(friday));
    (*shifts).push_back(move(saturday));
    (*shifts).push_back(move(sunday));

    Team *team = new Team("S1");
    (*team).addShift((*shifts)[0]);
    (*team).addShift((*shifts)[1]);
    (*team).addShift((*shifts)[5]);
    BOOST_CHECK_EQUAL((*team).getShifts()[6] -> isDayOff(), true);
    (*team).addShift((*shifts)[6]);
    BOOST_CHECK_EQUAL((*team).getShifts()[6] -> isDayOff(), false);
    (*team).addShift((*shifts)[2]);
    (*team).addShift((*shifts)[3]);
    (*team).addShift((*shifts)[4]);
    (*team).addPosition(doctor);
    (*team).addPosition(medic);
    BOOST_CHECK_EQUAL((*team).getShifts()[1] -> isDayOff(), false);
    (*team).removeShift(2);
    BOOST_CHECK_EQUAL((*team).getShifts()[1] -> isDayOff(), true);
}

BOOST_AUTO_TEST_CASE(TeamRemovePositionCase)
{
    shiftsPtr shifts(new std::vector<shiftPtr>);
    positionsPtr positions(new std::vector<positionPtr>);
    const std::shared_ptr<Doctor> doctor(new Doctor);
    std::unique_ptr<Shift> monday;
    std::unique_ptr<Shift> tuesday;
    std::unique_ptr<Shift> wednesday;
    std::unique_ptr<Shift> thursday;
    std::unique_ptr<Shift> friday;
    std::unique_ptr<Shift> saturday;
    std::unique_ptr<Shift> sunday;

    monday.reset(new Shift(1,2,1));
    tuesday.reset(new Shift(2, 5, 2));
    wednesday.reset(new Shift(10, 12, 3));
    thursday.reset(new Shift(0, 7, 4));
    friday.reset(new Shift(1,5,5));
    saturday.reset(new Shift(8, 16, 6));
    sunday.reset(new Shift(20,23, 7));

    const std::shared_ptr<Medic> medic(new Medic);

    (*shifts).push_back(move(monday));
    (*shifts).push_back(move(tuesday));
    (*shifts).push_back(move(wednesday));
    (*shifts).push_back(move(thursday));
    (*shifts).push_back(move(friday));
    (*shifts).push_back(move(saturday));
    (*shifts).push_back(move(sunday));

    Team *team = new Team("S1");
    (*team).addShift((*shifts)[0]);
    (*team).addShift((*shifts)[1]);
    (*team).addShift((*shifts)[5]);
    (*team).addShift((*shifts)[6]);
    (*team).addShift((*shifts)[2]);
    (*team).addShift((*shifts)[3]);
    (*team).addShift((*shifts)[4]);
    (*team).addPosition(doctor);
    (*team).addPosition(medic);
    (*team).removePosition(doctor);
    BOOST_CHECK_EQUAL((*team).getPositions().size(), 1);
}

BOOST_AUTO_TEST_SUITE_END()