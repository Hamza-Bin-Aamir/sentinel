#include "Physics.hpp"
#include <chrono>

#pragma once

namespace RocketSensors{
    
    enum PhysicsTypeNames {Scalar=0, Vect_3D, Vect_2D};

    union GenericPhysicsType{
        float Scalar;
        RocketPhysics::Vector2D Vect2D;
        RocketPhysics::Vector3D Vect3D;

        GenericPhysicsType(float Scalar): Scalar(Scalar) {};
        GenericPhysicsType(RocketPhysics::Vector2D Vect2D): Vect2D(Vect2D) {};
        GenericPhysicsType(RocketPhysics::Vector3D Vect3D): Vect3D(Vect3D) {};
    };

    // We will create a doubly linked list of vectors or scalars for our data

    /// @brief This node utilises a union to polymorph into three possible physics types: Vector 3D, Vector 2D, and float
    struct Node{
        PhysicsTypeNames SelectedType;
        Node* Next;
        GenericPhysicsType Data;
        std::chrono::milliseconds TimeStamp;
        
        Node(RocketPhysics::Vector3D Data): Data(Data), SelectedType(Vect_3D), TimeStamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), Next(nullptr) {};
        Node(RocketPhysics::Vector2D Data): Data(Data), SelectedType(Vect_2D), TimeStamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), Next(nullptr) {};
        Node(float Data): Data(Data), SelectedType(Scalar),TimeStamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), Next(nullptr) {};

        Node(RocketPhysics::Vector3D Data, std::chrono::milliseconds TimeStamp): Data(Data), SelectedType(Vect_3D), TimeStamp(TimeStamp), Next(nullptr) {};
        Node(RocketPhysics::Vector2D Data, std::chrono::milliseconds TimeStamp): Data(Data), SelectedType(Vect_2D), TimeStamp(TimeStamp), Next(nullptr) {};
        Node(float Data, std::chrono::milliseconds TimeStamp): Data(Data), SelectedType(Scalar), TimeStamp(TimeStamp), Next(nullptr) {};
        

        RocketPhysics::Vector3D Get3D(){
            if(SelectedType == Vect_3D){
                return Data.Vect3D;
            }
            return RocketPhysics::Vector3D(0, 0, 0, 'X');
        }

        RocketPhysics::Vector2D Get2D(){
            if(SelectedType == Vect_2D){
                return Data.Vect2D;
            }
            return RocketPhysics::Vector2D(0, 0, false, 'X');
        }

        float Get1D(){
            if(SelectedType == Scalar){
                return Data.Scalar;
            }
            return 0;
        }
    };

    
    /// @brief This is a specialised singly linked list that allows you to both access the latest value in O(1) and insert a value in O(1)
    class FastList{
    private:
        Node* head;
        Node* tail; 
        Node* last_read;
    
    public:
        FastList(): head(nullptr), tail(nullptr), last_read(nullptr) {};

        void Insert(RocketPhysics::Vector3D Insertion){
            // CASE A: There are no values in the list
            if(!head){
                head = new Node(Insertion);
                tail = head;
                return;
            }

            // CASE B: There are values already in the list
            tail->Next = new Node(Insertion);
            tail = tail->Next;
        }

        void Insert(RocketPhysics::Vector2D Insertion){
            // CASE A: There are no values in the list
            if(!head){
                head = new Node(Insertion);
                tail = head;
                return;
            }

            // CASE B: There are values already in the list
            tail->Next = new Node(Insertion);
            tail = tail->Next;
        }

        void Insert(float Insertion){
            // CASE A: There are no values in the list
            if(!head){
                head = new Node(Insertion);
                tail = head;
                return;
            }

            // CASE B: There are values already in the list
            tail->Next = new Node(Insertion);
            tail = tail->Next;
        }

        void Insert(RocketPhysics::Vector3D Insertion, std::chrono::milliseconds TimeStamp){
            // CASE A: There are no values in the list
            if(!head){
                head = new Node(Insertion, TimeStamp);
                tail = head;
                return;
            }

            // CASE B: There are values already in the list
            tail->Next = new Node(Insertion, TimeStamp);
            tail = tail->Next;
        }

        void Insert(RocketPhysics::Vector2D Insertion, std::chrono::milliseconds TimeStamp){
            // CASE A: There are no values in the list
            if(!head){
                head = new Node(Insertion, TimeStamp);
                tail = head;
                return;
            }

            // CASE B: There are values already in the list
            tail->Next = new Node(Insertion, TimeStamp);
            tail = tail->Next;
        }

        void Insert(float Insertion, std::chrono::milliseconds TimeStamp){
            // CASE A: There are no values in the list
            if(!head){
                head = new Node(Insertion, TimeStamp);
                tail = head;
                return;
            }

            // CASE B: There are values already in the list
            tail->Next = new Node(Insertion, TimeStamp);
            tail = tail->Next;
        }

        /// @brief O(1) access the unread value (FIFO)
        /// @return Unread node
        Node& ReadSequential(){
            // CASE A: NO VALUES EXIST YET
            if(!head){
                return *(new Node(0));
            }

            // CASE B: NOTHING HAS BEEN READ YET
            if(!last_read){
                last_read = head;
                return *last_read;
            }

            // CASE C: SOMETHING HAS BEEN READ, BUT NO NEW VALUE AVAILABLE
            if(!last_read->Next){
                return *last_read; // repeats old value
            }

            // CASE D: SOMETHING HAS BEEN READ AND A NEW VALUE IS AVAILABLE
            last_read = last_read->Next;
            return *last_read;
        }
    };
};