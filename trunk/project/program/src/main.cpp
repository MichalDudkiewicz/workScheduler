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

  DatabaseManager workScheduleDb;
  workScheduleDb.checkConnection();
  workScheduleDb.addTeams();
  workScheduleDb.addPositionsToTeams();
  workScheduleDb.addShiftsToTeams();
  workScheduleDb.addEmployees();
  workScheduleDb.addTeamsToEmployees();
  workScheduleDb.addEnemiesToEmployees();
  workScheduleDb.addPositionToEmployees();
  workScheduleDb.addShiftsToEmployees();

  // CREATING AND DISPLAYING SCHEDULE
  WorkScheduler::getInstance().createSchedule();
  cout << WorkScheduler::getInstance().scheduleInfo();
  cout << WorkScheduler::getInstance().toJson();
  return 0;
}
