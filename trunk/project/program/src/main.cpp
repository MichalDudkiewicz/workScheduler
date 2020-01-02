#include <iostream>
#include "schedule.h"
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include "teamQueues.h"
#include <memory>
#include "employeeRepository.h"
#include "teamRepository.h"
#include "finalSchedule.h"
#include "rescuerS.h"
#include "driverS.h"

using namespace std;

int main()
{
    std::shared_ptr<Employee> palinka=std::make_shared<Employee>("Palinka",1);
    std::shared_ptr<Employee> mateusz=std::make_shared<Employee>("Mateusz",2);



    std::unique_ptr<Shift> shift1(new Shift(0,10,2));
    std::unique_ptr<Shift> shift2(new Shift(15,20,3));
    std::unique_ptr<Shift> shift3(new Shift(0,9,8));
    std::unique_ptr<Shift> shift4(new Shift(1,3,20));
    std::unique_ptr<Shift> shift5(new Shift(21,24,7));
    std::unique_ptr<Shift> shift6(new Shift(20,24,7));
    std::unique_ptr<Shift> shift7(new Shift(0,10,8));
    std::unique_ptr<Shift> shift8(new Shift(0,10,20));
    std::unique_ptr<Shift> shift9(new Shift(10,24,12));
    std::unique_ptr<Shift> shift10(new Shift(0,24,12));
    std::unique_ptr<Shift> shift11(new Shift(0,8,29));
    std::unique_ptr<Shift> shift12(new Shift(0,7,29));
    std::unique_ptr<Shift> shift13(new Shift(20,24,29));
    std::unique_ptr<Shift> shift14(new Shift(21,24,29));
    std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
    std::shared_ptr<Position> rescuer=std::make_shared<RescuerS>();
    std::shared_ptr<Position> driver=std::make_shared<DriverS>();
    (*palinka).addDesiredShift(shift1);
    (*palinka).addDesiredShift(shift2);
    (*palinka).addDesiredShift(shift3);
    (*palinka).addDesiredShift(shift4);
    (*palinka).addDesiredShift(shift5);
    (*palinka).addDesiredShift(shift11);
    (*palinka).addDesiredShift(shift13);
    (*mateusz).addDesiredShift(shift6);
    (*mateusz).addDesiredShift(shift7);
    (*mateusz).addDesiredShift(shift8);
    (*mateusz).addDesiredShift(shift9);
    (*mateusz).addDesiredShift(shift10);
    (*mateusz).addDesiredShift(shift12);
    (*mateusz).addDesiredShift(shift14);
    (*mateusz).addPosition(doctor);
    (*mateusz).addPosition(rescuer);
    (*palinka).addPosition(rescuer);
    shiftsPtr shifts(new std::vector<shiftPtr>);
    positionsPtr positions(new std::vector<positionPtr>);

    std::unique_ptr<Shift> monday(new Shift(1,2,1));
    std::unique_ptr<Shift> tuesday(new Shift(22,6,2));
    std::unique_ptr<Shift> wednesday(new Shift(3));
    std::unique_ptr<Shift> thursday(new Shift(0, 7,4));
    std::unique_ptr<Shift> friday(new Shift(21,5,5));
    std::unique_ptr<Shift> saturday(new Shift(21,4,6));
    std::unique_ptr<Shift> sunday(new Shift(20,23,7));

    std::shared_ptr<Team> team = std::make_shared<Team>("S1");
    (*team).addShift(monday);
    (*team).addShift(tuesday);
    (*team).addShift(wednesday);
    (*team).addShift(thursday);
    (*team).addShift(friday);
    (*team).addShift(saturday);
    (*team).addShift(sunday);
    (*team).addPosition(rescuer);
    (*team).addPosition(doctor);
    (*team).addPosition(driver);
    std::vector<employeePtr> employees;
    employees.push_back(mateusz);
    employees.push_back(palinka);
    std::unique_ptr<EmployeeRepository> erep(new EmployeeRepository());
    std::unique_ptr<TeamRepository> trep(new TeamRepository());
    (*trep).addTeam(team);
    (*erep).addEmployee(mateusz);
    (*erep).addEmployee(palinka);
    FinalSchedule finSch(trep,erep);
    (*erep).getEmployeeByID(1)->addEnemy((*erep).getEmployeeByID(2));
    std::cout<<finSch.makeSchedule();
    return 0;
}
