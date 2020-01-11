#include <iostream>
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include <memory>
#include "employeeRepository.h"
#include "teamRepository.h"
#include "finalSchedule.h"
#include "rescuerS.h"
#include "driverS.h"
#include "rescuerN.h"
#include "driverN.h"
#include "medicalRecorder.h"
#include "dispatcher.h"
#include "shift.h"
#include <fstream>
#include "employeeType.h"
#include "schedule.h"
#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{

    // positions

    std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
    std::shared_ptr<Position> rescuerS=std::make_shared<RescuerS>();
    std::shared_ptr<Position> driverS=std::make_shared<DriverS>();
    std::shared_ptr<Position> rescuerN=std::make_shared<RescuerN>();
    std::shared_ptr<Position> driverN=std::make_shared<DriverN>();
    std::shared_ptr<Position> medic=std::make_shared<Medic>();
    std::shared_ptr<Position> medicalRecorder=std::make_shared<MedicalRecorder>();
    std::shared_ptr<Position> dispatcher=std::make_shared<Dispatcher>();

    std::vector<positionPtr> allPositions;
    allPositions.push_back(doctor);
    allPositions.push_back(rescuerS);
    allPositions.push_back(driverS);
    allPositions.push_back(rescuerN);
    allPositions.push_back(driverN);
    allPositions.push_back(medic);
    allPositions.push_back(medicalRecorder);
    allPositions.push_back(dispatcher);

    //employee Repository input

    ifstream empRepoStream;
    empRepoStream.open("../../../dataset/input/admin/employeeRepository.csv");
    vector<string> row;
    unsigned int columnNumber=0;
    unsigned int rowNumber=0;
    string cell,employeeID;
    while(empRepoStream.good())
    {
        getline(empRepoStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if(columnNumber==8)
        {
            columnNumber=0;
            if(rowNumber>0)
            {
                EmployeeRepository::getInstance().addEmployee(stoi(row[0]),row[1]);
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->setHourlyWage(stoi(row[2]));
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->setPoints(stoi(row[3]));
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->changeType(stoi(row[4]));
                EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->setNonresident(boost::lexical_cast<bool>(row[5]));

                vector<unsigned int> positions;
                std::replace(row[6].begin(), row[6].end(), ';', ' ');
                stringstream p(row[6]);
                unsigned int tempP;
                while (p >> tempP)
                    positions.push_back(tempP);
                for(auto &positionID : positions)
                {
                    for(const auto &position : allPositions)
                    {
                        if(position->positionID()==positionID)
                        {
                            EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->addPosition(position);
                            break;
                        }
                    }
                }

                vector<int> enemies;
                std::replace(row[7].begin(), row[7].end(), ';', ' ');
                stringstream e(row[7]);
                int tempE;
                while (e >> tempE)
                    enemies.push_back(tempE);
                for(const auto &enemyID : enemies)
                {
                    if(enemyID<stoi(row[0]))
                    {
                        EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->addEnemy(EmployeeRepository::getInstance().getEmployeeByID(enemyID));
                    }
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    empRepoStream.close();


    //desired Schedule input

    ifstream desSchedStream;
    desSchedStream.open("../../../dataset/input/employees/desiredSchedules.csv");
    row.clear();
    columnNumber=0;
    rowNumber=0;
    while(desSchedStream.good())
    {
        getline(desSchedStream, cell, ',');
        row.push_back(cell);
        ++columnNumber;
        if(columnNumber==Schedule::getNumberOfDays()+2)
        {
            columnNumber=0;
            if(rowNumber>0)
            {
                unsigned int day=0;
                for(auto &c : row)
                {
                    if(day>0)
                    {
                        vector<string> shifts;
                        std::replace(c.begin(), c.end(), ';', ' ');
                        stringstream p(c);
                        string tempP;
                        while (p >> tempP)
                        {
                            shifts.push_back(tempP);
                        }
                        for(auto &shift : shifts)
                        {

                            vector<unsigned int> shiftHours;
                            std::replace(shift.begin(), shift.end(), '-', ' ');
                            stringstream s(shift);
                            unsigned int tempS;
                            while (s >> tempS)
                            {
                                shiftHours.push_back(tempS);
                            }
                            EmployeeRepository::getInstance().getEmployeeByID(stoi(row[0]))->addDesiredShift(shiftHours[0],shiftHours[1],day);
                        }
                    }
                    ++day;
                }
            }
            ++rowNumber;
            row.clear();
        }
    }
    desSchedStream.close();


    //team repository input

    std::unique_ptr<Shift> monday;
    std::unique_ptr<Shift> tuesday;
    std::unique_ptr<Shift> wednesday;
    std::unique_ptr<Shift> thursday;
    std::unique_ptr<Shift> friday;
    std::unique_ptr<Shift> saturday;
    std::unique_ptr<Shift> sunday;

    std::shared_ptr<Team> tS1 = std::make_shared<Team>("S1");
    (*tS1).addPosition(rescuerS);
    (*tS1).addPosition(doctor);
    (*tS1).addPosition(driverS);
    monday.reset(new Shift(6,18,1));
    tuesday.reset(new Shift(6,18,2));
    wednesday.reset(new Shift(6,18,3));
    thursday.reset(new Shift(6,18,4));
    friday.reset(new Shift(6,18,5));
    saturday.reset(new Shift(8,20,6));
    sunday.reset(new Shift(8,20,7));
    (*tS1).addShift(monday);
    (*tS1).addShift(tuesday);
    (*tS1).addShift(wednesday);
    (*tS1).addShift(thursday);
    (*tS1).addShift(friday);
    (*tS1).addShift(saturday);
    (*tS1).addShift(sunday);
    TeamRepository::getInstance().addTeam(tS1);


    std::shared_ptr<Team> tS2 = std::make_shared<Team>("S2");
    (*tS2).addPosition(rescuerS);
    (*tS2).addPosition(doctor);
    (*tS2).addPosition(driverS);
    monday.reset(new Shift(7,19,1));
    tuesday.reset(new Shift(7,19,2));
    wednesday.reset(new Shift(7,19,3));
    thursday.reset(new Shift(7,19,4));
    friday.reset(new Shift(7,19,5));
    saturday.reset(new Shift(9,21,6));
    sunday.reset(new Shift(9,21,7));
    (*tS2).addShift(monday);
    (*tS2).addShift(tuesday);
    (*tS2).addShift(wednesday);
    (*tS2).addShift(thursday);
    (*tS2).addShift(friday);
    (*tS2).addShift(saturday);
    (*tS2).addShift(sunday);
    TeamRepository::getInstance().addTeam(tS2);

    std::shared_ptr<Team> tS3 = std::make_shared<Team>("S3");
    (*tS3).addPosition(rescuerS);
    (*tS3).addPosition(doctor);
    (*tS3).addPosition(driverS);
    monday.reset(new Shift(9,19,1));
    tuesday.reset(new Shift(9,19,2));
    wednesday.reset(new Shift(9,19,3));
    thursday.reset(new Shift(9,19,4));
    friday.reset(new Shift(9,19,5));
    saturday.reset(new Shift(9,19,6));
    sunday.reset(new Shift(7));
    (*tS3).addShift(monday);
    (*tS3).addShift(tuesday);
    (*tS3).addShift(wednesday);
    (*tS3).addShift(thursday);
    (*tS3).addShift(friday);
    (*tS3).addShift(saturday);
    (*tS3).addShift(sunday);
    TeamRepository::getInstance().addTeam(tS3);

    std::shared_ptr<Team> tS4 = std::make_shared<Team>("S4");
    (*tS4).addPosition(rescuerS);
    (*tS4).addPosition(doctor);
    (*tS4).addPosition(driverS);
    monday.reset(new Shift(10,21,1));
    tuesday.reset(new Shift(10,21,2));
    wednesday.reset(new Shift(10,21,3));
    thursday.reset(new Shift(10,21,4));
    friday.reset(new Shift(10,21,5));
    saturday.reset(new Shift(6));
    sunday.reset(new Shift(7));
    (*tS4).addShift(monday);
    (*tS4).addShift(tuesday);
    (*tS4).addShift(wednesday);
    (*tS4).addShift(thursday);
    (*tS4).addShift(friday);
    (*tS4).addShift(saturday);
    (*tS4).addShift(sunday);
    TeamRepository::getInstance().addTeam(tS4);

    std::shared_ptr<Team> t1 = std::make_shared<Team>("1");
    (*t1).addPosition(rescuerN);
    (*t1).addPosition(driverN);
    monday.reset(new Shift(8,17,1));
    tuesday.reset(new Shift(8,17,2));
    wednesday.reset(new Shift(8,17,3));
    thursday.reset(new Shift(8,17,4));
    friday.reset(new Shift(8,17,5));
    saturday.reset(new Shift(6));
    sunday.reset(new Shift(7));
    (*t1).addShift(monday);
    (*t1).addShift(tuesday);
    (*t1).addShift(wednesday);
    (*t1).addShift(thursday);
    (*t1).addShift(friday);
    (*t1).addShift(saturday);
    (*t1).addShift(sunday);
    TeamRepository::getInstance().addTeam(t1);

    std::shared_ptr<Team> t2 = std::make_shared<Team>("2");
    (*t2).addPosition(rescuerN);
    (*t2).addPosition(driverN);
    monday.reset(new Shift(9,18,1));
    tuesday.reset(new Shift(9,18,2));
    wednesday.reset(new Shift(9,18,3));
    thursday.reset(new Shift(9,18,4));
    friday.reset(new Shift(9,18,5));
    saturday.reset(new Shift(6));
    sunday.reset(new Shift(7));
    (*t2).addShift(monday);
    (*t2).addShift(tuesday);
    (*t2).addShift(wednesday);
    (*t2).addShift(thursday);
    (*t2).addShift(friday);
    (*t2).addShift(saturday);
    (*t2).addShift(sunday);
    TeamRepository::getInstance().addTeam(t2);

    std::shared_ptr<Team> t3 = std::make_shared<Team>("3");
    (*t3).addPosition(rescuerN);
    (*t3).addPosition(driverN);
    monday.reset(new Shift(6,18,1));
    tuesday.reset(new Shift(6,18,2));
    wednesday.reset(new Shift(6,18,3));
    thursday.reset(new Shift(6,18,4));
    friday.reset(new Shift(6,18,5));
    saturday.reset(new Shift(7,17,6));
    sunday.reset(new Shift(7,17,7));
    (*t3).addShift(monday);
    (*t3).addShift(tuesday);
    (*t3).addShift(wednesday);
    (*t3).addShift(thursday);
    (*t3).addShift(friday);
    (*t3).addShift(saturday);
    (*t3).addShift(sunday);
    TeamRepository::getInstance().addTeam(t3);

    std::shared_ptr<Team> t4 = std::make_shared<Team>("4");
    (*t4).addPosition(rescuerN);
    (*t4).addPosition(driverN);
    monday.reset(new Shift(10,21,1));
    tuesday.reset(new Shift(10,21,2));
    wednesday.reset(new Shift(10,21,3));
    thursday.reset(new Shift(10,21,4));
    friday.reset(new Shift(10,23,5));
    saturday.reset(new Shift(10,23,6));
    sunday.reset(new Shift(10,23,7));
    (*t4).addShift(monday);
    (*t4).addShift(tuesday);
    (*t4).addShift(wednesday);
    (*t4).addShift(thursday);
    (*t4).addShift(friday);
    (*t4).addShift(saturday);
    (*t4).addShift(sunday);
    TeamRepository::getInstance().addTeam(t4);

    std::shared_ptr<Team> t5 = std::make_shared<Team>("5");
    (*t5).addPosition(rescuerN);
    (*t5).addPosition(driverN);
    monday.reset(new Shift(8,19,1));
    tuesday.reset(new Shift(8,19,2));
    wednesday.reset(new Shift(8,19,3));
    thursday.reset(new Shift(8,19,4));
    friday.reset(new Shift(8,19,5));
    saturday.reset(new Shift(6));
    sunday.reset(new Shift(7));
    (*t5).addShift(monday);
    (*t5).addShift(tuesday);
    (*t5).addShift(wednesday);
    (*t5).addShift(thursday);
    (*t5).addShift(friday);
    (*t5).addShift(saturday);
    (*t5).addShift(sunday);
    TeamRepository::getInstance().addTeam(t5);

    std::shared_ptr<Team> t6 = std::make_shared<Team>("6");
    (*t6).addPosition(rescuerN);
    (*t6).addPosition(driverN);
    monday.reset(new Shift(10,20,1));
    tuesday.reset(new Shift(10,20,2));
    wednesday.reset(new Shift(10,20,3));
    thursday.reset(new Shift(10,20,4));
    friday.reset(new Shift(10,20,5));
    saturday.reset(new Shift(6));
    sunday.reset(new Shift(7));
    (*t6).addShift(monday);
    (*t6).addShift(tuesday);
    (*t6).addShift(wednesday);
    (*t6).addShift(thursday);
    (*t6).addShift(friday);
    (*t6).addShift(saturday);
    (*t6).addShift(sunday);
    TeamRepository::getInstance().addTeam(t6);

    std::shared_ptr<Team> tN1 = std::make_shared<Team>("N1");
    (*tN1).addPosition(rescuerS);
    (*tN1).addPosition(doctor);
    (*tN1).addPosition(driverS);
    monday.reset(new Shift(18,6,1));
    tuesday.reset(new Shift(18,6,2));
    wednesday.reset(new Shift(18,6,3));
    thursday.reset(new Shift(18,6,4));
    friday.reset(new Shift(18,8,5));
    saturday.reset(new Shift(20,8,6));
    sunday.reset(new Shift(20,6,7));
    (*tN1).addShift(monday);
    (*tN1).addShift(tuesday);
    (*tN1).addShift(wednesday);
    (*tN1).addShift(thursday);
    (*tN1).addShift(friday);
    (*tN1).addShift(saturday);
    (*tN1).addShift(sunday);
    TeamRepository::getInstance().addTeam(tN1);

    std::shared_ptr<Team> tN2 = std::make_shared<Team>("N2");
    (*tN2).addPosition(rescuerS);
    (*tN2).addPosition(doctor);
    (*tN2).addPosition(driverS);
    monday.reset(new Shift(19,7,1));
    tuesday.reset(new Shift(19,7,2));
    wednesday.reset(new Shift(19,7,3));
    thursday.reset(new Shift(19,7,4));
    friday.reset(new Shift(19,9,5));
    saturday.reset(new Shift(21,9,6));
    sunday.reset(new Shift(21,7,7));
    (*tN2).addShift(monday);
    (*tN2).addShift(tuesday);
    (*tN2).addShift(wednesday);
    (*tN2).addShift(thursday);
    (*tN2).addShift(friday);
    (*tN2).addShift(saturday);
    (*tN2).addShift(sunday);
    TeamRepository::getInstance().addTeam(tN2);

    std::shared_ptr<Team> tN3 = std::make_shared<Team>("N3");
    (*tN3).addPosition(rescuerN);
    (*tN3).addPosition(driverN);
    monday.reset(new Shift(20,6,1));
    tuesday.reset(new Shift(20,6,2));
    wednesday.reset(new Shift(20,6,3));
    thursday.reset(new Shift(20,6,4));
    friday.reset(new Shift(20,6,5));
    saturday.reset(new Shift(20,6,6));
    sunday.reset(new Shift(7));
    (*tN3).addShift(monday);
    (*tN3).addShift(tuesday);
    (*tN3).addShift(wednesday);
    (*tN3).addShift(thursday);
    (*tN3).addShift(friday);
    (*tN3).addShift(saturday);
    (*tN3).addShift(sunday);
    TeamRepository::getInstance().addTeam(tN3);

    std::shared_ptr<Team> tR = std::make_shared<Team>("R");
    (*tR).addPosition(medicalRecorder);
    monday.reset(new Shift(8,15,1));
    tuesday.reset(new Shift(8,15,2));
    wednesday.reset(new Shift(8,15,3));
    thursday.reset(new Shift(8,15,4));
    friday.reset(new Shift(8,15,5));
    saturday.reset(new Shift(6));
    sunday.reset(new Shift(7));
    (*tR).addShift(monday);
    (*tR).addShift(tuesday);
    (*tR).addShift(wednesday);
    (*tR).addShift(thursday);
    (*tR).addShift(friday);
    (*tR).addShift(saturday);
    (*tR).addShift(sunday);
    TeamRepository::getInstance().addTeam(tR);

    std::shared_ptr<Team> tDD = std::make_shared<Team>("DD");
    (*tDD).addPosition(dispatcher);
    monday.reset(new Shift(7,18,1));
    tuesday.reset(new Shift(7,18,2));
    wednesday.reset(new Shift(7,18,3));
    thursday.reset(new Shift(7,18,4));
    friday.reset(new Shift(7,18,5));
    saturday.reset(new Shift(7,18,6));
    sunday.reset(new Shift(7,18,7));
    (*tDD).addShift(monday);
    (*tDD).addShift(tuesday);
    (*tDD).addShift(wednesday);
    (*tDD).addShift(thursday);
    (*tDD).addShift(friday);
    (*tDD).addShift(saturday);
    (*tDD).addShift(sunday);
    TeamRepository::getInstance().addTeam(tDD);

    std::shared_ptr<Team> tDN = std::make_shared<Team>("DN");
    (*tDN).addPosition(dispatcher);
    monday.reset(new Shift(18,7,1));
    tuesday.reset(new Shift(18,7,2));
    wednesday.reset(new Shift(18,7,3));
    thursday.reset(new Shift(18,7,4));
    friday.reset(new Shift(18,7,5));
    saturday.reset(new Shift(18,7,6));
    sunday.reset(new Shift(18,7,7));
    (*tDN).addShift(monday);
    (*tDN).addShift(tuesday);
    (*tDN).addShift(wednesday);
    (*tDN).addShift(thursday);
    (*tDN).addShift(friday);
    (*tDN).addShift(saturday);
    (*tDN).addShift(sunday);
    TeamRepository::getInstance().addTeam(tDN);

//schedule
    FinalSchedule finalSchedule(TeamRepository::getInstance(),EmployeeRepository::getInstance());
    finalSchedule.makeSchedule();
    std::cout<<finalSchedule.scheduleInfo();

//    output employeeRepository
//    ofstream empRepoStream;
//    empRepoStream.open("employeeRepository.csv");
//    empRepoStream<<"ID,name,wage,points,priority,nonresident,positions,enemies,"<<endl;
//    for(const auto &employee : EmployeeRepository::getInstance().getAll())
//    {
//        empRepoStream<<employee->getId()<<","<<employee->getName()<<","<<employee->getHourlyWage()<<","<<employee->getPoints()<<","<<employee->getType()->getPriority()<<","<<employee->isNonresident()<<",";
//        for(const auto &position : employee->getPositions())
//        {
//            empRepoStream<<position->positionID()<<";";
//        }
//        empRepoStream<<",";
//        for(const auto &enemy : employee->getMyEnemies())
//        {
//            empRepoStream<<enemy->getId()<<";";
//        }
//        empRepoStream<<",";
//        empRepoStream<<endl;
//    }
//    empRepoStream.close();

    //output
//    ofstream test2;
//    test2.open("desiredSchedules.csv");
//    test2<<"ID\\day"<<",";
//    for(unsigned int day=1;day<=Schedule::getNumberOfDays();++day)
//    {
//        test2<<day<<",";
//    }
//    test2<<"1"<<","<<endl;
//    for(const auto &employee : EmployeeRepository::getInstance().getAll())
//    {
//        test2<<employee->getId()<<",";
//        for(const auto &shifts : employee->getDesiredSchedule())
//        {
//            for(const auto &shift : shifts)
//            {
//                test2<<shift->getStartHour()<<"-"<<shift->getEndHour()<<";";
//            }
//            test2<<",";
//        }
//        test2<<endl;
//    }
//    test2.close();

    // schedule output
    
    return 0;
}
