#include<iostream>
#include<vector>
#include <queue>
#include <functional>
#include<sqlite3.h>
#include<string>
#include <ctime>
#include<fstream>
#include "vehicles.h"
#include "parkingLot.h"
using namespace std;



static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void parkTool(ParkingLot* pl){
    string name, plate;
    time_t entry_time = time(nullptr);
    int type;
    
    cout << "\nSELECT TYPE: 1.Car  2.Bike  3.EV-Car  4.EV-Bike" << endl;
    cout << "Input: ";
    cin >> type;
    cout << "Current time: "<< ctime(&entry_time)<<endl;
    cout << "Enter Name, Plate, (e.g. Rahul DL01): ";
    
    cin >> name >> plate;
    vehicle* v = nullptr;

    switch (type){
        case 1:
            v = new Car(plate, name, entry_time);
            break;
        case 2:
            v = new bike(plate, name, entry_time);
            break;
        case 3:
            v = new EVCar(plate, name, entry_time);
            break;
        case 4:
            v = new EVBike(plate, name, entry_time);
            break;
        default:
            break;
    }
    if (v == nullptr) {
        cout << "Invalid Vehicle Type!" << endl;
        return;
    }
    pl->park(v);
    pl->debug();
}

void leaveTool(ParkingLot* pl){
    string p;
    int t;
    cout<<"Enter number plate: ";
    cin >> p;
    pl->leave(p);
    pl->debug();
}

int main(){
    // sqlite3* db;
    // int exit = 0;
    // exit = sqlite3_open("parkingLot.db", &db);
    // if(exit){
    //     cout<<"ERROR CREATING DATABSE: "<<sqlite3_errmsg(db)<<endl;
    // }
    // else {
    //     cout<<"SUCCESSFULLY CREATED DB!"<<endl;
    // }
    // sqlite3_close(db);
    cout << "--- WELCOME TO LOCUS ---" << endl;
    bool IsTrue = true;
    ParkingLot* pl = new ParkingLot();
    pl->debug();
    while(IsTrue){
        cout<<"What do you want to do?"<<endl;
        cout<<"1. Park"<<endl;
        cout<<"2. Leave"<<endl;
        cout<<"3. Exit"<<endl;
        int op;
        cin >> op;
        switch (op){
        case 1:
            parkTool(pl);
            break;
        case 2:
            leaveTool(pl);
            break;
        case 3: 
            delete pl;
            IsTrue = false;
            break;
        default:
            break;
        }
    }
}