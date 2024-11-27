#ifndef COFFEE_HPP
#define COFFEE_HPP

#include <bits/stdc++.h>

using namespace std;

// Enum representing the intensity levels of coffee
enum Intensity {
    LIGHT,
    NORMAL,
    STRONG
};

// Enum representing different types of syrups
enum SyrupType {
    MACADAMIA,
    VANILLA,
    COCONUT,
    CARAMEL,
    CHOCOLATE,
    POPCORN
};

// Base class for Coffee
class Coffee {
    friend class Barista; // Allows Barista to access private/protected members
protected:
    Intensity coffeeIntensity; // Coffee intensity level
    string coffeeName; // Name of the coffee

    // Constructor to initialize coffee intensity and name
    Coffee(Intensity intensity, const string &name) : coffeeIntensity(intensity), coffeeName(name) {}

    // Convert intensity enum to string
    string intensityToString() const {
        switch (coffeeIntensity) {
            case LIGHT: return "Light";
            case NORMAL: return "Normal";
            case STRONG: return "Strong";
        }
        return "Unknown"; // Default case
    }

    // Method to make coffee (to be overridden)
    virtual Coffee *makeCoffee() const {
        cout << "\nMaking " << coffeeName
             << "\nIntensity set to " << intensityToString() << endl;
        return new Coffee(*this); // Create a new instance of Coffee
    }

    // Print coffee details (to be overridden)
    virtual void printCoffeeDetails() const {
        cout << "\nCoffee Name: " << coffeeName
             << "\nCoffee Intensity: " << intensityToString() << endl;
    }

    // Get the name of the coffee
    string getName() const { return coffeeName; }
};

// Class for Americano, derived from Coffee
class Americano : public Coffee {
    friend class Barista; // Allows Barista to access private/protected members
protected:
    int mlOfWater; // Amount of water in ml

    // Constructor for Americano
    Americano(Intensity intensity, int water)
        : Coffee(intensity, "Americano"), mlOfWater(water) {}

    // Method to make Americano
    Americano *makeAmericano() const {
        makeCoffee(); // Call base class method
        cout << "Adding " << mlOfWater << " ml of Water" << endl;
        return new Americano(*this); // Return a new instance of Americano
    }

    // Print Americano details
    void printCoffeeDetails() const override {
        Coffee::printCoffeeDetails(); // Call base class method
        cout << "Water: " << mlOfWater << " ml" << endl;
    }
};

// Class for Cappuccino, derived from Coffee
class Cappuccino : public Coffee {
    friend class Barista; // Allows Barista to access private/protected members
protected:
    int mlOfMilk; // Amount of milk in ml

    // Constructor for Cappuccino
    Cappuccino(Intensity intensity, int milk)
        : Coffee(intensity, "Cappuccino"), mlOfMilk(milk) {}

    // Method to make Cappuccino
    Cappuccino *makeCappuccino() const {
        makeCoffee(); // Call base class method
        cout << "Adding " << mlOfMilk << " ml of Milk" << endl;
        return new Cappuccino(*this); // Return a new instance of Cappuccino
    }

    // Print Cappuccino details
    void printCoffeeDetails() const override {
        Coffee::printCoffeeDetails(); // Call base class method
        cout << "Milk: " << mlOfMilk << " ml" << endl;
    }
};

// Class for Syrup Cappuccino, derived from Cappuccino
class SyrupCappuccino : public Cappuccino {
    friend class Barista; // Allows Barista to access private/protected members
protected:
    SyrupType syrup; // Type of syrup added

    // Constructor for Syrup Cappuccino
    SyrupCappuccino(Intensity intensity, int milk, SyrupType syrupType)
        : Cappuccino(intensity, milk), syrup(syrupType) {
        coffeeName = "Syrup Cappuccino"; // Set coffee name
    }

    // Method to make Syrup Cappuccino
    SyrupCappuccino *makeSyrupCappuccino() const {
        makeCappuccino(); // Call base class method
        cout << "Adding " << syrupTypeToString() << " syrup" << endl;
        return new SyrupCappuccino(*this); // Return a new instance of Syrup Cappuccino
    }

    // Print Syrup Cappuccino details
    void printCoffeeDetails() const override {
        Cappuccino::printCoffeeDetails(); // Call base class method
        cout << "Syrup Type: " << syrupTypeToString() << endl;
    }

    // Convert syrup type enum to string
    string syrupTypeToString() const {
        switch (syrup) {
            case MACADAMIA: return "Macadamia";
            case VANILLA: return "Vanilla";
            case COCONUT: return "Coconut";
            case CARAMEL: return "Caramel";
            case CHOCOLATE: return "Chocolate";
            case POPCORN: return "Popcorn";
        }
        return "Unknown"; // Default case
    }
};

// Class for Pumpkin Spice Latte, derived from Cappuccino
class PumpkinSpiceLatte : public Cappuccino {
    friend class Barista; // Allows Barista to access private/protected members
protected:
    int mgOfPumpkinSpice; // Amount of pumpkin spice in mg

    // Constructor for Pumpkin Spice Latte
    PumpkinSpiceLatte(Intensity intensity, int milk, int spice)
        : Cappuccino(intensity, milk), mgOfPumpkinSpice(spice) {
        coffeeName = "Pumpkin Spice Latte"; // Set coffee name
    }

    // Method to make Pumpkin Spice Latte
    PumpkinSpiceLatte *makePumpkinSpiceLatte() const {
        makeCappuccino(); // Call base class method
        cout << "Adding " << mgOfPumpkinSpice << " mg of Pumpkin Spice" << endl;
        return new PumpkinSpiceLatte(*this); // Return a new instance of Pumpkin Spice Latte
    }

    // Print Pumpkin Spice Latte details
    void printCoffeeDetails() const override {
        Cappuccino::printCoffeeDetails(); // Call base class method
        cout << "Pumpkin Spice: " << mgOfPumpkinSpice << " mg" << endl;
    }
};

#endif // COFFEE_HPP
