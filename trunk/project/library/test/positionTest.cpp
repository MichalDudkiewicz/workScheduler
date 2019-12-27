#include <boost/test/unit_test.hpp>
#include "doctor.h"
#include "rescuerN.h"
#include "rescuerS.h"
#include "medic.h"
#include "medicalRecorder.h"
#include "dispatcher.h"
#include "driverN.h"
#include "driverS.h"
#include "position.h"
#include <memory>

typedef std::shared_ptr<Position> positionPtr;

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

BOOST_AUTO_TEST_CASE(PositionGetPositionCase)
{
    positionPtr doctor = std::make_shared<Doctor>();
    BOOST_REQUIRE_EQUAL((*doctor).positionInfo(), "doctor");
    positionPtr rescuerN = std::make_shared<RescuerN>();
    BOOST_REQUIRE_EQUAL((*rescuerN).positionInfo(), "rescuer (normal)");
    positionPtr rescuerS = std::make_shared<RescuerS>();
    BOOST_REQUIRE_EQUAL((*rescuerS).positionInfo(), "rescuer (special)");
    positionPtr medic = std::make_shared<Medic>();
    BOOST_REQUIRE_EQUAL((*medic).positionInfo(), "medic");
    positionPtr medicalRecorder = std::make_shared<MedicalRecorder>();
    BOOST_REQUIRE_EQUAL((*medicalRecorder).positionInfo(), "medical recorder");
    positionPtr dispatcher = std::make_shared<Dispatcher>();
    BOOST_REQUIRE_EQUAL((*dispatcher).positionInfo(), "dispatcher");
    positionPtr driverN = std::make_shared<DriverN>();
    BOOST_REQUIRE_EQUAL((*driverN).positionInfo(), "driver (normal)");
    positionPtr driverS = std::make_shared<DriverS>();
    BOOST_REQUIRE_EQUAL((*driverS).positionInfo(), "driver (special)");
}

BOOST_AUTO_TEST_SUITE_END()