#include <boost/test/unit_test.hpp>
#include "doctor.h"
#include "medic.h"
#include "team.h"
#include <memory>
#include <vector>
#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include "shift.h"
#include "employee.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct FixtureTeamTest {
        typedef std::unique_ptr<std::vector<positionPtr>> positionsPtr;
        typedef std::unique_ptr<std::vector<shiftPtr>> shiftsPtr;
        FixtureTeamTest()
                : shiftsCopy(), shiftsOriginal(), positionsCopy(), positionsOriginal(),
                  shifts(new std::vector<shiftPtr>), positions(new std::vector<positionPtr>), doctor(new Doctor),
                  medic(new Medic),
                  monday(new Shift(1, 2, 1)), tuesday(new Shift(2, 5, 2)), wednesday(new Shift(10, 12, 3)),
                  thursday(new Shift(0, 7, 4)), friday(new Shift(1, 5, 5)), saturday(new Shift(8, 16, 6)),
                  sunday(new Shift(20, 23, 7)) {
            (*positions).push_back(doctor);
            (*positions).push_back(medic);

            (*shifts).push_back(move(monday));
            (*shifts).push_back(move(tuesday));
            (*shifts).push_back(move(wednesday));
            (*shifts).push_back(move(thursday));
            (*shifts).push_back(move(friday));
            (*shifts).push_back(move(saturday));
            (*shifts).push_back(move(sunday));
        }

        ~FixtureTeamTest() {}

        boost::test_tools::output_test_stream shiftsCopy, shiftsOriginal, positionsCopy, positionsOriginal;
        shiftsPtr shifts;
        positionsPtr positions;
        const std::shared_ptr<Doctor> doctor;
        const std::shared_ptr<Medic> medic;
        std::unique_ptr<Shift> monday;
        std::unique_ptr<Shift> tuesday;
        std::unique_ptr<Shift> wednesday;
        std::unique_ptr<Shift> thursday;
        std::unique_ptr<Shift> friday;
        std::unique_ptr<Shift> saturday;
        std::unique_ptr<Shift> sunday;
    };


    BOOST_FIXTURE_TEST_CASE(TeamConstructionCase, FixtureTeamTest) {
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

        for (const auto &shift : (*team).getShifts()) {
            shiftsOriginal << shift->shiftInfo() << std::endl;
        }

        for (const auto &position : (*team).getPositions()) {
            shiftsOriginal << position->positionInfo() << std::endl;
        }
        BOOST_TEST(shiftsOriginal.is_equal(shiftsCopy.str()));
        BOOST_TEST(positionsOriginal.is_equal(positionsCopy.str()));
        BOOST_CHECK_EQUAL((*team).getName(), "S1");
    }

    BOOST_FIXTURE_TEST_CASE(TeamSetNameCase, FixtureTeamTest) {
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

    BOOST_FIXTURE_TEST_CASE(TeamAddPositionCase, FixtureTeamTest) {
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

    BOOST_FIXTURE_TEST_CASE(TeamEditShiftCase, FixtureTeamTest) {
        Team *team = new Team("S1");
        (*team).addShift((*shifts)[0]);
        (*team).addShift((*shifts)[1]);
        (*team).addShift((*shifts)[5]);
        BOOST_CHECK_EQUAL((*team).getShifts()[6]->isDayOff(), true);
        (*team).addShift((*shifts)[6]);
        BOOST_CHECK_EQUAL((*team).getShifts()[6]->isDayOff(), false);
        (*team).addShift((*shifts)[2]);
        (*team).addShift((*shifts)[3]);
        (*team).addShift((*shifts)[4]);
        (*team).addPosition(doctor);
        (*team).addPosition(medic);
        BOOST_CHECK_EQUAL((*team).getShifts()[1]->isDayOff(), false);
        (*team).removeShift(2);
        BOOST_CHECK_EQUAL((*team).getShifts()[1]->isDayOff(), true);
        (*team).removeShift(7);
        BOOST_CHECK_EQUAL((*team).getShifts()[6]->isDayOff(), true);
        (*team).addShift(8, 10, 7);
        BOOST_CHECK_EQUAL((*team).getShifts()[6]->isDayOff(), false);
        BOOST_CHECK_EQUAL((*team).getShifts()[6]->shiftInfo(), "day: 7, 8 - 10");
    }

    BOOST_FIXTURE_TEST_CASE(TeamRemovePositionCase, FixtureTeamTest) {
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