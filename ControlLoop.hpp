#include <iostream>
#include <unistd.h>
using namespace std;
#include "./Control/gridfins.hpp"
#include "./Recovery/parachute.hpp"

void bubbleSort(parachute* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].DeploySequence > arr[j + 1].DeploySequence) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j].DeploySequence;
                arr[j].DeploySequence = arr[j + 1].DeploySequence;
                arr[j +1].DeploySequence = temp;
            }
        }
    }
}

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

class ControlQueue
{
private:
    Node *front;
    Node *rear;

public:
    ControlQueue()
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

    // Get the front element (without removing it)
    string frontElement() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }

        return front->data;
    }
};
