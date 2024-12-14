#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <iostream>
#include "ActualLogger.hpp"
using namespace std;

class HashMap{
    private:
    struct HashNode {
        double timestamp;     // Key
        DataNode* dataPtr;    // Value
        HashNode* next;       // For handling collisions
        
        HashNode(double ts, DataNode* ptr): 
            timestamp(ts), 
            dataPtr(ptr), 
            next(nullptr) {}
    };

    static const int TABLE_SIZE = 100;
    HashNode* table[TABLE_SIZE];

    int hashFunction(double timestamp) {
    int int_timestamp = static_cast<int>(timestamp); 
    return int_timestamp % TABLE_SIZE;
    }

    public:
    HashMap() {
        // Initialize all table entries to nullptr
        for(int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    
    void insert(double timestamp, DataNode* dataPtr) {
        int index = hashFunction(timestamp);

        HashNode* newNode = new HashNode(timestamp, dataPtr);

        if(table[index] == nullptr) {
            table[index] = newNode;
        }
        // Handle collision by adding at the beginning of the list
        else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }
    
    DataNode* get(double timestamp) {
        int index = hashFunction(timestamp);
        HashNode* current = table[index];
        
        while(current) {
            if(current->timestamp == timestamp) {
                return current->dataPtr;
            }
            current = current->next;
        }
        
        return nullptr;  // Not found
    }
    

    void remove(double timestamp) {
        int index = hashFunction(timestamp);
        HashNode* current = table[index];
        HashNode* prev = nullptr;
        
        while(current && current->timestamp != timestamp) {
            prev = current;
            current = current->next;
        }
        
        
        if(current) {
            if(!prev) {
                // First node in the list
                table[index] = current->next;
            } else {
                // Middle or end of list
                prev->next = current->next;
            }
            delete current;
        }
    }

     // Destructor
    ~HashMap() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while(current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
        }
    }
};

#endif