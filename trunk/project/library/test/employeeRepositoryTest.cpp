#include <boost/test/unit_test.hpp>
#include "employeeRepository.h"
#include "employee.h"
#include "team.h"
#include "employeeType.h"
#include <memory>
#include "medic.h"
#include "doctor.h"
#include "driverN.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeRepositoryCase) {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz", 3);
        std::shared_ptr<Employee> paulina = std::make_shared<Employee>("Paulina", 9);
        std::shared_ptr<Employee> michal = std::make_shared<Employee>("Michal", 2);
        std::shared_ptr<Employee> janusz = std::make_shared<Employee>("Janusz", 5);
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        std::shared_ptr<Position> driver = std::make_shared<DriverN>();
        (*mateush).addPosition(medic);
        (*mateush).addPosition(doctor);
        (*paulina).addPosition(medic);
        (*michal).addPosition(doctor);
        std::shared_ptr<Team> team = std::make_shared<Team>("S1");
        (*team).addPosition(doctor);
        (*team).addPosition(medic);
        (*team).addPosition(driver);
        EmployeeRepository::getInstance().add(mateush);
        EmployeeRepository::getInstance().add(paulina);
        EmployeeRepository::getInstance().add(michal);
        EmployeeRepository::getInstance().add(janusz);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().get(9)->getName(), "Paulina");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().info(), "2. Michal\n"
                                                                              "3. Mateusz\n"
                                                                              "5. Janusz\n"
                                                                              "9. Paulina\n");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getAll()[2]->getName(), "Janusz");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByPosition(doctor).size(), 2);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByPosition(driver).size(), 0);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByTeam(team)[0].size(), 2);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByTeam(team)[1].size(), 0);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByType(1).size(), 4);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByType(2).size(), 0);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getStatisticsByID(5), "ID: 5\n"
                                                                                  "name: Janusz\n"
                                                                                  "type: normal\n"
                                                                                  "points: 0\n"
                                                                                  "hours worked: 0\n"
                                                                                  "wage/hour: 0\n"
                                                                                  "\n");
        (*mateush).setMinShifts(1);
        (*janusz).setMinShifts(20);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getAllUnsatisfied()[0]->getName(), "Mateusz");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getAllUnsatisfied().size(), 2);
        EmployeeRepository::getInstance().remove(5);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().info(), "2. Michal\n"
                                                                              "3. Mateusz\n"
                                                                              "9. Paulina\n");
    }
    BOOST_AUTO_TEST_CASE(ExceptionCase) {
        std::shared_ptr<Employee> janusz = std::make_shared<Employee>("Janusz", 77);
        EmployeeRepository::getInstance().add(janusz);
        std::shared_ptr<Employee> janusz1 = std::make_shared<Employee>("Janusz1", 77);
        BOOST_REQUIRE_THROW(EmployeeRepository::getInstance().add(janusz1), std::logic_error);
        EmployeeRepository::getInstance().remove(77);
        BOOST_REQUIRE_THROW(EmployeeRepository::getInstance().get(77), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()