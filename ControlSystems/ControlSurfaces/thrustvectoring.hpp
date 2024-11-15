// Code for basic thrust vectoring using a gimbaled engine

class gimbal
{
    public:
    float axis1, axis2;
    float gimbal_constant;

    gimbal(int gc)
    {
        axis1 = axis2 = 0.0;
        gimbal_constant = gc;
    }

    void yaw(float yaw)
    {
        axis1 = gimbal_constant*yaw;
    }

    void pitch(float pitch)
    {
        axis1 = gimbal_constant*pitch;
    }

    void keepvertical(float pitch, float yaw)
    {
        axis1 = gimbal_constant*yaw*-1;
        axis1 = gimbal_constant*pitch*-1;
    }
};

