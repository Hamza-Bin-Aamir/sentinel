#include "Sensing.hpp"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    // Declare example data 
    RocketPhysics::Vector2D ExampleA(22.3f, 31.4f, false, 'F');
    RocketPhysics::Vector2D ExampleB(100.0f, 1.1f, true, 'V');
    RocketPhysics::Vector3D ExampleC(200.0f, 201.0f, 202.0f, 'F');
    RocketPhysics::Vector3D ExampleD(200.0f, 0.2f, 1.2f, 'V');

    
    #ifdef ENABLE_UTEST
        // UNIT TESTS
        assert(abs(ExampleA.GetX() - 22.3f) < TEST_FLOAT_PRECISION);
        assert(abs(ExampleA.GetY() - 31.4f) < TEST_FLOAT_PRECISION);
        assert(ExampleA.GetCartesian()[0] == ExampleA.GetX());
        assert(ExampleA.GetCartesian()[1] == ExampleA.GetY());
        assert(ExampleA.GetRadial()[0] - 38.5129848233f < TEST_FLOAT_PRECISION);
        assert(ExampleA.GetRadial()[1] - 0.953263405f < TEST_FLOAT_PRECISION);
        assert(ExampleA.GetType() == 'F');

        assert(abs(ExampleB.GetX() - 45.3596121426f) < TEST_FLOAT_PRECISION);
        assert(abs(ExampleB.GetY() - 89.1207360061f) < TEST_FLOAT_PRECISION);
        assert(ExampleB.GetCartesian()[0] == ExampleB.GetX());
        assert(ExampleB.GetCartesian()[1] == ExampleB.GetY());
        assert(ExampleB.GetRadial()[0] - 100.0f < TEST_FLOAT_PRECISION);
        assert(ExampleB.GetRadial()[1] - 1.1f < TEST_FLOAT_PRECISION);
        assert(ExampleB.GetType() == 'V');

        assert(abs(ExampleC.GetX() - 200.0f) < TEST_FLOAT_PRECISION);
        assert(abs(ExampleC.GetY() - 201.0f) < TEST_FLOAT_PRECISION);
        assert(abs(ExampleC.GetZ() - 202.0f) < TEST_FLOAT_PRECISION);
        assert(ExampleC.GetAll()[0] == ExampleC.GetX());
        assert(ExampleC.GetAll()[1] == ExampleC.GetY());
        assert(ExampleC.GetAll()[2] == ExampleC.GetZ());
        assert(ExampleC.GetType() == 'F');

        assert(abs(ExampleD.GetX() - 200.0f) < TEST_FLOAT_PRECISION);
        assert(abs(ExampleD.GetY() - 0.2f) < TEST_FLOAT_PRECISION);
        assert(abs(ExampleD.GetZ() - 1.2f) < TEST_FLOAT_PRECISION);
        assert(ExampleD.GetAll()[0] == ExampleD.GetX());
        assert(ExampleD.GetAll()[1] == ExampleD.GetY());
        assert(ExampleD.GetAll()[2] == ExampleD.GetZ());
        assert(ExampleD.GetType() == 'V');

        cout << "ALL TESTS PASSED!" << endl;
    #endif

    // Showing results
    cout << "A: "; ExampleA.ShowCartesian();
    cout << endl << "B: "; ExampleB.ShowRadial();
    cout << endl << "C: "; ExampleC.Show();
    cout << endl << "D: "; ExampleD.Show();

    // Testing some operations
    cout << endl << "A+B: "; (ExampleA + ExampleB).ShowCartesian();
    cout << endl << "A-B: "; (ExampleA - ExampleB).ShowCartesian();
    cout << endl << "A*2: "; (ExampleA * 2.0f).ShowCartesian();
    cout << endl << "A/2: "; (ExampleA / 2.0f).ShowCartesian();
    cout << endl << "A*B: "; cout << ExampleA * ExampleB; // Dot product
    cout << endl << "A^B: "; cout << (ExampleA ^ ExampleB); // Cross product (2D)

    cout << endl << "C+D: "; (ExampleC + ExampleD).Show();
    cout << endl << "C-D: "; (ExampleC - ExampleD).Show();
    cout << endl << "C*2: "; (ExampleC * 2.0f).Show();
    cout << endl << "C/2: "; (ExampleC / 2.0f).Show();
    cout << endl << "C*D: "; cout << ExampleC * ExampleD; // Dot product
    cout << endl << "C^D: "; (ExampleC ^ ExampleD).Show(); // Cross product (3D)

    cout << endl; return 0;
}