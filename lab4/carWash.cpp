#include <bits/stdc++.h>
using namespace std;

// Abstract Queue class
template<typename T>
class Queue {
public:
    virtual ~Queue() {};

    virtual void enqueue(const T &item) = 0; // Adds an item to the queue

    virtual T dequeue() = 0; // Removes and returns an item from the queue

    virtual T front() const = 0; // Returns the item at the front without removing it

    virtual bool isEmpty() const = 0; // Checks if the queue is empty

    virtual size_t size() const = 0; // Returns the size of the queue
};

// Array-based Queue implementation
template<typename T>
class ArrayQueue : public Queue<T> {
private:
    vector<T> data; // Stores the items in the queue

public:
    void enqueue(const T &item) override
    {
        data.push_back(item); // Adds the item to the end of the queue
    }

    T dequeue() override
    {
        if (isEmpty()) throw runtime_error("Queue is empty"); // Throws error if the queue is empty
        T frontItem = data.front(); // Stores the front item
        data.erase(data.begin()); // Removes the front item
        return frontItem;
    }

    T front() const override
    {
        if (isEmpty()) throw runtime_error("Queue is empty"); // Throws error if the queue is empty
        return data.front(); // Returns the front item without removing it
    }

    bool isEmpty() const override
    {
        return data.empty(); // Returns true if the queue is empty
    }

    size_t size() const override
    {
        return data.size(); // Returns the size of the queue
    }
};

// Abstract Dineable class
class Dineable {
public:
    virtual void serveDinner(string carID) = 0; // Serves dinner to the car
    virtual ~Dineable() {};
};

// Abstract Refuelable class
class Refuelable {
public:
    virtual void refuel(string carID) = 0; // Refuels the car
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

public:
    void refuel(string carID) override
    {
        fueledElectric++; // Increment the count of fueled electric cars
        cout << "Recharging battery for " << carID << endl; // Outputs the car being refueled
    }

    int getFueledElectric() const { return fueledElectric; } // Returns the count of fueled electric cars
};

// Static initialization of the electric cars refueled count
int ElectricStation::fueledElectric = 0;

// Gas station for refueling gas cars
class GasStation : public Refuelable {
private:
    static int fueledGas; // Tracks the number of gas cars refueled

public:
    void refuel(string carID) override
    {
        fueledGas++; // Increment the count of fueled gas cars
        cout << "Refueling gas for " << carID << endl; // Outputs the car being refueled
    }

    int getFueledGas() const { return fueledGas; } // Returns the count of fueled gas cars
};

// Static initialization of the gas cars refueled count
int GasStation::fueledGas = 0;

// Enum for fuel types (electric and gas)
enum FuelType {
    ELECTRIC,
    GAS
};

// Car class representing a car object
class Car {
private:
    string name; // Car name
    int passengers; // Number of passengers
    bool requiresDinner; // Whether the car needs dinner
    bool requiresRefuel; // Whether the car needs refueling
    FuelType fuelType; // The type of fuel the car uses (electric or gas)

public:
    Car(string carName, int numPassengers, bool needsDinner, bool needsRefuel, FuelType fuel)
        : name(carName), passengers(numPassengers), requiresDinner(needsDinner), requiresRefuel(needsRefuel),
          fuelType(fuel) {}

    string getName() const { return name; }
    int getPassengers() const { return passengers; }
    bool getRequiresDinner() const { return requiresDinner; }
    bool getRequiresRefuel() const { return requiresRefuel; }
    FuelType getFuelType() const { return fuelType; }
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
            cout << "Processing car: " << car.getName() << " with " << car.getPassengers() << " passengers.\n";

            // Serve dinner if needed
            if (car.getRequiresDinner())
            {
                diningService->serveDinner(car.getName()); // Calls the serveDinner method for dining
            }

            // Check if car needs refueling
            if (car.getRequiresRefuel())
            {
                // If the car requires refuel but the station is for a different fuel type
                if ((car.getFuelType() == ELECTRIC && dynamic_cast<ElectricStation *>(refuelingService) == nullptr) ||
                    (car.getFuelType() == GAS && dynamic_cast<GasStation *>(refuelingService) == nullptr))
                {
                    cout << car.getName() <<
                            " cannot be refueled here because the station is not compatible with its fuel type.\n";
                }
                else
                {
                    refuelingService->refuel(car.getName()); // Calls the refuel method for refueling
                }
            }
        }

        cout << "All cars have been processed.\n"; // Outputs once all cars have been processed
    }

    void addCar(Car car)
    {
        queue.enqueue(car); // Adds the car to the queue
    }
};

int main()
{
    PeopleDinner peopleDinnerService;
    RobotDinner robotDinnerService;
    ElectricStation electricStationService;
    GasStation gasStationService;

    // Car stations for humans and robots
    CarStation stationForHumansElectric(&peopleDinnerService, &electricStationService);
    // A station for human electric cars
    CarStation stationForRobotsGas(&robotDinnerService, &gasStationService); // A station for robot gas cars
    CarStation stationForPeopleGas(&peopleDinnerService, &gasStationService); // A station for human gas cars
    CarStation stationForRobotsElectric(&robotDinnerService, &electricStationService);
    // A station for robot electric cars

    // Add cars to stationForHumansElectric (Electric Station for Humans)
    stationForHumansElectric.addCar(Car("Tesla Model S", 4, false, true, ELECTRIC));
    // No dinner and refuel (electric car)
    stationForHumansElectric.addCar(Car("Audi e-Tron", 2, false, true, GAS)); // No dinner, needs refuel (gas car)
    stationForHumansElectric.addCar(Car("Nissan Leaf", 5, true, false, ELECTRIC));
    // Needs dinner, no refuel (electric car)
    stationForHumansElectric.addCar(Car("Chevy Bolt", 1, false, true, ELECTRIC));
    // No dinner, needs refuel (electric car)
    stationForHumansElectric.addCar(Car("BMW i3", 6, true, true, ELECTRIC)); // Needs dinner and refuel (electric car)

    // Add cars to stationForRobotsGas (Gas Station for Robots)
    stationForRobotsGas.addCar(Car("Ford Mustang", 3, true, true, GAS)); // Needs dinner and refuel (gas car)
    stationForRobotsGas.addCar(Car("Volkswagen Golf", 6, false, true, ELECTRIC)); // No dinner, needs refuel (gas car)
    stationForRobotsGas.addCar(Car("Toyota Camry", 1, true, false, GAS)); // Needs dinner, no refuel (gas car)
    stationForRobotsGas.addCar(Car("Honda Accord", 4, false, true, ELECTRIC)); // No dinner, needs refuel (gas car)
    stationForRobotsGas.addCar(Car("Chevrolet Malibu", 2, true, true, GAS)); // Needs dinner and refuel (gas car)

    // Add cars to stationForPeopleGas (Gas Station for People)
    stationForPeopleGas.addCar(Car("Jeep Grand Cherokee", 2, true, true, GAS)); // Needs dinner and refuel (gas car)
    stationForPeopleGas.addCar(Car("Hyundai Kona", 3, false, true, ELECTRIC)); // No dinner, needs refuel (gas car)
    stationForPeopleGas.addCar(Car("Mazda CX-5", 5, true, false, GAS)); // Needs dinner, no refuel (gas car)
    stationForPeopleGas.addCar(Car("Subaru Outback", 1, false, true, GAS)); // No dinner, needs refuel (gas car)
    stationForPeopleGas.addCar(Car("Dodge Durango", 4, true, true, ELECTRIC)); // Needs dinner and refuel (gas car)

    // Add cars to stationForRobotsElectric (Electric Station for Robots)
    stationForRobotsElectric.addCar(Car("Rivian R1T", 3, true, true, GAS)); // Needs dinner and refuel (electric car)
    stationForRobotsElectric.addCar(Car("Lucid Air", 6, false, true, GAS)); // No dinner, needs refuel (electric car)
    stationForRobotsElectric.addCar(Car("Ford Mustang Mach-E", 1, true, false, ELECTRIC));
    // Needs dinner, no refuel (electric car)
    stationForRobotsElectric.addCar(Car("Porsche Taycan", 4, false, true, ELECTRIC));
    // No dinner, needs refuel (electric car)
    stationForRobotsElectric.addCar(Car("Polestar 2", 2, true, true, ELECTRIC));
    // Needs dinner and refuel (electric car)


    // Serve all cars at stationForHumansElectric (Electric Station for Humans)
    cout << "\nServing cars at the human electric station (Electric Station):\n";
    stationForHumansElectric.serveCars();

    // Serve all cars at stationForRobotsGas (Gas Station for Robots)
    cout << "\nServing cars at the robot gas station (Gas Station):\n";
    stationForRobotsGas.serveCars();

    // Serve all cars at stationForPeopleGas (Gas Station for People)
    cout << "\nServing cars at the people gas station (Gas Station):\n";
    stationForPeopleGas.serveCars();

    // Serve all cars at stationForRobotsElectric (Electric Station for Robots)
    cout << "\nServing cars at the robot electric station (Electric Station):\n";
    stationForRobotsElectric.serveCars();

    // Summary of served dinner counts
    cout << "\nSummary of service:\n";
    cout << "People served dinner: " << peopleDinnerService.getServedPeople() << endl;
    cout << "Robots served dinner: " << robotDinnerService.getServedRobots() << endl;
    cout << "Electric cars refueled: " << electricStationService.getFueledElectric() << endl;
    cout << "Gas cars refueled: " << gasStationService.getFueledGas() << endl;

    return 0;
}

