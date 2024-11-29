#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>

class Security{
    private:
    string password;

    public:
    SecurityUtils(const string& initialPassword = "admin") {
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
    
}