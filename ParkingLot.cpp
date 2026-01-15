#include<iostream>
#include<vector>
#include <queue>
#include <functional>
#include<sqlite3.h>
#include<string>
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
}class vehicle {
    protected:
        string licensePlate;
        string ownerName;
        int entryTime;
    public: 
        vehicle(){};
        vehicle(string plate, string name, int time){
            licensePlate = plate;
            ownerName = name;
            entryTime = time;
        }
        string getPlate() const {
            return licensePlate;
        }
        int getTime()const{
            return entryTime;
        }
        virtual string getType()=0;
        virtual int calculateFee(int exit)=0;
        virtual ~vehicle() {};
};
class bike : public vehicle {
    int rate = 20;
    public:
        bike(){};
        bike(string plate, string name, int time) : vehicle(plate, name, time) {}
        
        int calculateFee(int exit)override{
            int entry = getTime();
            int hours = (exit-entry);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
        string getType()override{
            return "Bike"; 
        }
};

class EVBike : public bike {
    int rate = 5;
    public:
        EVBike(){};
        EVBike(string plate, string name, int time) : bike(plate, name, time){}
        int calculateFee(int exit)override{
            int entry = getTime();
            int hours = (exit-entry);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
};
class Car : public vehicle {
    int rate = 50;
    public:
        Car(){};
        Car (string plate, string name, int time) : vehicle(plate, name, time) {};
        int calculateFee(int exit)override{
            int entry = getTime();
            int hours = (exit-entry);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
        
        string getType()override{
            return "Car"; 
        }
};
class EVCar : public Car {
    int rate = 25;
    public:
        EVCar(){};
        EVCar(string plate, string name, int time) : Car(plate, name, time){}
        int calculateFee(int exit)override{
            int entry = getTime();
            int hours = (exit-entry);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
};
class ParkingLot{
    private:
        vector<vehicle*>spots;
        int capacity;
        int curr;
        priority_queue<int, vector<int>, greater<int>> freeCarSpots;
        priority_queue<int, vector<int>, greater<int>> freeBikeSpots;
    public:
        ParkingLot(){
            spots.resize(100, nullptr);
            capacity = 100;
            curr = 0;
            for(int i=0; i<capacity; i++){
                if(i>=2 && i<5){
                    freeBikeSpots.push(i);
                }
                else {
                    freeCarSpots.push(i);
                }
            }
        }
        
        bool IsFull(){
            return curr==capacity;
        }
        
        bool IsEmpty(){
            return curr==0;
        }

        void debug() {
            cout << "\n--- [DEBUG VIEW] ---" << endl;
            for(int i=0; i<this->capacity; i++) {
                if(this->spots[i] == nullptr) 
                    cout << "Slot " << i << ": [ Empty ]" << endl;
                else 
                    cout << "Slot " << i << ": [ " << this->spots[i]->getPlate() << " ]" << endl;
            }
            cout << "--------------------\n" << endl;
        }
        
        void park(vehicle* v){
            if(IsFull()){
                cout<<"Full! couldnt park"<<endl;
                delete v;
                return;
            }
            string type = v->getType();
            int bestSpot = -1;
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
            spots[bestSpot] = v;
            curr++;
            cout << "Parked "<< type<<" in "<< bestSpot << endl;

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

        void leave(string plate, int exitTime) {
            if(IsEmpty()) {
                cout<<"Lot is empty!"<<endl;
                return;
            }
            for(int i=0; i<capacity; i++){
                if(spots[i] != nullptr && spots[i]->getPlate() == plate){
                    // calc
                    int fee = spots[i]->calculateFee(exitTime);
                    // output
                    cout << "\n--- RECEIPT ---" <<endl;
                    cout << "Vehicle: " << spots[i]->getPlate() <<endl;
                    cout << "Hours: " << (exitTime - spots[i]->getTime()) <<endl; 
                    cout << "Total Bill: $" << fee << endl;
                    cout << "---------------" << endl;
                    // memory
                    if(i>=2 && i<=4){
                        freeBikeSpots.push(i);
                    }
                    else {
                        freeCarSpots.push(i);
                    }
                    cout << "Slot " << i << " is now free." << endl;
                    delete spots[i];                         
                    spots[i] = nullptr;
                    curr--;
                    return;
                }
            }
            cout << "Vehicle " << plate << " not found!" <<endl;
        }
        ~ParkingLot() {
            for (int i = 0; i < capacity; i++) {
                if (spots[i] != nullptr) {
                    delete spots[i];
                    spots[i] = nullptr;
                }
            }
            cout << "Parking Lot Closed. All vehicles cleared." << endl;
        }
};

void parkTool(ParkingLot* pl){
    string name, plate;
    int time;
    int type;
    
    cout << "\nSELECT TYPE: 1.Car  2.Bike  3.EV-Car  4.EV-Bike" << endl;
    cout << "Input: ";
    cin >> type;

    cout << "Enter Name, Plate, EntryTime (e.g. Rahul DL01 10): ";
    cin >> name >> plate >> time;
    vehicle* v = nullptr;

    switch (type){
        case 1:
            v = new Car(plate, name, time);
            break;
        case 2:
            v = new bike(plate, name, time);
            break;
        case 3:
            v = new EVCar(plate, name, time);
            break;
        case 4:
            v = new EVBike(plate, name, time);
            break;
        default:
            break;
    }
    if (v == nullptr) {
        cout << "Invalid Vehicle Type!" << endl;
        return; // Don't call park()
    }
    pl->park(v);
    pl->debug();
}

void leaveTool(ParkingLot* pl){
    string p;
    int t;
    cout<<"Enter number plate and exit time: ";
    cin >> p;
    cin >> t;
    pl->leave(p, t);
    pl->debug();
}

int main(){
    sqlite3* db;
    int exit = 0;
    exit = sqlite3_open("parkingLot.db", &db);
    if(exit){
        cout<<"ERROR CREATING DATABSE: "<<sqlite3_errmsg(db)<<endl;
    }
    else {
        cout<<"SUCCESSFULLY CREATED DB!"<<endl;
    }
    sqlite3_close(db);
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