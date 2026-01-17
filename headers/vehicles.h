#pragma once
#include <string>
#include<ctime>
void duration(time_t entry, time_t exitTime);
class vehicle {
    protected:
        string licensePlate;
        string ownerName;
        time_t entryTime;
        int rate_per_hour;
        public: 
        vehicle(){};
        vehicle(string plate, string name, time_t time, int rate);
        string getPlate() const;
        time_t getTime() const;
        int getRate() const;
        virtual string getType()=0;
        double calculateFee(time_t exitTime);
        virtual ~vehicle() {};
};

class bike : public vehicle {
    public:
        bike(){};
        bike(string plate, string name, time_t time);
        bike(string plate, string name, time_t time, int rate);
        string getType() override;
};

class EVBike : public bike {
    public:
    EVBike(){};
    EVBike(string plate, string name, time_t time);
    string getType() override;
};
class Car : public vehicle {
    public:
    Car(){};
    Car (string plate, string name, time_t time);
    Car (string plate, string name, time_t time, int rate);
    string getType() override;
};
class EVCar : public Car {
    public:
    EVCar(){};
    EVCar(string plate, string name, time_t time);
    string getType()override;
};