#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "car.h"
#include "station.h"
#include "queue.h"

// Mock implementation for Dineable
class MockDineable : public Dineable {
public:
    void serveDinner(string carID) override {
        servedCars.push_back(carID);
    }
    vector<string> servedCars;
};

// Mock implementation for Refuelable
class MockRefuelable : public Refuelable {
public:
    void refuel(string carID, int consumption) override {
        refueledCars.push_back({carID, consumption});
    }
    vector<pair<string, int>> refueledCars;
};

// Mock implementation for ElectricStation
class MockElectricStation : public ElectricStation {
public:
    static int fueledElectric;
    static int usedElectric;

    void refuel(string carID, int consumption) override {
        fueledElectric++;
        usedElectric += consumption;
    }

    void reset() {
        fueledElectric = 0;
        usedElectric = 0;
    }

    int getFueledElectric() const { return fueledElectric; }
    int getUsedElectric() const { return usedElectric; }
};

int MockElectricStation::fueledElectric = 0;
int MockElectricStation::usedElectric = 0;

// Mock implementation for GasStation
class MockGasStation : public GasStation {
public:
    static int fueledGas;
    static int usedGas;

    void refuel(string carID, int consumption) override {
        fueledGas++;
        usedGas += consumption;
    }

    void reset() {
        fueledGas = 0;
        usedGas = 0;
    }

    int getFueledGas() const { return fueledGas; }
    int getUsedGas() const { return usedGas; }
};

int MockGasStation::fueledGas = 0;
int MockGasStation::usedGas = 0;

// Tests for ArrayQueue
TEST_CASE("ArrayQueue operations") {
    ArrayQueue<int> queue;

    SECTION("Enqueue and size") {
        queue.enqueue(1);
        queue.enqueue(2);
        REQUIRE(queue.size() == 2);
    }

    SECTION("Dequeue works correctly") {
        queue.enqueue(3);
        REQUIRE(queue.dequeue() == 3);
        REQUIRE(queue.isEmpty());
    }

    SECTION("Front retrieves the first element") {
        queue.enqueue(5);
        REQUIRE(queue.front() == 5);
    }
}

// Tests for Car class
TEST_CASE("Car class functionality") {
    Car car1(1, ELECTRIC, PEOPLE, true, 50);

    SECTION("Getters work as expected") {
        REQUIRE(car1.getId() == 1);
        REQUIRE(car1.getFuelType() == ELECTRIC);
        REQUIRE(car1.getPassengerType() == PEOPLE);
        REQUIRE(car1.getIsDining());
        REQUIRE(car1.getConsumption() == 50);
    }

    SECTION("Car initialization") {
        Car car2(2, GAS, ROBOTS, false, 30);
        REQUIRE(car2.getId() == 2);
        REQUIRE(car2.getFuelType() == GAS);
        REQUIRE(car2.getPassengerType() == ROBOTS);
        REQUIRE_FALSE(car2.getIsDining());
        REQUIRE(car2.getConsumption() == 30);
    }

    SECTION("Different fuel types") {
        Car car3(3, GAS, PEOPLE, true, 40);
        REQUIRE(car3.getFuelType() == GAS);
    }
}

// Tests for Dineable and Refuelable classes
TEST_CASE("MockDineable functionality") {
    MockDineable mockDine;

    SECTION("Serve dinner to a single car") {
        mockDine.serveDinner("Car1");
        REQUIRE(mockDine.servedCars.size() == 1);
        REQUIRE(mockDine.servedCars[0] == "Car1");
    }

    SECTION("Serve dinner to multiple cars") {
        mockDine.serveDinner("Car2");
        mockDine.serveDinner("Car3");
        REQUIRE(mockDine.servedCars.size() == 2);
        REQUIRE(mockDine.servedCars[1] == "Car3");
    }

    SECTION("No cars served yet") {
        REQUIRE(mockDine.servedCars.empty());
    }
}

TEST_CASE("MockRefuelable functionality") {
    MockRefuelable mockRefuel;

    SECTION("Refuel a single car") {
        mockRefuel.refuel("Car1", 100);
        REQUIRE(mockRefuel.refueledCars.size() == 1);
        REQUIRE(mockRefuel.refueledCars[0].first == "Car1");
        REQUIRE(mockRefuel.refueledCars[0].second == 100);
    }

    SECTION("Refuel multiple cars") {
        mockRefuel.refuel("Car2", 50);
        mockRefuel.refuel("Car3", 30);
        REQUIRE(mockRefuel.refueledCars.size() == 2);
        REQUIRE(mockRefuel.refueledCars[1].first == "Car3");
        REQUIRE(mockRefuel.refueledCars[1].second == 30);
    }

    SECTION("No cars refueled yet") {
        REQUIRE(mockRefuel.refueledCars.empty());
    }
}

// Tests for CarStation
TEST_CASE("CarStation operations") {
    MockDineable dineService;
    MockRefuelable refuelService;
    MockElectricStation electricStation;
    MockGasStation gasStation;
    CarStation station(&dineService, &refuelService);

    SECTION("Serve a single car") {
        Car car1(1, ELECTRIC, PEOPLE, true, 60);
        station.addCar(car1);
        station.serveCars();
        REQUIRE(dineService.servedCars.size() == 1);
        REQUIRE(refuelService.refueledCars.size() == 1);
    }

    SECTION("Serve multiple cars") {
        Car car2(2, GAS, ROBOTS, true, 50);
        Car car3(3, ELECTRIC, PEOPLE, false, 40);
        station.addCar(car2);
        station.addCar(car3);
        station.serveCars();
        REQUIRE(dineService.servedCars.size() == 1);
        REQUIRE(refuelService.refueledCars.size() == 2);
    }

    SECTION("Empty station queue") {
        station.serveCars();
        REQUIRE(dineService.servedCars.empty());
        REQUIRE(refuelService.refueledCars.empty());
    }
}

// Tests for Semaphore
TEST_CASE("Semaphore operations") {
    MockDineable peopleDine;
    MockDineable robotDine;
    MockElectricStation electricRefuel;
    MockGasStation gasRefuel;
    CarStation peopleElectric(&peopleDine, &electricRefuel);
    CarStation peopleGas(&peopleDine, &gasRefuel);
    CarStation robotElectric(&robotDine, &electricRefuel);
    CarStation robotGas(&robotDine, &gasRefuel);
    Semaphore semaphore(&peopleElectric, &peopleGas, &robotElectric, &robotGas);

    SECTION("Redirect cars to correct stations") {
        semaphore.addCarToQueue(Car(1, ELECTRIC, PEOPLE, true, 70));
        semaphore.addCarToQueue(Car(2, GAS, ROBOTS, false, 50));
        semaphore.processCars();

        REQUIRE(peopleDine.servedCars.size() == 1);
        REQUIRE(robotDine.servedCars.empty());
        REQUIRE(electricRefuel.getFueledElectric() == 1);
        REQUIRE(gasRefuel.getFueledGas() == 1);
    }

    SECTION("Process mixed cars") {
        semaphore.addCarToQueue(Car(3, GAS, PEOPLE, true, 30));
        semaphore.addCarToQueue(Car(4, ELECTRIC, ROBOTS, false, 20));
        semaphore.processCars();

        REQUIRE(peopleDine.servedCars.size() == 1);
        REQUIRE(robotDine.servedCars.empty());
        REQUIRE(electricRefuel.getFueledElectric() == 2);
        REQUIRE(gasRefuel.getFueledGas() == 2);
    }

    SECTION("Empty semaphore queue") {
        semaphore.processCars();
        REQUIRE(peopleDine.servedCars.empty());
        REQUIRE(robotDine.servedCars.empty());
        REQUIRE(electricRefuel.getFueledElectric() == 2);
        REQUIRE(gasRefuel.getFueledGas() == 2);
    }
}
