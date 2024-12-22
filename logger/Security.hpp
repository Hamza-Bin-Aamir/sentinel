#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

class Security{
    private:
    string password;

    public:
    //constructor with default password
    Security(const string& initialPassword = "admin") {
        password = initialPassword;
    }
    
    // Change password
    void setPassword(const string& newPassword) {
        if (newPassword.empty()) {
            throw runtime_error("Password cannot be empty");
        }
        password = newPassword;
    }

    bool checkPassword(const string& inputPassword) {
        if(password == inputPassword)
            return true;
        else
            return false;
    }
    bool writeToFile(const string& filePath, const string& content, 
                    const string& inputPassword) {
        if (!checkPassword(inputPassword)) {
            return false;  // Wrong password
        }
        
        try {
            ofstream file(filePath);
            if (!file) {
               throw runtime_error("Unable to open file for writing");
            }
            
            // Write content to file
            file << content;
            return true;
        } catch (...) {
           return "Unknown error occurred during file reading.";  // Any error during reading
        }
    }
    string readFromFile(const string& filePath, const string& inputPassword) {
        if (!checkPassword(inputPassword)) {
            return "Wrong Password";  
        }
        
        try {
            ifstream file(filePath);
            if (!file) {
                throw runtime_error("Unable to open file for reading: " + filePath);
            }
            
            string content;
            string line;
            while (getline(file, line)) {
                content += line + "\n";
            }
            
            return content;
        } catch (...) {
           return "Unknown error occurred during file reading.";  // Any error during reading
        }
    }
    
    // Check if file can be accessed
    bool canAccessFile(const string& inputPassword) {
        return checkPassword(inputPassword);
    }
};

#endif