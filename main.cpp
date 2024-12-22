#include <iostream>
#include "ControlLoop.hpp"
#include "Sensing.hpp"
#include "Logger.hpp"

using namespace std;

int main()
{

    int choice, num;
    bool landed = false;
    float yaw,pitch;
    ControlQueue commands;

    // First we load the file
    DataLogger Example("LastFlight.log");
    Example.ReadFromFile();

    ErrorLogger Errors;

    Errors.warning("Auto-generated warning (for demo) -- SAFE TO IGNORE");
    Errors.critical("Auto-generated critical error (for demo) -- SAFE TO IGNORE");

    // We will be implementing two data points for the sake of simplicity
    // but this system can be extended for as many data points as you like
    RocketSensors::FastList PitchList, YawList;
    RocketSensors::BinarySearchTree Sensors;
    Sensors.create('P', 10000);
    Sensors.create('Y', 10000);
    RocketSensors::DeadlineStack *PitchRaw;
    RocketSensors::DeadlineStack *YawRaw;

    RocketSensors::Sensor *SensorRoot = Sensors.GetRoot();
    RocketSensors::Sensor *SensorPosition = SensorRoot;

    while (SensorPosition)
    {
        if (SensorPosition->getType() == 'P')
        {
            PitchRaw = &(SensorPosition->Raw);
        }
        else if (SensorPosition->getType() == 'Y')
        {
            YawRaw = &(SensorPosition->Raw);
        }

        SensorPosition = Sensors.Traverse(SensorPosition);
    }

    vector<Logs> LastTenReadings = Example.getLastNReadings(10);

    for (Logs Reading : LastTenReadings)
    {
        PitchList.Insert(Reading.acceleration);
        YawList.Insert(Reading.bearing);

        RocketSensors::TransferToDeadlineStack(PitchList, *PitchRaw);
        RocketSensors::TransferToDeadlineStack(YawList, *YawRaw);
    }

    cout << "Welcome to Project SENTINEL" << endl;
    cout << "Please select 1 to intitiate preloaded flight sequence, 0 to terminate: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Initiating flight sequence." << endl;
        sleep_for(1000);
        cout << "Initialising control surfaces" << endl;
        cout << "Please enter number of grid fins: ";
        cin >> num;

        gridSystem fins(num);
        parachute Chutes[5];
        Chutes[0].DeploySequence = 1;
        Chutes[1].DeploySequence = 2;
        Chutes[2].DeploySequence = 0;
        Chutes[3].DeploySequence = 3;
        Chutes[4].DeploySequence = 4;


        for (int i = 0; i < num; i++)
        {
            fins.addNew();
        }
        while (landed == false)
        {
            try
            {
                RocketSensors::Node* PitchLatest = PitchRaw->Pop();
                RocketSensors::Node* YawLatest = YawRaw->Pop();

                pitch = PitchLatest->Get1D();
                yaw = YawLatest->Get1D();
            }
            catch(...)
            {
                landed = true;
            }

            gkeepvertical(fins,pitch,yaw);
        }

        bubbleSort(Chutes, 5);

        for (auto& chute: Chutes){
            sleep_for(1000);
            chute.deploychute();
        }

        cout << "General Information" << endl;
        cout << "Max Altitude: " << Example.MaxAltitude() << "m" << endl;
        cout << "Average Velocity: " << Example.AverageVelocity() << " m/s" << endl;
    }
    else if (choice == 0)
    {
        cout << "Exiting Program." << endl;
    }
}