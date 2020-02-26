#include "database/databaseManager.h"
#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "managers/employeeManager.h"
#include "managers/positionManager.h"
#include "managers/teamManager.h"
#include "shift/shift.h"
#include "team/team.h"

DatabaseManager::DatabaseManager()
  : connection("tcp://127.0.0.1:3306", "Michal", "1234", "work_scheduler")
  , stmt(connection.getConnection()->createStatement())
  , res(nullptr)
  , resMeta(nullptr)
  , prepStmt(nullptr)
{}

void
DatabaseManager::checkConnection()
{
  res = stmt->executeQuery("SELECT 'Hello World!' AS _message");

  while (res->next()) {
    std::cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    std::cout << res->getString("_message") << std::endl;
    std::cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    std::cout << res->getString(1) << std::endl;
  }
}

void
DatabaseManager::addTeams()
{
  res = stmt->executeQuery("SELECT team FROM team_repository");

  while (res->next()) {
    TeamManager::getInstance().addTeam(res->getString(1));
  }
}

void
DatabaseManager::addPositionsToTeams()
{
  res = stmt->executeQuery("SELECT team, position_id FROM team_positions");

  while (res->next()) {
    TeamManager::getInstance()
      .get(res->getString(1))
      ->addPosition(PositionManager::getInstance().get(res->getInt(2)));
  }
}

DatabaseManager::~DatabaseManager()
{
  delete res;
  delete prepStmt;
  delete stmt;
}

void
DatabaseManager::addShiftsToTeams()
{
  res = stmt->executeQuery("SELECT * FROM team_working_hours");

  while (res->next()) {
    for (unsigned int i = 1; i <= 7; i++) {
      if (!(res->isNull(2 * i) or res->isNull(2 * i + 1)))
        TeamManager::getInstance()
          .get(res->getString(1))
          ->addShift(res->getInt(2 * i), res->getInt(2 * i + 1), i);
    }
  }
}

void
DatabaseManager::addEmployees()
{
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
}

void
DatabaseManager::addTeamsToEmployees()
{
  res = stmt->executeQuery("SELECT employee_id, team FROM employee_team");
  while (res->next()) {
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getAuthorisation()
      .addTeam(TeamManager::getInstance().get(res->getString(2)));
  }
}

void
DatabaseManager::addEnemiesToEmployees()
{
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
}

void
DatabaseManager::addPositionToEmployees()
{
  res = stmt->executeQuery("SELECT employee_id, position_id FROM occupation");
  while (res->next()) {
    EmployeeManager::getInstance()
      .get(res->getInt(1))
      ->getFactor()
      ->getAuthorisation()
      .addPosition(PositionManager::getInstance().get(res->getInt(2)));
  }
}

void
DatabaseManager::addShiftsToEmployees()
{
  res = stmt->executeQuery("SELECT * FROM employee_shifts");
  resMeta = res->getMetaData();
  unsigned int number_of_columns = resMeta->getColumnCount();
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
}

DatabaseManager&
DatabaseManager::getInstance()
{
  static DatabaseManager instance;
  return instance;
}
