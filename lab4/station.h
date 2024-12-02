#ifndef STATION_H
#include <bits/stdc++.h>
#include "queue.h"

using namespace std;

// Abstract Dineable class
class Dineable {
public:
    virtual void serveDinner(string carID) = 0; // Serves dinner to the car
    virtual ~Dineable() {};
};

// Abstract Refuelable class
class Refuelable {
public:
    virtual void refuel(string carID, int consumption) = 0; // Refuels the car
    virtual ~Refuelable() {};
};

// Specific implementation for serving dinner to people
class PeopleDinner : public Dineable {
private:
    static int servedPeople; // Tracks the number of people served dinner

public:
    void serveDinner(string carID) override
    {
        servedPeople++; // Increment the count of served people
        cout << "Serving dinner to people in " << carID << endl; // Outputs the car being served
    }

    int getServedPeople() const { return servedPeople; } // Returns the count of people served dinner
};

// Static initialization of the served people count
int PeopleDinner::servedPeople = 0;

// Specific implementation for serving dinner to robots
class RobotDinner : public Dineable {
private:
    static int servedRobots; // Tracks the number of robots served dinner

public:
    void serveDinner(string carID) override
    {
        servedRobots++; // Increment the count of served robots
        cout << "Serving dinner to robots in " << carID << endl; // Outputs the car being served
    }

    int getServedRobots() const { return servedRobots; } // Returns the count of robots served dinner
};

// Static initialization of the served robots count
int RobotDinner::servedRobots = 0;

// Electric station for refueling electric cars
class ElectricStation : public Refuelable {
private:
    static int fueledElectric; // Tracks the number of electric cars refueled
    static int usedElectric;

public:
    void refuel(string carID, int consumption) override
    {
        fueledElectric++; // Increment the count of fueled electric cars
        usedElectric += consumption;
        cout << "Recharging battery for " << carID << endl; // Outputs the car being refueled
    }

    int getFueledElectric() const { return fueledElectric; } // Returns the count of fueled electric cars
    int getUsedElectric() const { return usedElectric; }
};

// Static initialization of the electric cars refueled count
int ElectricStation::fueledElectric = 0;
int ElectricStation::usedElectric = 0;

// Gas station for refueling gas cars
class GasStation : public Refuelable {
private:
    static int fueledGas; // Tracks the number of gas cars refueled
    static int usedGas;

public:
    void refuel(string carID, int consumption) override
    {
        fueledGas++; // Increment the count of fueled gas cars
        usedGas += consumption;
        cout << "Refueling gas for " << carID << endl; // Outputs the car being refueled
    }

    int getFueledGas() const { return fueledGas; } // Returns the count of fueled gas cars
    int getUsedGas() const { return usedGas; }
};

// Static initialization of the gas cars refueled count
int GasStation::fueledGas = 0;
int GasStation::usedGas = 0;


#define STATION_H

#endif //STATION_H
