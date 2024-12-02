#ifndef CAR_H
#include <bits/stdc++.h>
#include "queue.h"
#include "station.h"

using namespace std;
namespace fs = filesystem;
using namespace chrono;

// Time intervals for various actions
const int STOP_TIMER = 5000; // Milliseconds to stop processing if no new files detected
const int CHECK_TIMER = 500; // Milliseconds to check for new files
const int WAIT_TIMER = 1000; // Milliseconds to send cars to specific stations

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
    // Constructor to initialize car attributes
    Car(int id, FuelType fuel, PassengerType passenger, bool dine, int consumption)
        : id(id), fuelType(fuel), passengerType(passenger), isDining(dine), consumption(consumption) {}

    // Getters for car attributes
    int getId() const { return id; }
    FuelType getFuelType() const { return fuelType; }
    PassengerType getPassengerType() const { return passengerType; }
    bool getIsDining() const { return isDining; }
    int getConsumption() const { return consumption; }
};

// Factory class to create Car objects from JSON data
class CarFactory {
public:
    // Method to create a car from JSON file
    static Car createCarFromJSON(const string &fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            throw runtime_error("Unable to open file: " + fileName);
        }

        json carData;
        file >> carData;

        // Extract car data from JSON
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

// Car station class that handles both dining and refueling services
class CarStation {
private:
    Dineable *diningService; // Dining service for the station
    Refuelable *refuelingService; // Refueling service for the station
    ArrayQueue<Car> queue; // Queue of cars waiting for service
    static int servedPeople;
    static int servedRobots;

public:
    // Constructor to initialize the dining and refueling services
    CarStation(Dineable *dine, Refuelable *refuel)
        : diningService(dine), refuelingService(refuel) {}

    // Function to serve all cars in the queue
    void serveCars()
    {
        while (!queue.isEmpty()) // Process each car in the queue
        {
            Car car = queue.dequeue(); // Dequeue a car
            // Serve dinner if needed
            if (car.getIsDining())
            {
                diningService->serveDinner("Car " + to_string(car.getId())); // Serve dinner for the car
            }

            // Refuel the car
            refuelingService->refuel("Car " + to_string(car.getId()), car.getConsumption());

            // Track the number of served people or robots
            if (car.getPassengerType() == PEOPLE)
                servedPeople++;
            else if (car.getPassengerType() == ROBOTS)
                servedRobots++;
        }
    }

    // Add a car to the queue
    void addCar(Car car)
    {
        queue.enqueue(car);
    }

    // Get the number of served people and robots
    int getServedPeople() const { return servedPeople; }
    int getServedRobots() const { return servedRobots; }
};

// Initialize static variables for served count
int CarStation::servedPeople = 0;
int CarStation::servedRobots = 0;

// Semaphore class to manage car queue and directory monitoring
class Semaphore {
private:
    ArrayQueue<Car> carQueue; // Queue for incoming cars
    CarStation *peopleElectricStation;
    CarStation *peopleGasStation;
    CarStation *robotElectricStation;
    CarStation *robotGasStation;
    bool stopProcessing = false; // Flag to stop processing
    string directoryPath;
    steady_clock::time_point lastFileTime;
    int carsProcessed = 0;

public:
    // Constructor to initialize the stations and directory path
    Semaphore(CarStation *peopleElectric, CarStation *peopleGas, CarStation *robotElectric, CarStation *robotGas,
              const string &dirPath)
        : peopleElectricStation(peopleElectric),
          peopleGasStation(peopleGas),
          robotElectricStation(robotElectric),
          robotGasStation(robotGas),
          directoryPath(dirPath)
    {
        lastFileTime = steady_clock::now();
    }

    // Add a car to the queue
    void addCarToQueue(const Car &car)
    {
        carQueue.enqueue(car);
    }

    // Monitor the directory for new car files and stop when no new files are found in 5 seconds
    void monitorDirectory()
    {
        while (!stopProcessing)
        {
            bool newFileFound = false;
            for (const auto &entry: fs::directory_iterator(directoryPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == ".json")
                {
                    try
                    {
                        // Create a car from the JSON file
                        Car car = CarFactory::createCarFromJSON(entry.path().string());
                        if (car.getId() > carsProcessed)
                        {
                            addCarToQueue(car); // Add the car to the queue
                            carsProcessed++;
                            newFileFound = true;
                        }
                    } catch (const runtime_error &e)
                    {
                        cout << "Error processing file " << entry.path() << ": " << e.what() << endl;
                    }
                }
            }

            if (newFileFound)
            {
                lastFileTime = steady_clock::now(); // Reset the timer if new file is found
            }

            // Stop processing if no new files found for 5 seconds and queue is empty
            if ((steady_clock::now() - lastFileTime > milliseconds(STOP_TIMER)) && carQueue.isEmpty())
            {
                stopProcessing = true;
                cout << "Stopping monitoring, no new files detected and queue is empty." << endl;
            }

            this_thread::sleep_for(milliseconds(CHECK_TIMER)); // Sleep before checking again
        }
    }

    // Sort cars into the correct stations based on fuel type and passenger type
    void sortCars()
    {
        while (!stopProcessing)
        {
            if (!carQueue.isEmpty())
            {
                Car car = carQueue.dequeue(); // Get a car from the queue
                this_thread::sleep_for(milliseconds(WAIT_TIMER));

                // Add the car to the appropriate station based on its type
                if (car.getPassengerType() == PEOPLE)
                {
                    if (car.getFuelType() == ELECTRIC)
                    {
                        peopleElectricStation->addCar(car);
                    }
                    else
                    {
                        peopleGasStation->addCar(car);
                    }
                }
                else if (car.getPassengerType() == ROBOTS)
                {
                    if (car.getFuelType() == ELECTRIC)
                    {
                        robotElectricStation->addCar(car);
                    }
                    else
                    {
                        robotGasStation->addCar(car);
                    }
                }
            }

            processCars(); // Process the cars in the stations

            this_thread::sleep_for(milliseconds(CHECK_TIMER)); // Sleep before checking again
        }
    }

    // Process cars at all stations
    void processCars()
    {
        peopleElectricStation->serveCars();
        peopleGasStation->serveCars();
        robotElectricStation->serveCars();
        robotGasStation->serveCars();
    }

    // Start processing and monitoring the directory in separate threads
    void startProcessing()
    {
        stopProcessing = false;

        // Start the directory monitoring and car sorting threads
        thread monitorThread([this]() { this->monitorDirectory(); });
        thread sortThread([this]() { this->sortCars(); });

        // Wait for both threads to finish
        monitorThread.join(); // Wait for the directory monitoring thread
        sortThread.join(); // Wait for the car sorting thread
    }

    // Stop the processing manually
    void stopProcessingQueue()
    {
        stopProcessing = true;
    }

    void finishProcess(PeopleDinner peopleDinner, RobotDinner robotDinner, GasStation gasStation,
                       ElectricStation electricStation)
    {
        ofstream output("finish.json");
        json finishData;

        // Get the counts from the services
        int peopleDineCount = peopleElectricStation->getServedPeople();
        int robotDineCount = robotElectricStation->getServedRobots();
        int gasCount = gasStation.getFueledGas();
        int electricCount = electricStation.getFueledElectric();

        // Get the dining and non-dining counts
        int diningCount = peopleDinner.getServedPeople() + robotDinner.getServedRobots();
        int notDiningCount = gasCount + electricCount - diningCount; // All cars minus those served dinner

        // Get the consumption data
        int electricConsumption = electricStation.getUsedElectric();
        int gasConsumption = gasStation.getUsedGas();

        // Construct the JSON data structure
        finishData["ELECTRIC"] = electricCount;
        finishData["GAS"] = gasCount;
        finishData["PEOPLE"] = peopleDineCount;
        finishData["ROBOTS"] = robotDineCount;
        finishData["DINING"] = diningCount;
        finishData["NOT_DINING"] = notDiningCount;

        // Add consumption data as a nested object
        finishData["CONSUMPTION"]["ELECTRIC"] = electricConsumption;
        finishData["CONSUMPTION"]["GAS"] = gasConsumption;

        // Write the data to the file
        if (output.is_open())
        {
            output << finishData.dump(4); // Pretty print with 4 spaces
            output.close();
            cout << "Finished processing. Data written to finish.json" << endl;
        }
        else
        {
            cout << "Failed to open file for writing" << endl;
        }
    }
};


#define CAR_H

#endif //CAR_H
