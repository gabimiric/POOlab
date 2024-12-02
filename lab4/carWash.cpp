#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "queue.h"
#include "station.h"
#include "car.h"

using namespace std;
using namespace nlohmann;
namespace fs = filesystem;

int main()
{
    // Initialize service objects for dining and fueling stations
    PeopleDinner peopleDinnerService; // Service for serving dinner to people
    RobotDinner robotDinnerService; // Service for serving dinner to robots
    ElectricStation electricStationService; // Service for electric fueling
    GasStation gasStationService; // Service for gas fueling

    // Initialize car stations for different types of cars (people/robots, electric/gas)
    CarStation peopleElectricStation(&peopleDinnerService, &electricStationService);
    // Station for people with electric cars
    CarStation peopleGasStation(&peopleDinnerService, &gasStationService); // Station for people with gas cars
    CarStation robotElectricStation(&robotDinnerService, &electricStationService);
    // Station for robots with electric cars
    CarStation robotGasStation(&robotDinnerService, &gasStationService); // Station for robots with gas cars

    string directoryPath = "./queue"; // Path to the directory where car JSON files will be read

    // Initialize the Semaphore object which manages the car processing
    Semaphore semaphore(&peopleElectricStation, &peopleGasStation, &robotElectricStation, &robotGasStation,
                        directoryPath);

    // Start processing cars in a separate thread to allow parallel execution
    thread processThread([&semaphore]()
    {
        semaphore.startProcessing(); // Start the semaphore processing in a separate thread
    });

    // Run the Python script that generates car JSONs in a separate thread
    // This ensures that the car processing does not block the generation of new files
    thread pythonScriptThread([]()
    {
        system("python3 generator.py"); // Run the Python script to generate the car JSON files
    });

    // Wait for the Python script to finish execution (join the thread)
    pythonScriptThread.join(); // Block until the Python script completes

    // Wait for the semaphore processing thread to finish
    // The car processing will continue in the background until it's completed
    processThread.join(); // Block until the car processing finishes

    // After processing all cars, write the final results to a JSON file
    // This will include the statistics of the car processing
    semaphore.finishProcess(peopleDinnerService, robotDinnerService, gasStationService, electricStationService);

    return 0; // Return 0 to indicate successful execution
}
