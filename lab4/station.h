#ifndef STATION_H
#include <bits/stdc++.h>
#include "queue.h"

using namespace std;

// Abstract class for dining service
class Dineable {
public:
    virtual void serveDinner(string carID) = 0; // Pure virtual function to serve dinner to the car
    virtual ~Dineable() {}; // Virtual destructor
};

// Abstract class for refueling service
class Refuelable {
public:
    virtual void refuel(string carID, int consumption) = 0; // Pure virtual function to refuel the car
    virtual ~Refuelable() {}; // Virtual destructor
};

// Class to serve dinner to people in the car
class PeopleDinner : public Dineable {
private:
    static int servedPeople; // Static variable to track the number of people served dinner

public:
    // Implementation of serveDinner for people
    void serveDinner(string carID) override
    {
        servedPeople++; // Increment the count of served people
        cout << "Serving dinner to people in " << carID << endl; // Output the car being served
    }

    // Returns the count of people served dinner
    int getServedPeople() const { return servedPeople; }
};

// Static initialization of the served people count
int PeopleDinner::servedPeople = 0;

// Class to serve dinner to robots in the car
class RobotDinner : public Dineable {
private:
    static int servedRobots; // Static variable to track the number of robots served dinner

public:
    // Implementation of serveDinner for robots
    void serveDinner(string carID) override
    {
        servedRobots++; // Increment the count of served robots
        cout << "Serving dinner to robots in " << carID << endl; // Output the car being served
    }

    // Returns the count of robots served dinner
    int getServedRobots() const { return servedRobots; }
};

// Static initialization of the served robots count
int RobotDinner::servedRobots = 0;

// Class for refueling electric cars
class ElectricStation : public Refuelable {
private:
    static int fueledElectric; // Static variable to track the number of electric cars refueled
    static int usedElectric; // Static variable to track the total electric consumption

public:
    // Implementation of refuel for electric cars
    void refuel(string carID, int consumption) override
    {
        fueledElectric++; // Increment the count of fueled electric cars
        usedElectric += consumption; // Increment the total electric consumption
        cout << "Recharging battery for " << carID << endl; // Output the car being refueled
    }

    // Returns the count of electric cars refueled
    int getFueledElectric() const { return fueledElectric; }

    // Returns the total electric consumption
    int getUsedElectric() const { return usedElectric; }
};

// Static initialization of electric car counters
int ElectricStation::fueledElectric = 0;
int ElectricStation::usedElectric = 0;

// Class for refueling gas cars
class GasStation : public Refuelable {
private:
    static int fueledGas; // Static variable to track the number of gas cars refueled
    static int usedGas; // Static variable to track the total gas consumption

public:
    // Implementation of refuel for gas cars
    void refuel(string carID, int consumption) override
    {
        fueledGas++; // Increment the count of fueled gas cars
        usedGas += consumption; // Increment the total gas consumption
        cout << "Refueling gas for " << carID << endl; // Output the car being refueled
    }

    // Returns the count of gas cars refueled
    int getFueledGas() const { return fueledGas; }

    // Returns the total gas consumption
    int getUsedGas() const { return usedGas; }
};

// Static initialization of gas car counters
int GasStation::fueledGas = 0;
int GasStation::usedGas = 0;

#define STATION_H

#endif //STATION_H
