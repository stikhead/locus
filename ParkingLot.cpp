#include<iostream>
#include<vector>
using namespace std;
class Car {
    string licensePlate;
    string ownerName;
    friend class ParkingLot;
    public:
        Car(string name, string plate){
            ownerName = name;
            licensePlate = plate;
        }
};

class ParkingLot{
    private:
        vector<Car> spots;
        int lotNumber = 0;
    public:
        void park(Car c){
            spots.push_back(c);
            lotNumber++;
            cout<<"car parked at: "<<lotNumber<<endl<<"owner: "<<c.ownerName<<endl;
        }
        void leave(Car c){
            cout<<"car left at: "<<lotNumber<<endl<<"owner: "<<c.ownerName<<endl;
            lotNumber--;

        }
};
int main(){
    string n, p;
    cin >> n >> p;
    Car c(n, p);
    ParkingLot pl;
    pl.park(c);
    cin >> n >> p;
    Car c2(n, p);
    pl.leave(c);
    pl.park(c2);
    cin >> n >> p;
    Car c3(n, p);
    pl.park(c3);
    pl.leave(c2);
}