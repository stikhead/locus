#include<iostream>
#include<vector>
using namespace std;

class ParkingLot;
class Car {
    string licensePlate;
    string ownerName;
    friend void debug(ParkingLot p);
    friend class ParkingLot;
    public:
        Car(){
        };
        Car(string name, string plate){
            ownerName = name;
            licensePlate = plate;
        }
};

class ParkingLot{
    private:
        vector<Car>spots;
        int capacity;
        int curr;
        public:
        ParkingLot(int cap){
            spots.resize(cap);
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
        void park(Car c){
            if(IsFull()){
                cout<<"Full! couldnt park"<<endl;
                return;
            }
            for(int i=0; i<capacity; i++){
                if(spots[i].licensePlate==""){
                    spots[i] = c;
                    curr++;
                    cout<<"Parked"<<endl;
                    break;
                }
            }
            
        }
        void leave(Car c){
            if(IsEmpty()){
                return;
            }
            for(int i=0; i<capacity; i++){
                if(spots[i].licensePlate==c.licensePlate){
                    spots[i].licensePlate="";
                    curr--;
                    cout<<"Left "<<c.ownerName<<endl;
                    break;
                }
            }
        }
};

void debug(ParkingLot p) {
    cout << "\n--- [DEBUG VIEW] ---" << endl;
    for(int i=0; i<p.capacity; i++) {
        if(p.spots[i].licensePlate == "") 
            cout << "Slot " << i << ": [ Empty ]" << endl;
        else 
            cout << "Slot " << i << ": [ " << p.spots[i].licensePlate << " ]" << endl;
    }
    cout << "--------------------\n" << endl;
}
int main(){
    string n, p;
    cin >> n >> p;
    Car c(n, p);
    ParkingLot pl(5);
    pl.park(c);
    debug(pl);
    cin >> n >> p;
    Car c2(n, p);
    pl.leave(c);
    debug(pl);
    pl.park(c2);
    debug(pl);
    cin >> n >> p;
    Car c3(n, p);
    pl.park(c3);
    debug(pl);
    pl.leave(c2);
    debug(pl);
}