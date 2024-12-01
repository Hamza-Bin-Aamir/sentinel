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
    bool pyrocharge;

    parachute()
    {
        pyrocharge = 0;
    }

    void deploychute()
    {
        GPS pos;
        
        pyrocharge = 1;
        cout << "Recovery System engaged." << endl << "Parachute Deployed." << endl;

        cout << "Rocket Coordinates: " << endl;

        for (int i = 0; i < 20; i++)
        {
            pos = getpos();
            cout << "Lat: " << pos.lat << "Lon: " << pos.lon << endl;
        }
    }
};