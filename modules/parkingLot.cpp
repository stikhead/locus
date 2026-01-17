#include "parkingLot.h"
#include "vehicles.h"
#include <iostream>
using namespace std;
ParkingLot::ParkingLot(){
    spots.resize(10, vector<vehicle *>(3, nullptr));
    capacity = 10;
    curr = 0;
    for (int i = 0; i < capacity; i++){
        freeCarSpots.push({i, 0});
        freeBikeSpots.push({i, 1});
        freeEVspots.push({i, 2});
    }
}

bool ParkingLot::IsFull(){
    return curr == capacity * 3;
}

bool ParkingLot::IsEmpty(){
    return curr == 0;
}

bool ParkingLot::isDuplicateEntry(vehicle *v){
    string type = v->getType();
    int search;
    if (type == "Car"){
        search = 0;
    }
    else if (type == "Bike"){
        search = 1;
    }
    else{
        search = 2;
    }

    for (int i = 0; i < spots.size(); i++){
        if (spots[i][search] != nullptr && spots[i][search]->getPlate() == v->getPlate()){
            return true;
        }
    }
    return false;
}

void ParkingLot::debug(){
    cout << "\n======================== [ LIVE MAP ] ========================" << endl;
    cout << "| Slot |      CAR       |      BIKE      |    EV / OTHER  |" << endl;
    cout << "|------|----------------|----------------|----------------|" << endl;

    for (int i = 0; i < capacity; i++){
        if (i < 10) { cout << "|  " << i << "   |"; }
        else { cout << "|  " << i << "  |"; }
        
        for (int j = 0; j < 3; j++){
            if (spots[i][j] == nullptr){
                cout << "    . . . .     |";
            }
            else{
                string p = spots[i][j]->getPlate();
                if (p.length() <= 4)
                    cout << "      " << p << "      |";
                else if (p.length() <= 6)
                    cout << "   " << p << "     |";
                else
                    cout << "  " << p << "   |";
            }
        }
        cout << endl;
    }
    cout << "==========================================================" << endl;
}

void ParkingLot::park(vehicle *v){
    if (IsFull()){
        cout << "Full! couldnt park" << endl;
        delete v;
        return;
    }

    string type = v->getType();
    pair<int, int> bestSpot = {-1, -1};
    if (type == "Bike"){
        if(freeBikeSpots.empty()){
            cout << "No Empty Bike Lane!" << endl;
            delete v;
            return;
        }
        bestSpot = freeBikeSpots.top();
        freeBikeSpots.pop();
    }

    else if (type == "Car"){
        if (IsFull()){
            cout << "Full! couldnt park" << endl;
            delete v;
            return;
        }
        if (freeCarSpots.empty()){
            cout << "No Empty Car Lane!" << endl;
            return;
        }
        bestSpot = freeCarSpots.top();
        freeCarSpots.pop();
    }

    else{
        if (IsFull()){
            cout << "Full! couldnt park" << endl;
            delete v;
            return;
        }
        if (freeEVspots.empty()){
            cout << "No Empty EV Lane!" << endl;
            return;
        }
        bestSpot = freeEVspots.top();
        freeEVspots.pop();
    }

    if (isDuplicateEntry(v)){
        delete v;
        cout << "Duplicate Entry!" << endl;
        return;
    }

    spots[bestSpot.first][bestSpot.second] = v;
    curr++;
    time_t entry = v->getTime();
    cout << "Parked " << type << " in " << bestSpot.first << " at " << ctime(&entry) << endl;
}

void ParkingLot::leave(string plate){
    time_t exitTime = time(nullptr);
    if (IsEmpty()){
        cout << "Lot is empty!" << endl;
        return;
    }

    for (int i = 0; i < capacity; i++){
        for (int j = 0; j < 3; j++){
            if (spots[i][j] != nullptr && spots[i][j]->getPlate() == plate){
                // calc
                double fee = spots[i][j]->calculateFee(exitTime);
                // output
                cout << "\n--- RECEIPT ---" << endl;
                cout << "Vehicle: " << spots[i][j]->getPlate() << endl;
                cout << "Total Bill: $" << fee << endl;
                cout << "---------------" << endl;
                // memory
                if (j == 0)
                    freeCarSpots.push({i, 0});
                else if (j == 1)
                    freeBikeSpots.push({i, 1});
                else if (j == 2)
                    freeEVspots.push({i, 2});
                cout << "Slot " << i << " is now free." << endl;
                delete spots[i][j];
                spots[i][j] = nullptr;
                curr--;
                return;
            }
        }
    }
    cout << "Vehicle " << plate << " not found!" << endl;
}
ParkingLot::~ParkingLot(){
    for (int i = 0; i < capacity; i++){
        for (int j = 0; j < 3; j++){
            if (spots[i][j] != nullptr){
                delete spots[i][j];
                spots[i][j] = nullptr;
            }
        }
    }
    cout << "Parking Lot Closed. All vehicles cleared." << endl;
}