#ifndef CAR_H
#include <bits/stdc++.h>
#include "queue.h"
#include "station.h"

using namespace std;

// Enum for fuel types (electric and gas)
enum FuelType {
    ELECTRIC,
    GAS
};

// Enum for passenger types (people and robots)
enum PassengerType {
    PEOPLE,
    ROBOTS
};

// Car class representing a car object
class Car {
private:
    int id;
    FuelType fuelType;
    PassengerType passengerType;
    bool isDining;
    int consumption;

public:
    Car(int id, FuelType fuel, PassengerType passenger, bool dine, int consumption)
        : id(id), fuelType(fuel), passengerType(passenger), isDining(dine), consumption(consumption) {}

    int getId() const { return id; }
    FuelType getFuelType() const { return fuelType; }
    PassengerType getPassengerType() const { return passengerType; }
    bool getIsDining() const { return isDining; }
    int getConsumption() const { return consumption; }
};

// Car station class that combines dining and refueling services
class CarStation {
private:
    Dineable *diningService; // Dining service for the station
    Refuelable *refuelingService; // Refueling service for the station
    ArrayQueue<Car> queue; // Queue of cars waiting for service

public:
    CarStation(Dineable *dine, Refuelable *refuel)
        : diningService(dine), refuelingService(refuel) {}

    // Function to process all cars in the queue
    void serveCars()
    {
        if (queue.isEmpty())
        {
            cout << "No cars in the queue.\n"; // Outputs if the queue is empty
            return;
        }

        while (!queue.isEmpty()) // Process each car in the queue
        {
            Car car = queue.dequeue(); // Dequeues the car from the queue
            cout << "Processing car with ID: " << car.getId() << endl;

            // Serve dinner if needed
            if (car.getIsDining())
            {
                diningService->serveDinner("Car " + to_string(car.getId())); // Calls the serveDinner method for dining
            }

            // Refuel cars
            refuelingService->refuel("Car " + to_string(car.getId()), car.getConsumption());

        }

        cout << "All cars have been processed.\n"; // Outputs once all cars have been processed
    }

    void addCar(Car car)
    {
        queue.enqueue(car); // Adds the car to the queue
    }
};

class Semaphore {
private:
    ArrayQueue<Car> carQueue; // Queue to manage incoming cars
    CarStation *peopleElectricStation;
    CarStation *peopleGasStation;
    CarStation *robotElectricStation;
    CarStation *robotGasStation;

public:
    Semaphore(CarStation *peopleElectric, CarStation *peopleGas, CarStation *robotElectric, CarStation *robotGas)
        : peopleElectricStation(peopleElectric),
          peopleGasStation(peopleGas),
          robotElectricStation(robotElectric),
          robotGasStation(robotGas) {}

    void addCarToQueue(const Car &car) {
        carQueue.enqueue(car); // Add car to the semaphore queue
    }

    void processCars() {
        while (!carQueue.isEmpty()) {
            Car car = carQueue.dequeue();

            // Redirect the car based on its attributes
            if (car.getPassengerType() == PEOPLE) {
                if (car.getFuelType() == ELECTRIC) {
                    peopleElectricStation->addCar(car);
                } else {
                    peopleGasStation->addCar(car);
                }
            } else if (car.getPassengerType() == ROBOTS) {
                if (car.getFuelType() == ELECTRIC) {
                    robotElectricStation->addCar(car);
                } else {
                    robotGasStation->addCar(car);
                }
            }
        }

        // Process all cars in each station's queue
        peopleElectricStation->serveCars();
        peopleGasStation->serveCars();
        robotElectricStation->serveCars();
        robotGasStation->serveCars();
    }
};

class CarFactory {
public:
    static Car createCarFromJSON(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + fileName);
        }

        nlohmann::json carData;
        file >> carData;

        // Extract data from JSON
        int id = carData.at("id").get<int>();
        string fuelTypeStr = carData.at("type").get<string>();
        string passengerTypeStr = carData.at("passengers").get<string>();
        bool isDining = carData.at("isDining").get<bool>();
        int consumption = carData.at("consumption").get<int>();

        // Map strings to enums
        FuelType fuelType = (fuelTypeStr == "ELECTRIC") ? ELECTRIC : GAS;
        PassengerType passengerType = (passengerTypeStr == "PEOPLE") ? PEOPLE : ROBOTS;

        return Car(id, fuelType, passengerType, isDining, consumption);
    }
};

#define CAR_H

#endif //CAR_H
