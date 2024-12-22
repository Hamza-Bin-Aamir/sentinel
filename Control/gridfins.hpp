#include <iostream>
#include <string>
#include <list>
#include <cstdlib> // using this for system
#include <thread> // using this for sleep
#include <chrono> // for timing
using namespace std;

/// @brief Sleeps for a certain amount of milliseconds
/// Credits to HighCommander4 on StackOverflow: https://stackoverflow.com/questions/4184468/sleep-for-milliseconds 
/// @param milliseconds time to sleep for in milliseconds
void sleep_for(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

struct finMount
{
    bool left;  // 1 for left mounted, 0 for right
    bool front; // 1 for front mounted, 0 for back
};

class gridfin
{
public:
    int num;
    float angle;
    finMount mount;

    gridfin(int n, bool l, bool f)
    {
        num = n;
        angle = 0.0;
        mount.left = l;
        mount.front = f;
    }
};

class gridSystem // Graph to connect the grid fins together and control them
{
public:
    int numV; // Number of Grid Fins
    list<gridfin> *adj;

    gridSystem(int V)
    {
        this->numV = V;
        adj = new list<gridfin>[V];
    }

    void addNew()
    {
        int n;
        string t;
        bool l, f;

        cout << "Please set the grid fin number: ";
        cin >> n;
        cout << "Please enter 1 if fin is left mounted, 0 if right mounted: ";
        cin >> l;
        cout << "Please enter 1 if fin is front mounted, 0 if back mounted: ";
        cin >> f;

        gridfin gnew(n, l, f);

        for (int i = 0; i < numV; i++)
        {
            for (auto temp : adj[i])
            {
                if ((temp.mount.left == gnew.mount.left) || (temp.mount.front == gnew.mount.front))
                {
                    adj[i].push_back(gnew);
                    adj[gnew.num].push_back(temp); // Add bidirectional connection
                }
            }
        }
    }

    void printGraphRecursive(int v)
    {
        cout << "-> " << v;

        for (auto x : adj[v])
        {
            printGraphRecursive(x.num);
        }
    }

    void printGraph()
    {
        for (int v = 0; v < numV; ++v)
        {
            cout << "Adjacency list of vertex " << v << ":\n head ";
            printGraphRecursive(v);
            cout << endl;
        }
    }
};

void gkeepvertical(gridSystem &graph, float pitch, float yaw)
{
    cout << "Control Loop engaged. " << endl
         << "Current Yaw: " << yaw << " degrees, Pitch: " << pitch << " degrees." << endl;
    sleep_for(2000);
    cout << "Rocket trajectory correcting..." << endl;

    for (int i = 0; i < graph.numV; i++)
    {
        for (auto &g : graph.adj[i])
        {
            if (pitch > 0)
            { // Nose Up
                if (g.mount.front == true)
                {
                    g.angle = ((pitch * 60) / 360);
                }
                else
                {
                    g.angle = -1 * ((pitch * 60) / 360);
                }
            }
            else if (pitch < 0)
            { // Nose Down
                if (g.mount.front == true)
                {
                    g.angle = -1 * ((pitch * 60) / 360);
                }
                else
                {
                    g.angle = ((pitch * 60) / 360);
                }
            }

            if (yaw > 0)
            { // Veer Right
                if (g.mount.left == true)
                {
                    g.angle += ((yaw * 60) / 360);
                }
                else
                {
                    g.angle -= ((yaw * 60) / 360);
                }
            }
            else if (yaw < 0)
            { // Veer Left
                if (g.mount.left == true)
                {
                    g.angle -= ((yaw * 60) / 360);
                }
                else
                {
                    g.angle += ((yaw * 60) / 360);
                }
            }
            
        }
    }
}

void gyaw(gridSystem &graph, float yaw)
{

    cout << "Yawing to " << yaw << " degrees" << endl;
    for (int i = 0; i < graph.numV; i++)
    {
        for (auto &g : graph.adj[i])
        {
            if (yaw > 0)
            { // Veer Right
                if (g.mount.left == 1)
                {
                    g.angle = ((yaw * 60) / 360);
                }
                else
                {
                    g.angle = -1 * ((yaw * 60) / 360);
                }
            }
            else if (yaw < 0)
            { // Veer Left
                if (g.mount.left == 1)
                {
                    g.angle = -1 * ((yaw * 60) / 360);
                }
                else
                {
                    g.angle = ((yaw * 60) / 360);
                }
            }
        }
    }
}

void gpitch(gridSystem &graph, float pitch)
{
    cout << "Pitching to " << pitch << " degrees" << endl;
    for (int i = 0; i < graph.numV; i++)
    {
        for (auto &g : graph.adj[i])
        {
            if (pitch > 0)
            { // Nose Up
                if (g.mount.front == 1)
                {
                    g.angle = ((pitch * 60) / 360);
                }
                else
                {
                    g.angle = -1 * ((pitch * 60) / 360);
                }
            }
            else if (pitch < 0)
            { // Nose Down
                if (g.mount.front == 1)
                {
                    g.angle = -1 * ((pitch * 60) / 360);
                }
                else
                {
                    g.angle = ((pitch * 60) / 360);
                }
            }
        }
    }
}

void airbrake(gridSystem &graph)
{
    cout << "Airbrake System engaged. Rocket velocity reduced" << endl;
    for (int i = 0; i < graph.numV; i++)
    {
        for (auto &g : graph.adj[i])
        {
            g.angle = 60;
        }
    }
}