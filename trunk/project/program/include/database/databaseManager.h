#ifndef WORKSCHEDULER_DATABASEMANAGER_H
#define WORKSCHEDULER_DATABASEMANAGER_H

#include "database/connectionProvider.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class DatabaseManager {
private:
    ConnectionProvider connection;
    sql::Statement* stmt;
    sql::ResultSet* res;
    sql::ResultSetMetaData* resMeta;
    sql::PreparedStatement* prepStmt;
    DatabaseManager();

public:
    static DatabaseManager& getInstance();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
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
