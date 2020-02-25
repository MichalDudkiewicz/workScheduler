#ifndef WORKSCHEDULER_DATABASEMANAGER_H
#define WORKSCHEDULER_DATABASEMANAGER_H

#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class DatabaseManager
{
private:
  sql::Driver* driver;
  sql::Connection* con;
  sql::Statement* stmt;
  sql::ResultSet* res;
  sql::ResultSetMetaData* res_meta;
  sql::PreparedStatement* prep_stmt;
  DatabaseManager(const DatabaseManager&) = default;
  DatabaseManager& operator=(const DatabaseManager&) = default;

public:
  DatabaseManager() noexcept(false);
  ~DatabaseManager();
  void checkConnection();
  void addTeams();
  void addPositionsToTeams();
  void addShiftsToTeams();
  void addEmployees();
  void addTeamsToEmployees();
  void addEnemiesToEmployees();
  void addPositionToEmployees();
  void addShiftsToEmployees();
};

#endif // WORKSCHEDULER_DATABASEMANAGER_H
