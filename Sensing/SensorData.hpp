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
        Node* Prev; // The Fast List class does NOT utilise this parameter
        GenericPhysicsType Data;
        std::chrono::milliseconds TimeStamp;
        
        Node(RocketPhysics::Vector3D Data): Data(Data), SelectedType(Vect_3D), TimeStamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), Next(nullptr), Prev(nullptr) {};
        Node(RocketPhysics::Vector2D Data): Data(Data), SelectedType(Vect_2D), TimeStamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), Next(nullptr), Prev(nullptr) {};
        Node(float Data): Data(Data), SelectedType(Scalar),TimeStamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), Next(nullptr), Prev(nullptr) {};

        Node(RocketPhysics::Vector3D Data, std::chrono::milliseconds TimeStamp): Data(Data), SelectedType(Vect_3D), TimeStamp(TimeStamp), Next(nullptr), Prev(nullptr) {};
        Node(RocketPhysics::Vector2D Data, std::chrono::milliseconds TimeStamp): Data(Data), SelectedType(Vect_2D), TimeStamp(TimeStamp), Next(nullptr), Prev(nullptr) {};
        Node(float Data, std::chrono::milliseconds TimeStamp): Data(Data), SelectedType(Scalar), TimeStamp(TimeStamp), Next(nullptr), Prev(nullptr) {};
        

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

        inline void ResetRead(){
            last_read = head;
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

    /// @brief The deadline stack allows us to discard old values based on a preset deadline, 
    /// This ensures that only recent data is passed on for further processing
    class DeadlineStack{
        private:
            Node* head;
            Node* tail;
            float DeadlineSeconds;

        public:
            DeadlineStack(): head(nullptr), tail(nullptr), DeadlineSeconds(0.1) {};
            DeadlineStack(float DeadlineSeconds): head(nullptr), tail(nullptr), DeadlineSeconds(DeadlineSeconds) {};

            /// @brief Add a 3D vector to the stack
            /// @param data the vector to insert
            /// @param timestamp the time the vector was inserted
            void Insert(RocketPhysics::Vector3D Insertion, std::chrono::milliseconds TimeStamp){
                // CASE A: There are no values in the list
                if(!head){
                    head = new Node(Insertion, TimeStamp);
                    tail = head;
                    return;
                }

                // CASE B: There are values already in the list
                tail->Next = new Node(Insertion, TimeStamp);
                tail->Next->Prev = tail;
                tail = tail->Next;
            }

            /// @brief Add a 2D vector to the stack
            /// @param data the vector to insert
            /// @param timestamp the time the vector was inserted
            void Insert(RocketPhysics::Vector2D Insertion, std::chrono::milliseconds TimeStamp){
                // CASE A: There are no values in the list
                if(!head){
                    head = new Node(Insertion, TimeStamp);
                    tail = head;
                    return;
                }

                // CASE B: There are values already in the list
                tail->Next = new Node(Insertion, TimeStamp);
                tail->Next->Prev = tail;
                tail = tail->Next;
            }

            /// @brief Add a scalar to the stack
            /// @param data the scalar to insert
            /// @param timestamp the time the vector was inserted
            void Insert(float Insertion, std::chrono::milliseconds TimeStamp){
                // CASE A: There are no values in the list
                if(!head){
                    head = new Node(Insertion, TimeStamp);
                    tail = head;
                    return;
                }

                // CASE B: There are values already in the list
                tail->Next = new Node(Insertion, TimeStamp);
                tail->Next->Prev = tail;
                tail = tail->Next;
            }

            /// @brief Shows the last node without popping it
            /// @return the last node
            inline Node Peek(){
                return *tail;
            }

            /// @brief The deadline stack allows us to discard old values based on a preset deadline,
            /// This ensures that only recent data is passed on for further processing
            Node* Pop() {
                Node* result = tail;

                if (!tail) {
                    std::cout << "Dead end" << std::endl << std::endl << std::endl;
                    throw 0;
                }

                // Check if the current tail node is outdated
                if (std::abs(static_cast<int>(tail->TimeStamp.count()) - 
                            static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                                std::chrono::system_clock::now().time_since_epoch()).count())) 
                    < int(DeadlineSeconds * 1000)) {

                    tail = tail->Prev;

                    return result; 
                }

                throw 0;
            }
    };


    /// @brief Primitive Data-Type representing a "virtual" sensor
    class Sensor{
    private:
        static int IterationCount;
        int ID;
        DeadlineStack Raw; // We use composition to enhance the functionality of this primitive
        DeadlineStack Stable; 

    public:
        Sensor* Right;
        Sensor* Left;
        Sensor* Parent;
        char Type;

        Sensor(float DeadlineSeconds){
            ID = IterationCount++;
            Raw = DeadlineStack(DeadlineSeconds);
            Stable = DeadlineStack(DeadlineSeconds);
            Right = nullptr;
            Left = nullptr;
            Parent = nullptr;
            Type = 'X';
        }

        Sensor(char Type): Raw(DeadlineStack()), Stable(DeadlineStack()), ID(IterationCount++), Right(nullptr), Left(nullptr), Parent(nullptr), Type(Type) {};

        Sensor() : Raw(DeadlineStack()), Stable(DeadlineStack()), ID(IterationCount++), Right(nullptr), Left(nullptr), Parent(nullptr), Type('X') {};


        inline void Insert(RocketPhysics::Vector3D Insertion, std::chrono::milliseconds TimeStamp){
            Raw.Insert(Insertion, TimeStamp);
        }

        inline void Insert(RocketPhysics::Vector2D Insertion, std::chrono::milliseconds TimeStamp){
            Raw.Insert(Insertion, TimeStamp);
        }

        inline void Insert(float Insertion, std::chrono::milliseconds TimeStamp){
            Raw.Insert(Insertion, TimeStamp);
        }

        /// @brief Call this regularly if you want to use the stable values of the sensor
        void Update(){
            try{
                Node* MedianS; Node* Median2D; Node* Median3D;
                float TotalS = 0.0f; RocketPhysics::Vector2D Total2D(0,0,false,'X'); RocketPhysics::Vector3D Total3D(0,0,0,'X');
                int FloatCount = 0, Vec2DCount = 0, Vec3DCount = 0;
                for(; FloatCount >= 2 || Vec2DCount >= 2 || Vec3DCount >= 2;){
                    Node* Buffer = Raw.Pop();

                    if(Buffer->SelectedType == Scalar){
                        TotalS += Buffer->Data.Scalar;
                        if(FloatCount == 1) {MedianS = Buffer;}
                        FloatCount++;  
                    }
                    else if(Buffer->SelectedType == Vect_2D){
                        Total2D = Total2D + Buffer->Data.Vect2D;
                        if(Vec2DCount == 1) {Median2D = Buffer;}
                        Vec2DCount++;
                    }
                    else{
                        Total3D = Total3D + Buffer->Data.Vect3D;
                        if(Vec3DCount == 1) {Median3D = Buffer;}
                        Vec3DCount++;
                    }
                }

                if(FloatCount >= 2){
                    Stable.Insert(TotalS/3, MedianS->TimeStamp);
                }
                else if(Vec2DCount >= 2){
                    Stable.Insert(Total2D/3, Median2D->TimeStamp);
                }
                else if(Vec3DCount >= 2){
                    Stable.Insert(Total3D/3, Median3D->TimeStamp);
                }
            }
            catch(...){
                return;
            }
        }

        int getID() const { return ID; }
        char getType() const {return Type; }
    };

    int Sensor::IterationCount = 0;

    // Organising our sensors
    class BinarySearchTree{
        private:
        Sensor* Root;
        /// @brief Performs an in-order traversal to update the stable estimates of all the sensors 
        /// @param Position What node we are currently on (used in recursion)
        void Update(Sensor* Position){
            if(!Position) {return;}
            Update(Position->Left);
            Position->Update();
            Update(Position->Right);
        }

        Sensor* Traverse(Sensor* CurrPosition, Sensor* TargetPosition) {
            if (CurrPosition == nullptr) {
                return nullptr;
            }

            // Visit the current node
            if (CurrPosition == TargetPosition) {
                // If the target node has a right child, return the right child
                if (CurrPosition->Right) {
                    return CurrPosition->Right;
                }

                // If the target node has no right child, find the next in-order successor
                Sensor* successor = CurrPosition;
                while (successor->Parent && successor == successor->Parent->Right) {
                    successor = successor->Parent;
                }

                if (successor->Parent) {
                    return successor->Parent; 
                } else {
                    return nullptr; 
                }
            }

            // Recursively traverse the left and right subtrees
            Sensor* nextSensor = Traverse(CurrPosition->Left, TargetPosition);
            if (nextSensor != nullptr) {
                return nextSensor;
            }

            return Traverse(CurrPosition->Right, TargetPosition);
        }
        public:
        
        BinarySearchTree(): Root(nullptr) {};

        Sensor* create(char Type){
            if(!Root){
                Root = new Sensor(Type);
                return Root;
            }

            Sensor* Insertion = new Sensor(Type);
            Sensor* Position = Root;

            while(Position->Left || Position->Right){
                if(Position->Left){
                    if(Position->Left->getID() > Insertion->getID()){
                        Position = Position->Left;
                    }
                }
                else if(Position->Right){
                    if(Position->Right->getID() < Insertion->getID()){
                        Position = Position->Right;
                    }
                }
            }

            if(Position->getID() < Insertion->getID()){
                Position->Right = Insertion;
            }
            else{
                Position->Left = Insertion;
            }

            return Insertion;
        }

        Sensor* create(float DeadlineSeconds){
            if(!Root){
                Root = new Sensor(DeadlineSeconds);
                return Root;
            }

            Sensor* Insertion = new Sensor(DeadlineSeconds);
            Sensor* Position = Root;

            while(Position->Left || Position->Right){
                if(Position->Left){
                    if(Position->Left->getID() > Insertion->getID()){
                        Position = Position->Left;
                    }
                }
                else if(Position->Right){
                    if(Position->Right->getID() < Insertion->getID()){
                        Position = Position->Right;
                    }
                }
            }

            Insertion->Parent = Position;

            if(Position->getID() < Insertion->getID()){
                Position->Right = Insertion;
            }
            else{
                Position->Left = Insertion;
            }

            return Insertion;
        }

        /// @brief Updates every available sensor in the tree,
        /// Uses in-order traversal
        void Update(){
            Update(Root); // Starts the traversal at root
        }

        
        /// @brief Gets the next sensor in order (uses pre-order traversal)
        /// @param TargetPosition 
        /// @return Sensor pointer for the latest
        Sensor* Traverse(Sensor* TargetPosition){
            return Traverse(Root, TargetPosition);
        }

        Sensor* GetRoot()
        { return Root;}
    };



    void TransferToDeadlineStack(RocketSensors::FastList& the_list, RocketSensors::DeadlineStack& the_stack){
        RocketSensors::Node NodeBuffer = the_list.ReadSequential();
        if(NodeBuffer.SelectedType == RocketSensors::Scalar){
            the_stack.Insert(NodeBuffer.Data.Scalar, NodeBuffer.TimeStamp);
        }
        else if(NodeBuffer.SelectedType == RocketSensors::Vect_2D){
            the_stack.Insert(NodeBuffer.Data.Vect2D, NodeBuffer.TimeStamp);
        }
        else {
            the_stack.Insert(NodeBuffer.Data.Vect3D, NodeBuffer.TimeStamp);
        }
    }


};