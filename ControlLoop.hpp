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

    // Check if the queue is empty
    bool isEmpty() const
    {
        return front == nullptr;
    }

    // Enqueue: Add an element to the rear of the queue
    void enqueue(string value)
    {
        Node *newNode = new Node(value);

        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Dequeue: Remove and return the element from the front of the queue
    string dequeue()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }

        string data = front->data;
        Node *temp = front;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr; // If front becomes null, rear also becomes null
        }

        delete temp;
        return data;
    }


};
