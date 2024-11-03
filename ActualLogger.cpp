#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

struct Coordinates{
    double latitude;
    double longitude;
    double altitude;

    Coordinates(): 
        latitude(0), longitude(0), altitude(0) {}
    Coordinates(double lat, double lon, double alt): 
        latitude(lat), longitude(lon), altitude(alt) {}
}

struct Logs{
    double timestamp;
    Coordinates gps;
    double bearing;      // in degrees
    double velocity;     // in m/s
    double acceleration; // in m/s²
    double temperature; // in Celsius
    double pressure;    // in hPa
    
   Logs(): 
        timestamp(0), bearing(0), velocity(0),
        acceleration(0), temperature(0), pressure(0) {}
}

class DataLogger{
    private:
    //For doubly linked list
    struct DataNode{
        Logs logs;
        DataNode* prev;
        DataNode* next;

        DataNode(Logs& d):
            data(d),prev(NULL),next(Null){0}
    };
};
