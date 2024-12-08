#include <iostream>
using namespace std;
#include "./Control/gridfins.hpp"

struct Node
{
    string data;
    Node *next;

    Node(string d)
    {
        this->data = d;
        next = nullptr;
    }
};

class Queue
{
private:
    Node *front;
    Node *rear;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

};
