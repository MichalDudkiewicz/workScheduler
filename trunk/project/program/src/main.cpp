#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "file_stream/fileStream.h"
#include "managers/employeeManager.h"
#include "managers/positionManager.h"
#include "managers/teamManager.h"
#include "managers/workScheduler.h"
#include "positions/position.h"
#include "repositories/employeeRepository.h"
#include "repositories/teamRepository.h"
#include "shift/shift.h"
#include "team/team.h"
#include <chrono>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

using namespace std;

int
main()
{
  sql::ResultSet* res;
  sql::Driver* driver;
  sql::Statement* stmt;
  sql::Connection* con;
  //    sql::PreparedStatement *prep_stmt;
  sql::ResultSetMetaData* res_meta;

  try {

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "Michal", "1234");
    /* Connect to the MySQL test database */
    con->setSchema("work_scheduler");
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT 'Hello World!' AS _message");

    while (res->next()) {
      cout << "\t... MySQL replies: ";
      /* Access column data by alias or column name */
      cout << res->getString("_message") << endl;
      cout << "\t... MySQL says it again: ";
      /* Access column data by numeric offset, 1 is the first column */
      cout << res->getString(1) << endl;
    }

  } catch (sql::SQLException& e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  input::loadPositions();

  res = stmt->executeQuery("SELECT team FROM team_repository");

  while (res->next()) {
    TeamManager::getInstance().addTeam(res->getString(1));
  }
  res = stmt->executeQuery("SELECT team, position_id FROM team_positions");

  while (res->next()) {
    TeamManager::getInstance()
      .get(res->getString(1))
      ->addPosition(PositionManager::getInstance().get(res->getInt(2)));
  }

  res = stmt->executeQuery("SELECT * FROM team_working_hours");

  while (res->next()) {
    for (unsigned int i = 1; i <= 7; i++) {
      if (!(res->isNull(2 * i) or res->isNull(2 * i + 1)))
        TeamManager::getInstance()
          .get(res->getString(1))
          ->addShift(res->getInt(2 * i), res->getInt(2 * i + 1), i);
    }
  }

  res = stmt->executeQuery("SELECT ID, name, wage, points, priority, "
                           "nonresident FROM employee_repository");

  while (res->next()) {
    EmployeeManager::getInstance().add(res->getInt(1), res->getString(2));
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->setHourlyWage(res->getInt(3));
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getRules()
      .setPoints(res->getInt(4));
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getRules()
      .changeType(res->getInt(5));
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getRules()
      .setNonresident(boost::lexical_cast<bool>(res->getInt(6)));
  }

  res = stmt->executeQuery("SELECT employee_id, team FROM employee_team");
  while (res->next()) {
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getAuthorisation()
      .addTeam(TeamManager::getInstance().get(res->getString(2)));
  }

  res = stmt->executeQuery("SELECT employee_id, enemy_id FROM enemies");

  while (res->next()) {
    if (res->getInt(2) < res->getInt(1)) {
      EmployeeManager::getInstance()
        .get(res->getInt(1))
        ->getFactor()
        ->getRelationship()
        .addEnemy(EmployeeManager::getInstance().get(res->getInt(2)));
    }
  }

  res = stmt->executeQuery("SELECT employee_id, position_id FROM occupation");
  while (res->next()) {
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getAuthorisation()
      .addPosition(PositionManager::getInstance().get(res->getInt(2)));
  }

  res = stmt->executeQuery("SELECT * FROM employee_shifts");
  res_meta = res->getMetaData();
  unsigned int number_of_columns = res_meta->getColumnCount();
  while (res->next()) {
    for (unsigned int i = 3; i < number_of_columns; i += 2) {
      if (!(res->isNull(i) or res->isNull(i + 1)))
        EmployeeManager::getInstance()
          .get(res->getInt(1))
          ->getFactor()
          ->getAvailability()
          .getDesiredSchedule()
          .addShift(res->getInt(i), res->getInt(i + 1), res->getInt(2));
    }
  }

  delete res;
  //    delete prep_stmt;
  delete stmt;
  delete con;

  // CREATING AND DISPLAYING SCHEDULE
  WorkScheduler::getInstance().createSchedule();
  cout << WorkScheduler::getInstance().scheduleInfo();
  std::cout << WorkScheduler::getInstance().toJson();
  return 0;
}
