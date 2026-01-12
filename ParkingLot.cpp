#include<iostream>
#include<vector>
using namespace std;

class vehicle {
    protected:
        string licensePlate;
        string ownerName;
        int entryTime;
        int exitTime;

    public: 
        vehicle(){};
        vehicle(string plate, string name, int time){
            licensePlate = plate;
            ownerName = name;
            entryTime = time;
        }
        string getPlate(){
            return licensePlate;
        }
        int getTime(){
            return entryTime;
        }
        virtual int calculateFee(int exit)=0;
        virtual ~vehicle() {};
};
class bike : public vehicle {
    int rate = 20;
    public:
        bike(){};
        bike(string plate, string name, int time) : vehicle(plate, name, time) {}
        
        int calculateFee(int exit){
            int entry = getTime();
            int hours = (entry-exit);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
};

class EVBike : public bike {
    int rate = 5;
    public:
        EVBike(){};
        EVBike(string plate, string name, int time) : bike(plate, name, time){}
        int calculateFee(int exit){
            int entry = getTime();
            int hours = (entry-exit);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
};
class Car : public vehicle {
    int rate = 50;
    public:
        Car(){};
        Car (string plate, string name, int time) : vehicle(plate, name, time) {};
        int calculateFee(int exit){
            int entry = getTime();
            int hours = (entry-exit);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
};
class EVCar : public Car {
    int rate = 25;
    public:
        EVCar(){};
        EVCar(string plate, string name, int time) : Car(plate, name, time){}
        int calculateFee(int exit){
            int entry = getTime();
            int hours = (entry-exit);
            if(hours < 0) hours = 0;
            return hours*rate;
        }
};
class ParkingLot{
    private:
        vector<vehicle*>spots;
        int capacity;
        int curr;
    public:
        ParkingLot(int cap){
            spots.resize(cap, nullptr);
            capacity = cap;
            curr = 0;
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
                return;
            }
            for(int i=0; i<capacity; i++){
                if(spots[i]==nullptr){
                    spots[i] = v;
                    curr++;
                    cout << "Parked at Slot " << i << endl;
                    break;
                }
            }
            
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
                    delete spots[i];                         
                    spots[i] = nullptr;
                    curr--;
                    return;
                }
            }
            cout << "Vehicle " << plate << " not found!" <<endl;
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
    cout << "--- WELCOME TO LOCUS ---" << endl;
    cout << "Enter Max Capacity: ";
    int n;
    cin >> n;
    ParkingLot* pl = new ParkingLot(n);
    pl->debug();
    while(true){
        cout<<"What do you want to do?"<<endl;
        cout<<"1. Park"<<endl;
        cout<<"2. Leave"<<endl;
        int op;
        cin >> op;
        switch (op){
        case 1:
            parkTool(pl);
            break;
        case 2:
            leaveTool(pl);
            break;
        default:
            break;
        }
    }
}