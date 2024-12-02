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
    // Initialize services
    PeopleDinner peopleDinnerService;
    RobotDinner robotDinnerService;
    ElectricStation electricStationService;
    GasStation gasStationService;

    // Initialize car stations
    CarStation peopleElectricStation(&peopleDinnerService, &electricStationService);
    CarStation peopleGasStation(&peopleDinnerService, &gasStationService);
    CarStation robotElectricStation(&robotDinnerService, &electricStationService);
    CarStation robotGasStation(&robotDinnerService, &gasStationService);

    // Initialize semaphore
    Semaphore semaphore(&peopleElectricStation, &peopleGasStation, &robotElectricStation, &robotGasStation);

    // Read car JSON files from the "cars" folder
    const string folderPath = "./queue"; // Adjust folder path if needed
    for (const auto &entry: fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".json")
        {
            try
            {
                Car car = CarFactory::createCarFromJSON(entry.path().string());
                semaphore.addCarToQueue(car);
            } catch (const exception &e)
            {
                cerr << "Error processing file " << entry.path() << ": " << e.what() << endl;
            }
        }
    }

    // Process cars in the semaphore
    semaphore.processCars();

    // Summary of served dinner counts
    cout << "\nSummary of service:\n";
    cout << "People served dinner: " << peopleDinnerService.getServedPeople() << endl;
    cout << "Robots served dinner: " << robotDinnerService.getServedRobots() << endl;
    cout << "Electric cars refueled: " << electricStationService.getFueledElectric() << " with " <<
    electricStationService.getUsedElectric() << " kWh." << endl;
    cout << "Gas cars refueled: " << gasStationService.getFueledGas() << " with " << gasStationService.getUsedGas() <<
    " litres." << endl;

    return 0;
}

