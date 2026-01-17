#pragma once
#include <vector>
#include <queue>
#include "vehicles.h"
class ParkingLot{
    private:
        vector<vector<vehicle*>>spots;
        int capacity;
        int curr;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeCarSpots;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeBikeSpots;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeEVspots;
    public:
        ParkingLot();
        
        bool IsFull();
        
        bool IsEmpty();
        bool isDuplicateEntry(vehicle* v);

        void debug();
        
        void park(vehicle* v);
        void leave(string plate);
        ~ParkingLot();
};
