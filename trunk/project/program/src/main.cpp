#include "database/databaseManager.h"
#include "employee/employee.h"
#include "file_stream/fileStream.h"
#include "managers/workScheduler.h"
#include "shift/shift.h"
#include "team/team.h"
#include <chrono>

#include <iostream>

using namespace std;

int
main()
{
  system("rm -R -f ../../../dataset/converted/* && libreoffice --headless "
         "--convert-to csv --outdir ../../../dataset/converted/ "
         "../../../dataset/unconverted/*");

  //    input::loadDesiredShifts("../../../dataset/unconverted");

  input::loadPositions();

  DatabaseManager::getInstance().checkConnection();
  DatabaseManager::getInstance().addTeams();
  DatabaseManager::getInstance().addPositionsToTeams();
  DatabaseManager::getInstance().addShiftsToTeams();
  DatabaseManager::getInstance().addEmployees();
  DatabaseManager::getInstance().addTeamsToEmployees();
  DatabaseManager::getInstance().addEnemiesToEmployees();
  DatabaseManager::getInstance().addPositionToEmployees();
  DatabaseManager::getInstance().addShiftsToEmployees();

  // CREATING AND DISPLAYING SCHEDULE
  WorkScheduler::getInstance().createSchedule();
  cout << WorkScheduler::getInstance().scheduleInfo();
  cout << WorkScheduler::getInstance().toJson();
  return 0;
}
