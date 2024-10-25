#include <string>
using namespace std;

struct finMount
{
    bool left; // 1 for left mounted, 0 for right
    bool front; // 1 for front mounted, 0 for back
};

class gridfin
{
    public:
    string name;
    string type;
    float angle;
    finMount mount;

    gridfin(string n, string t, bool dir, bool l, bool f)
    {
        name = n;
        type = t;
        angle = 0.0;
        mount.left = l;
        mount.front = f;
    }

};

void gkeepvertical(gridfin g[], int gnum, float pitch, float yaw)
{
    if (pitch > 0) // Nose Up
    {
        for (int i = 0; i < gnum; i++)
        {
            if (g[i].mount.front == 1)
            {
                g[i].angle = pitch;
            }
            if (g[i].mount.front == 0)
            {
                g[i].angle = -1*pitch;
            }
        }
    }

    if (pitch < 0) // Nose Up
    {
        for (int i = 0; i < gnum; i++)
        {
            if (g[i].mount.front == 1)
            {
                g[i].angle = -1*pitch;
            }
            if (g[i].mount.front == 0)
            {
                g[i].angle = pitch;
            }
        }
    }

    if (yaw > 0) // Nose Up
    {
        for (int i = 0; i < gnum; i++)
        {
            if (g[i].mount.left == 1)
            {
                g[i].angle = yaw;
            }
            if (g[i].mount.left == 0)
            {
                g[i].angle = -1*yaw;
            }
        }
    }

    if (yaw < 0) // Nose Up
    {
        for (int i = 0; i < gnum; i++)
        {
            if (g[i].mount.left == 1)
            {
                g[i].angle = -1*yaw;
            }
            if (g[i].mount.front == 0)
            {
                g[i].angle = yaw;
            }
        }
    }
}