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

    DataNode* head;
    DataNode* tail;
    size_t dataCount;
    static const int CACHE_SIZE = 20;
    string logFilepath;

    public:
    DataLogger(const string& filePath = "rocket_data.txt"): 
        head(nullptr), tail(nullptr), dataCount(0), logFilePath(filePath) {}

    string formatDataForFile(const Logs& log){
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6);
    
    // Format: timestamp,lat,lon,alt,bearing,velocity,accel,temp,pressure
    ss << data.timestamp << ","
       << data.gps.latitude << ","
       << data.gps.longitude << ","
       << data.gps.altitude << ","
       << data.bearing << ","
       << data.velocity << ","
       << data.acceleration << ","
       << data.temperature << ","
       << data.pressure;
    
    return ss.str();
    }

    void writeNodeToFile(const DataNode* node){
    if(!node)
        return;

    ofstream file(logFilepath, ios::app);
    if (!file) {
        throw runtime_error("Unable to open file for writing: " + logFilePath);
    }

    file << formatDataForFile(node->data) << endl;
    }

};
