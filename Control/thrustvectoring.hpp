// Code for basic thrust vectoring using a gimbaled engine

#include <iostream>
using namespace std;

class gimbal
{
    public:
    float axis1, axis2;
    float gimbal_constant;

    gimbal(int gc, float y_offset, float p_offset)
    {
        //initialising and centering gimbal
        axis1 = -1*y_offset;
        axis2 = -1*p_offset; 
        gimbal_constant = gc;
    }

    void yaw(float yaw)
    {
        axis1 = gimbal_constant*yaw;
        cout << "Yawing to " << yaw << " degrees"<< endl;

    }

    void pitch(float pitch)
    {
        axis1 = gimbal_constant*pitch;
        cout << "Pitching to " << pitch << " degrees."<< endl;
    }

    void keepvertical(float pitch, float yaw)
    {
        axis1 = gimbal_constant*yaw*-1;
        axis1 = gimbal_constant*pitch*-1;

        cout << "Control loop engaged. Rocket trajectory stabilized." << endl;
    }
};

