#include <boost/test/unit_test.hpp>
#include "employeeRepository.h"
#include <employee.h>
#include <team.h>
#include <employeeType.h>
#include <memory>
#include "medic.h"
#include "doctor.h"
#include "driverN.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeRepositoryCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",3);
        std::shared_ptr<Employee> palinka = std::make_shared<Employee>("Palinka",9);
        std::shared_ptr<Employee> michal = std::make_shared<Employee>("Michal",2);
        std::shared_ptr<Employee> janusz = std::make_shared<Employee>("Janusz",5);
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        std::shared_ptr<Position> driver = std::make_shared<DriverN>();
        (*mateush).addPosition(medic);
        (*mateush).addPosition(doctor);
        (*palinka).addPosition(medic);
        (*michal).addPosition(doctor);
        std::shared_ptr<Team> team = std::make_shared<Team>("S1");
        (*team).addPosition(doctor);
        (*team).addPosition(medic);
        (*team).addPosition(driver);
        EmployeeRepository::getInstance().addEmployee(mateush);
        EmployeeRepository::getInstance().addEmployee(palinka);
        EmployeeRepository::getInstance().addEmployee(michal);
        EmployeeRepository::getInstance().addEmployee(janusz);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getEmployeeByID(9)->getName(),"Palinka");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().repositoryInfo(),"2. Michal\n"
                                                      "3. Mateusz\n"
                                                      "5. Janusz\n"
                                                      "9. Palinka\n");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getAll()[2]->getName(),"Janusz");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByPosition(doctor).size(),2);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByPosition(driver).size(),0);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByTeam(team)[0].size(),2);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByTeam(team)[1].size(),0);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByType(1).size(),4);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getByType(2).size(),0);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getStatisticsByID(5),"ID: 5\n"
                                                          "name: Janusz\n"
                                                          "type: normal\n"
                                                          "points: 0\n"
                                                          "hours worked: 0\n"
                                                          "wage/hour: 0\n"
                                                          "\n");
        (*mateush).setMinShifts(1);
        (*janusz).setMinShifts(20);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getAllUnsatisfied()[0]->getName(),"Mateusz");
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().getAllUnsatisfied().size(),2);
        EmployeeRepository::getInstance().removeEmployee(5);
        BOOST_CHECK_EQUAL(EmployeeRepository::getInstance().repositoryInfo(),"2. Michal\n"
                                                      "3. Mateusz\n"
                                                      "9. Palinka\n");
    }

BOOST_AUTO_TEST_SUITE_END()