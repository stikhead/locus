#include<iostream>
#include<vector>
using namespace std;

class ParkingLot;
class vehicle {
    string licensePlate;
    string ownerName;
    int entryTime;
    public: 
        friend class ParkingLot;
        friend void debug(ParkingLot p);
        vehicle(){};
        vehicle(string plate, string name, int time){
            licensePlate = plate;
            ownerName = name;
            entryTime = time;
        }

        string getPlate(){
            return licensePlate;
        }
        virtual ~vehicle() {};
};

class bike : public vehicle {
    public:
        bike(){};
        bike(string plate, string name, int time) : vehicle(plate, name, time) {}
};
class Car : public vehicle {
    public:
        Car(){};
        Car (string plate, string name, int time) : vehicle(plate, name, time) {};
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
        friend void debug(ParkingLot p);
        bool IsFull(){
            return curr==capacity;
        }
        bool IsEmpty(){
            return curr==0;
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
                    cout<<"Parked"<<endl;
                    break;
                }
            }
            
        }
       void leave(string plate) {
        if(IsEmpty()) return;
        
        for(int i=0; i<capacity; i++){
            if(spots[i] != nullptr && spots[i]->getPlate() == plate){
                cout << "Left " << spots[i]->getPlate() << endl;
                spots[i] = nullptr;
                curr--;
                break;
            }
        }
    }
};

void debug(ParkingLot p) {
    cout << "\n--- [DEBUG VIEW] ---" << endl;
    for(int i=0; i<p.capacity; i++) {
        if(p.spots[i] == nullptr) 
            cout << "Slot " << i << ": [ Empty ]" << endl;
        else 
            cout << "Slot " << i << ": [ " << p.spots[i]->licensePlate << " ]" << endl;
    }
    cout << "--------------------\n" << endl;
}

void parkTool(ParkingLot* pl){
    string m, p;
    int t;
    bool isCar = true;
    cin >> isCar;
    cin >> m >> p;
    cin >> t;
    if(isCar){
        Car* v = new Car(p, m, t);    
        pl->park(v);
        debug(*pl);
    }
    else {
        bike* v = new bike(p, m, t);
        pl->park(v);
        debug(*pl);
        pl->leave(p);
        debug(*pl);
    }
}

int main(){
    cout<<"Enter Number of vehicles"<<endl;
    int n;
    cin >> n;
    ParkingLot* pl = new ParkingLot(n);
    debug(*pl);
    for(int i=0; i<n; i++){
        cout<<"Bool Name Plate Time"<<endl;
        parkTool(pl);
    }
    
}