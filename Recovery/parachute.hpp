// Contains code for deployment of parachute

#include <iostream>
using namespace std;

struct GPS
{
    float lat, lon;
};

GPS getpos()
{
    //In real world application this will be pulling values from GPS module

    GPS coord;

    coord.lat = 34.0691;
    coord.lon = 72.6441;

    //For now using coordinates of GIKI

    return coord;
}

class parachute
{
    public:
    int DeploySequence;
    bool pyrocharge;

    parachute()
    {
        pyrocharge = 0;
    }

    void deploychute()
    {
        GPS pos = getpos();
        
        pyrocharge = 1;
        cout << "Chute #" << DeploySequence << " engaged." << endl << "Parachute Deployed at " << pos.lat << ", " << pos.lon << endl; 

        // cout << "Rocket Coordinates: " << endl;

        // for (int i = 0; i < 20; i++)
        // {
        //     pos = getpos();
        //     cout << "Lat: " << pos.lat << "Lon: " << pos.lon << endl;
        // }
    }
};