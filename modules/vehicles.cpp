#include "vehicles.h"
#include <ctime>
#include <iostream>
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
vehicle::vehicle(string plate, string name, time_t time, int rate){
    licensePlate = plate;
    ownerName = name;
    entryTime = time;
    rate_per_hour = rate;
}
        
string vehicle::getPlate() const {
    return licensePlate;
}

time_t vehicle::getTime()const{
    return entryTime;
}
int vehicle::getRate()const{
    return rate_per_hour;
}
double vehicle::calculateFee(time_t exitTime){
    time_t entry = getTime();
    duration(entry, exitTime);
    double total_seconds = difftime(exitTime, entry);
    double hours_fractional = total_seconds / 3600.0;
    double total_cost = hours_fractional * rate_per_hour;
    return total_cost;
};

bike::bike(string plate, string name, time_t time) : vehicle(plate, name, time, 20) {}
bike::bike(string plate, string name, time_t time, int rate) : vehicle(plate, name, time, rate) {}
string bike::getType(){
    return "Bike"; 
}    

EVBike::EVBike(string plate, string name, time_t time) : bike(plate, name, time, 5){}
string EVBike::getType(){
    return "EV"; 
}

Car::Car (string plate, string name, time_t time) : vehicle(plate, name, time, 50) {};
Car::Car (string plate, string name, time_t time, int rate) : vehicle(plate, name, time, rate) {};
string Car::getType(){
    return "Car"; 
}

EVCar::EVCar(string plate, string name, time_t time) : Car(plate, name, time, 25){}
string EVCar::getType(){
    return "EV"; 
}