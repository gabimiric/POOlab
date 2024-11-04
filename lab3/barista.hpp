#ifndef BARISTA_HPP
#define BARISTA_HPP

#include <bits/stdc++.h>
#include "coffee.hpp"

using namespace std;

class Barista {
private:
    vector<unique_ptr<Coffee>> coffeeMenu; // Stores the list of coffee objects

    // Clears the console screen based on the operating system
    void clearScreen() {
        #ifdef _WIN32
            system("cls"); // For Windows
        #else
            system("clear"); // For Unix/Linux
        #endif
    }

    // Waits for the user to press Enter to continue
    void waitForEnter() {
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get(); // Wait for the user to press Enter
    }

public:
    Barista() = default; // Default constructor

    // Factory methods to create coffee objects
    unique_ptr<Americano> createAmericano(Intensity intensity, int water) {
        return unique_ptr<Americano>(new Americano(intensity, water));
    }

    unique_ptr<Cappuccino> createCappuccino(Intensity intensity, int milk) {
        return unique_ptr<Cappuccino>(new Cappuccino(intensity, milk));
    }

    unique_ptr<SyrupCappuccino> createSyrupCappuccino(Intensity intensity, int milk, SyrupType syrupType) {
        return unique_ptr<SyrupCappuccino>(new SyrupCappuccino(intensity, milk, syrupType));
    }

    unique_ptr<PumpkinSpiceLatte> createPumpkinSpiceLatte(Intensity intensity, int milk, int spice) {
        return unique_ptr<PumpkinSpiceLatte>(new PumpkinSpiceLatte(intensity, milk, spice));
    }

    // Creates a coffee menu by prompting the user for coffee details
    void createCoffeeMenu() {
        clearScreen(); // Clear the screen before displaying the menu
        int choice;
        do {
            cout << "Select the type of coffee to add to the menu:\n";
            cout << "1. Americano\n";
            cout << "2. Cappuccino\n";
            cout << "3. Syrup Cappuccino\n";
            cout << "4. Pumpkin Spice Latte\n";
            cout << "5. Done\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: { // Adding an Americano
                    int intensity, water;
                    cout << "Select intensity (0: LIGHT, 1: NORMAL, 2: STRONG): ";
                    cin >> intensity;
                    cout << "Enter ml of Water: ";
                    cin >> water;
                    coffeeMenu.emplace_back(createAmericano(static_cast<Intensity>(intensity), water));
                    break;
                }
                case 2: { // Adding a Cappuccino
                    int intensity, milk;
                    cout << "Select intensity (0: LIGHT, 1: NORMAL, 2: STRONG): ";
                    cin >> intensity;
                    cout << "Enter ml of Milk: ";
                    cin >> milk;
                    coffeeMenu.emplace_back(createCappuccino(static_cast<Intensity>(intensity), milk));
                    break;
                }
                case 3: { // Adding a Syrup Cappuccino
                    int intensity, milk, syrupType;
                    cout << "Select intensity (0: LIGHT, 1: NORMAL, 2: STRONG): ";
                    cin >> intensity;
                    cout << "Enter ml of Milk: ";
                    cin >> milk;
                    cout << "Select syrup type (0: MACADAMIA, 1: VANILLA, 2: COCONUT, 3: CARAMEL, 4: CHOCOLATE, 5: POPCORN): ";
                    cin >> syrupType;
                    coffeeMenu.emplace_back(createSyrupCappuccino(static_cast<Intensity>(intensity), milk,
                                                                  static_cast<SyrupType>(syrupType)));
                    break;
                }
                case 4: { // Adding a Pumpkin Spice Latte
                    int intensity, milk, spice;
                    cout << "Select intensity (0: LIGHT, 1: NORMAL, 2: STRONG): ";
                    cin >> intensity;
                    cout << "Enter ml of Milk: ";
                    cin >> milk;
                    cout << "Enter mg of Pumpkin Spice: ";
                    cin >> spice;
                    coffeeMenu.emplace_back(createPumpkinSpiceLatte(static_cast<Intensity>(intensity), milk, spice));
                    break;
                }
                case 5:
                    cout << "Finished creating the coffee menu.\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n"; // Handle invalid input
            }
        } while (choice != 5);
        waitForEnter(); // Wait for user input before returning
    }

    // Displays the current coffee menu
    void displayCoffeeMenu() {
        clearScreen(); // Clear the screen before displaying the menu
        if (coffeeMenu.empty()) {
            cout << "The coffee menu is currently empty.\n"; // Check if menu is empty
        } else {
            cout << "Coffee Menu:\n";
            for (size_t i = 0; i < coffeeMenu.size(); ++i) {
                cout << i + 1 << ". " << coffeeMenu[i]->getName() << "\n"; // Use getName() method to display coffee names
            }
        }
        waitForEnter(); // Wait for user input before returning
    }

    // Allows the user to display details for a specific coffee
    void askCoffeeMenu() {
        clearScreen(); // Clear the screen before displaying the menu
        int choice;
        cout << "Enter the number of the coffee you want to display details for (0 to cancel): ";
        cin >> choice;

        if (choice > 0 && choice <= static_cast<int>(coffeeMenu.size())) {
            // Display details for the selected coffee
            cout << "Details for " << typeid(*coffeeMenu[choice - 1]).name() << ":\n";
            coffeeMenu[choice - 1]->printCoffeeDetails(); // Assuming each Coffee class has a printDetails() method
        } else if (choice != 0) {
            cout << "Invalid choice.\n"; // Handle invalid input
        }
        waitForEnter(); // Wait for user input before returning
    }

    // Allows the user to make a selected coffee
    void makeCoffee() {
        clearScreen(); // Clear the screen before displaying the menu
        if (coffeeMenu.empty()) {
            cout << "The coffee menu is currently empty.\n"; // Check if menu is empty
        } else {
            cout << "Select the coffee you want to make:\n";
            for (size_t i = 0; i < coffeeMenu.size(); ++i) {
                cout << i + 1 << ". " << coffeeMenu[i]->getName() << "\n"; // Display coffee names
            }

            int choice;
            cout << "Enter the number of the coffee you want to make (0 to cancel): ";
            cin >> choice;

            if (choice > 0 && choice <= static_cast<int>(coffeeMenu.size())) {
                // Get the selected coffee
                Coffee *selectedCoffee = coffeeMenu[choice - 1].get();

                // Use RTTI to determine the type of coffee and call the respective make method
                if (auto americano = dynamic_cast<Americano *>(selectedCoffee)) {
                    americano->makeAmericano();
                } else if (auto cappuccino = dynamic_cast<Cappuccino *>(selectedCoffee)) {
                    cappuccino->makeCappuccino();
                } else if (auto syrupCappuccino = dynamic_cast<SyrupCappuccino *>(selectedCoffee)) {
                    syrupCappuccino->makeSyrupCappuccino();
                } else if (auto pumpkinSpiceLatte = dynamic_cast<PumpkinSpiceLatte *>(selectedCoffee)) {
                    pumpkinSpiceLatte->makePumpkinSpiceLatte();
                } else {
                    cout << "Invalid coffee type.\n"; // Handle invalid coffee type
                }
            } else if (choice != 0) {
                cout << "Invalid choice.\n"; // Handle invalid input
            }
        }
        waitForEnter(); // Wait for user input before returning
    }

    // Main service menu for the Barista
    void service() {
        int choice;
        do {
            clearScreen(); // Clear the screen at the start of the menu
            cout << "--- Coffee Service Menu ---\n";
            cout << "1. Create Coffee Menu\n";
            cout << "2. Display Coffee Menu\n";
            cout << "3. Make Coffee\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createCoffeeMenu(); // Create the coffee menu
                    break;
                case 2:
                    displayCoffeeMenu(); // Display the coffee menu
                    break;
                case 3:
                    makeCoffee(); // Make the selected coffee
                    break;
                case 4:
                    cout << "Exiting the service menu.\n"; // Exit message
                    break;
                default:
                    cout << "Invalid choice, please try again.\n"; // Handle invalid input
            }
            waitForEnter(); // Wait for user input before returning to the menu
        } while (choice != 4);
    }
};

#endif // BARISTA_HPP
