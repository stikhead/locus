#include<iostream>
#include<vector>
#include <queue>
#include <functional>
#include<sqlite3.h>
#include<string>
#include <ctime>
#include<fstream>
using namespace std;

void duration(time_t entry, time_t exitTime){
    double total_seconds = difftime(exitTime, entry);
    int total_seconds_int = static_cast<int>(total_seconds);
    int hours = total_seconds_int / 3600;
    int minutes = (total_seconds_int % 3600) / 60;
    int seconds = total_seconds_int % 60;
    cout << "---------------------------------" << endl;
    cout << "Total Duration: " 
         << hours << "h " 
         << minutes << "m " 
         << seconds << "s" << endl;
}

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

class vehicle {
    protected:
        string licensePlate;
        string ownerName;
        time_t entryTime;
        int rate_per_hour;
    public: 
        vehicle(){};
        vehicle(string plate, string name, time_t time, int rate){
            licensePlate = plate;
            ownerName = name;
            entryTime = time;
            rate_per_hour = rate;
        }
        string getPlate() const {

            return licensePlate;
        }
        time_t getTime()const{
            return entryTime;
        }
        int getRate()const{
            return rate_per_hour;
        }
        virtual string getType()=0;
        double calculateFee(time_t exitTime){
            time_t entry = getTime();
            duration(entry, exitTime);
            double total_seconds = difftime(exitTime, entry);
            double hours_fractional = total_seconds / 3600.0;
            double total_cost = hours_fractional * rate_per_hour;
            return total_cost;
        };
        virtual ~vehicle() {};
};
class bike : public vehicle {
    public:
        bike(){};
        bike(string plate, string name, time_t time) : vehicle(plate, name, time, 20) {}
                bike(string plate, string name, time_t time, int rate) : vehicle(plate, name, time, rate) {}
        
        string getType()override{
            return "Bike"; 
        }
};

class EVBike : public bike {
    public:
    EVBike(){};
        EVBike(string plate, string name, time_t time) : bike(plate, name, time, 5){}
        string getType()override{
            return "EV"; 
        }
};
class Car : public vehicle {
    public:
    Car(){};
        Car (string plate, string name, time_t time) : vehicle(plate, name, time, 50) {};
        Car (string plate, string name, time_t time, int rate) : vehicle(plate, name, time, rate) {};

        
        string getType()override{
            return "Car"; 
        }
};
class EVCar : public Car {
    public:
    EVCar(){};
        EVCar(string plate, string name, time_t time) : Car(plate, name, time, 25){}
        string getType()override{
                    return "EV"; 
                }
};
class ParkingLot{
    private:
        vector<vector<vehicle*>>spots;
        int capacity;
        int curr;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeCarSpots;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeBikeSpots;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeEVspots;
    public:
        ParkingLot(){
            spots.resize(10, vector<vehicle*>(3, nullptr));
            capacity = 10;
            curr = 0;
            for(int i=0; i<capacity; i++){
                freeCarSpots.push({i, 0});
                freeBikeSpots.push({i, 1});
                freeEVspots.push({i, 2});
            }
        }
        
        bool IsFull(){
            return curr==capacity;
        }
        
        bool IsEmpty(){
            return curr==0;
        }
        bool isDuplicateEntry(vehicle* v){
            string type = v->getType();
            int search;
            if(type=="Car"){
                search = 0;
            }
            else if(type=="Bike"){
                search = 1;
            }
            else {
                search = 2;
            }
            for(int i=0; i<spots.size(); i++){
                if(spots[i][search] != nullptr && spots[i][search]->getPlate()==v->getPlate()){
                    return true;
                }
            }
            return false;
        }

        void debug() {
            cout << "\n======================== [ LIVE MAP ] ========================" << endl;
            cout << "| Slot |      CAR       |      BIKE      |    EV / OTHER  |" << endl;
            cout << "|------|----------------|----------------|----------------|" << endl;

            for(int i=0; i<capacity; i++) {
                if(i < 10) cout << "|  " << i << "   |"; 
                else       cout << "|  " << i << "  |";
                for(int j=0; j<3; j++) {
                    if(spots[i][j] == nullptr) {
                        cout << "    . . . .     |"; 
                    } 
                    else {
                        string p = spots[i][j]->getPlate();
                        if (p.length() <= 4)      cout << "      " << p << "      |";
                        else if (p.length() <= 6) cout << "   " << p << "     |";
                        else                      cout << "  " << p << "   |";
                    }
                }
                cout << endl;
            }
            cout << "==========================================================" << endl;
        }
        
        void park(vehicle* v){
            if(IsFull()){
                cout<<"Full! couldnt park"<<endl;
                delete v;
                return;
            }

            string type = v->getType();
            pair<int, int> bestSpot = {-1, -1};
            if(type=="Bike"){
                if(freeBikeSpots.empty()){
                    cout<<"No Empty Bike Lane!"<<endl;
                    delete v;
                    return;
                }
                bestSpot = freeBikeSpots.top();
                freeBikeSpots.pop();
            }

            else if(type=="Car"){
                if(IsFull()){
                    cout<<"Full! couldnt park"<<endl;
                    delete v;
                    return;
                }
                if(freeCarSpots.empty()){
                    cout<<"No Empty Car Lane!"<<endl;
                    return;
                }
                bestSpot = freeCarSpots.top();
                freeCarSpots.pop();
            }

            else {
                if(IsFull()){
                    cout<<"Full! couldnt park"<<endl;
                    delete v;
                    return;
                }
                if(freeEVspots.empty()){
                    cout<<"No Empty EV Lane!"<<endl;
                    return;
                }
                bestSpot = freeEVspots.top();
                freeEVspots.pop();
            }

            if(isDuplicateEntry(v)){
                delete v;
                cout<<"Duplicate Entry!"<<endl;
                return;
            }

            spots[bestSpot.first][bestSpot.second] = v;
            curr++;
            time_t entry = v->getTime();
            cout << "Parked "<< type<<" in "<< bestSpot.first << " at "<< ctime(&entry) << endl;
            //------------------------------------------- MOVE TO PRIORITY QUEUES --------------------------------------------
            // string type = v->getType();
            // vector<pair<int, int>> searchZone;
            // if(type=="Bike"){
            //     searchZone.push_back({BikeZoneStart,BikeZoneEnd});
            // }
            // else if(type=="Car"){
            //     searchZone.push_back({0, 2});
            //     searchZone.push_back({6, capacity});
            // }
            // bool parked = false;

            // for(auto zone: searchZone){
            //     int start = zone.first;
            //     int end = zone.second;
            //     if(start>=capacity) continue;
            //     if(end>capacity) end = capacity;
            //     for(int i=start; i<end; i++){
            //         if(spots[i]==nullptr){
            //             spots[i] = v;
            //             curr++;
            //             cout << "Parked "<< type<<" in "<< i << endl;
            //             parked = true;
            //             break;
            //         }
            //     }
            //     if (parked) break;
            // }
            // if (!parked) {
            //     cout << "No space available in " << type << " Lane!" << endl;
            // }
            // ----------------------------------------------------------------------------------------
        }

        void leave(string plate) {
            time_t exitTime = time(nullptr);
            if(IsEmpty()) {
                cout<<"Lot is empty!"<<endl;
                return;
            }
            
            for(int i=0; i<capacity; i++){
                for(int j=0; j<3; j++){
                    if(spots[i][j] != nullptr && spots[i][j]->getPlate() == plate){
                        // calc
                        double fee = spots[i][j]->calculateFee(exitTime);
                        // output
                        cout << "\n--- RECEIPT ---" <<endl;
                        cout << "Vehicle: " << spots[i][j]->getPlate() <<endl;
                        cout << "Total Bill: $" << fee << endl;
                        cout << "---------------" << endl;
                        // memory
                        if(j==0) freeCarSpots.push({i, 0});
                        else if(j==1) freeBikeSpots.push({i, 1});
                        else if(j==2) freeEVspots.push({i, 2});
                        cout << "Slot " << i << " is now free." << endl;
                        delete spots[i][j];                         
                        spots[i][j] = nullptr;
                        curr--;
                        return;
                    }
                }
            cout << "Vehicle " << plate << " not found!" <<endl;
        }
        ~ParkingLot() {
            for (int i = 0; i < capacity; i++) {
               for(int j=0; j<3; j++){
                    if (spots[i][j] != nullptr) {
                        delete spots[i][j];
                        spots[i][j] = nullptr;
                    }
               }    
            }
            cout << "Parking Lot Closed. All vehicles cleared." << endl;
        }
};

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