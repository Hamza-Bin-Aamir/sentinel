// BEWARE
// WE ARE NOT SCIENTISTS, WE ARE ENGINEERS
// What you will see in this file will defy all common expectation, sense, and logic
// Please do not touch anything unless you are absolutely sure of what you are doing

// We use the pragma once flag to tell the compiler to prevent multiple exclusions of this program
#pragma once

#include <iostream>
#include <cmath>


namespace RocketPhysics{
// Unless a better value for gravity is given, use standard gravity
#ifndef GRAVITY
    #define GRAVITY 9.80655
#endif

/// THE VECTOR PRIMITIVE
/// @brief The vector 2D data type is a primitive data type that can contain a 2D representation of a float, you may use a direction, magnitude or a magnitude X, Y to create or access the data, but it is stored in the magnitude X, Y formats
class Vector2D{
private:
    float DataX;
    float DataY;
    /// @brief This contains the unit for the value in this vector. There are no guidelines except that 'X' means undefined
    char DataType;

public:
    ///@param DataA float, a magnitude
    ///@param DataB float, EITHER a magnitude OR a direction (degrees)
    ///@param Angle boolean, true if the second value is an angle
    ///@param DType character, the datatype of the value
    Vector2D(const float& DataA, const float& DataB, const bool& Angle, const char& DType='X') {
        Set(DataA, DataB, Angle, DType); 
    }   

    /// @brief Sets all the values for the vector
    /// @param DataA float, a magnitude
    /// @param DataB float, EITHER a magnitude OR a direction (degrees)
    /// @param Angle boolean, true if the second value is an angle
    /// @param DType character, the datatype of the value
    void Set(const float& DataA, const float& DataB, const bool& Angle, const char& DType='X'){
        DataType = DType;
        // If both values are magnitudes, enter them directly
        if(!Angle){
            DataX = DataA;
            DataY = DataB;
            return;
        }

        // If the second value is an angle, calculate the actual direction
        DataX = DataA * cos(DataB);
        DataY = DataA * sin(DataB);
    }    

    /// @brief Setter for the datatype
    /// @param newType What the datatype should be (character)
    inline void SetType(const char& newType){
        DataType = newType;
    }

    /// @brief Getter for the datatype
    /// @return A copy of the datatype (character)
    inline char GetType() const{
        return DataType;
    }

    /// @brief Getter for the data (in radial format)
    /// @return a pair of floats, where the first value is the magnitude and the second value is an angle
    inline float* GetRadial() const{
        return new float[2] {sqrt(float(pow(DataX, 2) + pow(DataY, 2))), atan2(DataY, DataX)};
    }

    /// @brief Getter for the data (in magnitude X, Y format)
    /// @return a pair of floats, where the first value is the magnitude X and the second value is the magnitude Y
    inline float* GetCartesian() const{
        return new float[2] {DataX, DataY};
    }

    /// @brief Getter for the X coordinate
    /// @return The x coordinate raw
    inline float GetX() const{
        return DataX;
    }

    /// @brief Getter for the Y coordinate
    /// @return The y coordinate raw
    inline float GetY() const{
        return DataY;
    }

    /// @brief Addition operator
    /// @param v The vector to add 
    /// @return A new vector as the result
    inline Vector2D operator+(const Vector2D& v) const{
        return Vector2D(DataX + v.GetX(), DataY + v.GetY(), false, DataType);
    }

    /// @brief Subtraction operator
    /// @param v The vector to subtract
    /// @return A new vector as the result
    inline Vector2D operator-(const Vector2D& v) const {
        return Vector2D(DataX - v.GetX(), DataY - v.GetY(), false, DataType);
    }

    /// @brief Division operator
    /// @param s The scalar to divide by
    /// @return A new vector as the result
    inline Vector2D operator/(const float& s){
        return Vector2D(DataX/s, DataY/s, false, 'X');
    }

    
    /// @brief Multiplication operator
    /// @param s The scalar to divide by
    /// @return A new vector as the result
    inline Vector2D operator*(const float& s){
        return Vector2D(DataX*s, DataY*s, false, 'X');
    }

    /// @brief Dot product
    /// @param v The vector to multiply by
    /// @return A floating point result of the dot product
    inline float operator*(const Vector2D& v){
        return DataX * v.GetX() + DataY * v.GetY();
    }

    /// @brief Cross product
    /// @param v The vector to multiply by
    /// @return A floating point result of the cross product
    inline float operator^(const Vector2D& v){
        return DataX * v.GetY() - DataY * v.GetX();
    }

    /// @brief Shows the vector in X/Y format
    inline void ShowCartesian(){
        std::cout << "X: " << DataX << ", Y: " << DataY;
    }

    /// @brief Shows the vector in Magnitude/Theta format
    inline void ShowRadial(){
        std::cout << "Magnitude: " << GetRadial()[0] << ", Theta: " << GetRadial()[1];
    }
};

/// THE VECTOR PRIMITIVE
/// @brief The vector 3D data type is a primitive data type that can contain a 3D representation of a float, 
/// you may use a direction, magnitude or a magnitude X, Y, Z to create or access the data, 
/// but it is stored in the magnitude X, Y, Z formats
class Vector3D {
private:
    float DataX;
    float DataY;
    float DataZ;
    /// @brief This contains the unit for the value in this vector. There are no guidelines except that 'X' means undefined
    char DataType; 

public:
    /// @param DataA float, a magnitude
    /// @param DataB float, EITHER a magnitude OR a direction (degrees) 
    /// @param DataC float, EITHER a magnitude OR an angle (degrees) 
    /// @param Angle boolean, true if the second and third values are angles
    /// @param DType character, the datatype of the value
    Vector3D(const float& DataA, const float& DataB, const float& DataC, const bool& Angle, const char& DType='X') {
        Set(DataA, DataB, DataC, Angle, DType);
    }

    /// @brief Sets all the values for the vector
    /// @param DataA float, a magnitude
    /// @param DataB float, EITHER a magnitude OR a direction (degrees) 
    /// @param DataC float, EITHER a magnitude OR an angle (degrees) 
    /// @param Angle boolean, true if the second and third values are angles
    /// @param DType character, the datatype of the value
    void Set(const float& DataA, const float& DataB, const float& DataC, const bool& Angle, const char& DType='X') {
        DataType = DType;
        // If both values are magnitudes, enter them directly
        if (!Angle) {
            DataX = DataA;
            DataY = DataB;
            DataZ = DataC;
            return;
        }

        // If the second and third values are angles, calculate the actual direction (spherical coordinates)
        float theta = DataB * (M_PI / 180.0f); // Azimuth (longitude)
        float phi = DataC * (M_PI / 180.0f);   // Elevation (latitude)

        DataX = DataA * sin(phi) * cos(theta);
        DataY = DataA * sin(phi) * sin(theta);
        DataZ = DataA * cos(phi);
    }

    /// @brief Setter for the datatype
    /// @param newType What the datatype should be (character)
    inline void SetType(const char& newType) {
        DataType = newType;
    }

    /// @brief Getter for the datatype
    /// @return A copy of the datatype (character)
    inline char GetType() const {
        return DataType;
    }

    /// @brief Getter for the data (in spherical format)
    /// @return a pair of floats, where the first value is the magnitude, 
    /// the second value is the azimuth (theta), and the third value is the elevation (phi)
    inline float* GetSpherical() const {
        float* result = new float[3];
        result[0] = sqrt(DataX * DataX + DataY * DataY + DataZ * DataZ); 
        result[1] = atan2(DataY, DataX); // Azimuth
        result[2] = acos(DataZ / result[0]); // Elevation
        return result;
    }

    /// @brief Getter for the data (in magnitude X, Y, Z format)
    /// @return a pair of floats, where the first value is the magnitude X, 
    /// the second value is the magnitude Y, and the third value is the magnitude Z
    inline float* GetCartesian() const {
        return new float[3] {DataX, DataY, DataZ}; 
    }

    /// @brief Getter for the X coordinate
    /// @return The x coordinate raw
    inline float GetX() const {
        return DataX;
    }

    /// @brief Getter for the Y coordinate
    /// @return The y coordinate raw
    inline float GetY() const {
        return DataY;
    }

    /// @brief Getter for the Z coordinate
    /// @return The z coordinate raw
    inline float GetZ() const {
        return DataZ;
    }

    /// @brief Addition operator
    /// @param v The vector to add
    /// @return A new vector as the result
    inline Vector3D operator+(const Vector3D& v) const {
        return Vector3D(DataX + v.GetX(), DataY + v.GetY(), DataZ + v.GetZ(), false, DataType);
    }

    /// @brief Subtraction operator
    /// @param v The vector to subtract
    /// @return A new vector as the result
    inline Vector3D operator-(const Vector3D& v) const {
        return Vector3D(DataX - v.GetX(), DataY - v.GetY(), DataZ - v.GetZ(), false, DataType);
    }

    /// @brief Division operator
    /// @param s The scalar to divide by
    /// @return A new vector as the result
    inline Vector3D operator/(const float& s) {
        return Vector3D(DataX / s, DataY / s, DataZ / s, false, 'X');
    }

    /// @brief Multiplication operator
    /// @param s The scalar to divide by
    /// @return A new vector as the result
    inline Vector3D operator*(const float& s) {
        return Vector3D(DataX * s, DataY * s, DataZ * s, false, 'X');
    }

    /// @brief Dot product
    /// @param v The vector to multiply by
    /// @return A floating point result of the dot product
    inline float operator*(const Vector3D& v) {
        return DataX * v.GetX() + DataY * v.GetY() + DataZ * v.GetZ();
    }

    /// @brief Cross product
    /// @param v The vector to multiply by
    /// @return A new Vector3D as the result of the cross product
    inline Vector3D operator^(const Vector3D& v) const {
        return Vector3D(
            DataY * v.GetZ() - DataZ * v.GetY(),
            DataZ * v.GetX() - DataX * v.GetZ(),
            DataX * v.GetY() - DataY * v.GetX(),
            false, 'X'
        );
    }

    /// @brief Shows the vector in X/Y/Z format
    inline void ShowCartesian() const {
        std::cout << "X: " << DataX << ", Y: " << DataY << ", Z: " << DataZ;
    }

    /// @brief Shows the vector in Magnitude/Theta/Phi format
    inline void ShowSpherical() const {
        float* spherical = GetSpherical();
        std::cout << "Magnitude: " << spherical[0] 
                << ", Theta (Azimuth): " << spherical[1] * 180.0 / M_PI 
                << ", Phi (Elevation): " << spherical[2] * 180.0 / M_PI;
        delete[] spherical;
    }
};
};