#include "Sensing.hpp"
#include <iostream>

using namespace std;

int main(){
    // Basic tests on the primitives 
    RocketPhysics::Vector2D ExampleA(22.3f, 31.4f, false, 'F');
    RocketPhysics::Vector2D ExampleB(100.0f, 1.1f, true, 'V');
    RocketPhysics::Vector3D ExampleC(200.0f, 200.0f, 200.0f, false, 'F');
    RocketPhysics::Vector3D ExampleD(200.0f, 0.2f, 1.2f, true, 'V');

    cout << "A: "; ExampleA.ShowCartesian();
    cout << endl << "B: "; ExampleB.ShowRadial();
    cout << endl << "C: "; ExampleC.ShowCartesian();
    cout << endl << "D: "; ExampleD.ShowSpherical();

    // Testing some operations
    cout << endl << "A+B: "; (ExampleA + ExampleB).ShowCartesian();
    cout << endl << "A-B: "; (ExampleA - ExampleB).ShowCartesian();
    cout << endl << "A*2: "; (ExampleA * 2.0f).ShowCartesian();
    cout << endl << "A/2: "; (ExampleA / 2.0f).ShowCartesian();
    cout << endl << "A*B: "; cout << ExampleA * ExampleB; // Dot product
    cout << endl << "A^B: "; cout << (ExampleA ^ ExampleB); // Cross product (2D)

    cout << endl << "C+D: "; (ExampleC + ExampleD).ShowCartesian();
    cout << endl << "C-D: "; (ExampleC - ExampleD).ShowCartesian();
    cout << endl << "C*2: "; (ExampleC * 2.0f).ShowCartesian();
    cout << endl << "C/2: "; (ExampleC / 2.0f).ShowCartesian();
    cout << endl << "C*D: "; cout << ExampleC * ExampleD; // Dot product
    cout << endl << "C^D: "; (ExampleC ^ ExampleD).ShowCartesian(); // Cross product (3D)

    cout << endl; return 0;
}