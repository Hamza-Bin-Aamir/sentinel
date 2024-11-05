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

    string formatDataForFile(const Logs& logs){
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

    Logs parseDataFromFile(const string& line) const {
        stringstream ss(line);
        string token;
        Logs logs;       
        try {
            //Done by following format
            getline(ss, token, ',');
            data.timestamp = stod(token);
            
            getline(ss, token, ',');
            data.gps.latitude = stod(token);
            
            getline(ss, token, ',');
            data.gps.longitude = stod(token);
            
            getline(ss, token, ',');
            data.gps.altitude = stod(token);
            
            getline(ss, token, ',');
            data.bearing = stod(token);
            
            getline(ss, token, ',');
            data.velocity = stod(token);
            
            getline(ss, token, ',');
            data.acceleration = stod(token);
            
            getline(ss, token, ',');
            data.temperature = stod(token);
            
            getline(ss, token, ',');
            data.pressure = stod(token);
            
        } catch (const exception& e) {
            throw runtime_error("Error parsing data line: " + line);
        }
        
        return logs;
    }

        void clearCache() {
        DataNode* current = head;
        while (current) {
            DataNode* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        dataCount = 0;
    }

    void addDataPoint(const Logs& logs){
        DataNode* newNode = new DataNode(logs);
        if(dataCount >= CACHE_SIZE){
            writeNodeToFile(head);
            DataNode* oldhead = head;
            head = head->next;
            if(head)
                head->prev = NULL;
            delete oldhead;
            dataCount--;
        }

        if(head == NULL)
            head = tail = newNode;
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        dataCount++;
    }

    // Data retrieval
    SensorData* getLatestData() const {
        if(tail)
            return &(tail->data);
        else
            return NULL;
    }

    vector<Logs> getLastNReadings(int n) const {
        vector<Logs> readings;
        DataNode* current = tail;
        int count = 0;

        while (current && count < n) {
            readings.push_back(current->data);
            current = current->prev;
            count++;
        }

        return readings;
    }

    //Analysis functions
    double AverageVelocity()const{
        if(!head)
            return 0.0;

        DataNode* current = head;
        double sum = 0.0;
        int count = 0;

        while(current){
            sum += current->data.velocity;
            count++;
            current = current->next;
        }

        if(count == 0)
            return 0.0;
        else
            return sum/count;
    }

    double calculateDistance(const Coordinates& coord1, const Coordinates& coord2) const {
        // Formula for distance between two GPS coordinates
        const double PI = 3.14159;
        const double R = 6371000; // Earth's radius in meters
        double lat1 = coord1.latitude * PI / 180;
        double lat2 = coord2.latitude * PI / 180;
        double deltaLat = (coord2.latitude - coord1.latitude) * PI / 180;
        double deltaLon = (coord2.longitude - coord1.longitude) * PI / 180;

        double a = sin(deltaLat/2) * sin(deltaLat/2) +
                  cos(lat1) * cos(lat2) *
                  sin(deltaLon/2) * sin(deltaLon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));

        return R * c;
    }
};
