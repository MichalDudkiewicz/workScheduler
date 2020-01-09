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
        EmployeeRepository *repository;
        repository = EmployeeRepository::getInstance();
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
        (*repository).addEmployee(mateush);
        (*repository).addEmployee(palinka);
        (*repository).addEmployee(michal);
        (*repository).addEmployee(janusz);
        BOOST_CHECK_EQUAL((*repository).getEmployeeByID(9)->getName(),"Palinka");
        BOOST_CHECK_EQUAL((*repository).repositoryInfo(),"2. Michal\n"
                                                      "3. Mateusz\n"
                                                      "5. Janusz\n"
                                                      "9. Palinka\n");
        BOOST_CHECK_EQUAL((*repository).getAll()[2]->getName(),"Janusz");
        BOOST_CHECK_EQUAL((*repository).getByPosition(doctor).size(),2);
        BOOST_CHECK_EQUAL((*repository).getByPosition(driver).size(),0);
        BOOST_CHECK_EQUAL((*repository).getByTeam(team)[0].size(),2);
        BOOST_CHECK_EQUAL((*repository).getByTeam(team)[1].size(),0);
        BOOST_CHECK_EQUAL((*repository).getByType(1).size(),4);
        BOOST_CHECK_EQUAL((*repository).getByType(2).size(),0);
        BOOST_CHECK_EQUAL((*repository).getStatisticsByID(5),"ID: 5\n"
                                                          "name: Janusz\n"
                                                          "type: normal\n"
                                                          "points: 0\n"
                                                          "hours worked: 0\n"
                                                          "wage/hour: 0\n"
                                                          "\n");
        (*mateush).setMinShifts(1);
        (*janusz).setMinShifts(20);
        BOOST_CHECK_EQUAL((*repository).getAllUnsatisfied()[0]->getName(),"Mateusz");
        BOOST_CHECK_EQUAL((*repository).getAllUnsatisfied().size(),2);
        (*repository).removeEmployee(5);
        BOOST_CHECK_EQUAL((*repository).repositoryInfo(),"2. Michal\n"
                                                      "3. Mateusz\n"
                                                      "9. Palinka\n");
    }

BOOST_AUTO_TEST_SUITE_END()