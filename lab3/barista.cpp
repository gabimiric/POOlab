#include <iostream>
#include <string>

using namespace std;

enum Intensity {
    LIGHT,
    NORMAL,
    STRONG
};

enum SyrupType {
    MACADAMIA,
    VANILLA,
    COCONUT,
    CARAMEL,
    CHOCOLATE,
    POPCORN
};

class Coffee {
protected:
    Intensity coffeeIntensity;
    string coffeeName;

public:
    Coffee(Intensity intensity, const string &name) : coffeeIntensity(intensity), coffeeName(name) {}

    string intensityToString() const
    {
        switch (coffeeIntensity)
        {
            case LIGHT: return "Light";
            case NORMAL: return "Normal";
            case STRONG: return "Strong";
        }
        return "Unknown";
    }

    virtual Coffee *makeCoffee() const
    {
        cout << "\nMaking " << coffeeName
                << "\nIntensity set to " << intensityToString() << endl;
        return new Coffee(*this);
    }

    virtual void printCoffeeDetails() const
    {
        cout << "\nCoffee Name: " << coffeeName
                << "\nCoffee Intensity: " << intensityToString() << endl;
    }
};

class Americano : public Coffee {
protected:
    int mlOfWater;

public:
    Americano(Intensity intensity, int water)
        : Coffee(intensity, "Americano"), mlOfWater(water) {}

    Americano *makeAmericano() const
    {
        makeCoffee();
        cout << "Adding " << mlOfWater << " ml of Water" << endl;
        return new Americano(*this); // Return a new instance of Americano
    }

    void printCoffeeDetails() const override
    {
        Coffee::printCoffeeDetails();
        cout << "Water: " << mlOfWater << " ml" << endl;
    }
};

class Cappuccino : public Coffee {
protected:
    int mlOfMilk;

public:
    Cappuccino(Intensity intensity, int milk)
        : Coffee(intensity, "Cappuccino"), mlOfMilk(milk) {}

    Cappuccino *makeCappuccino() const
    {
        makeCoffee();
        cout << "Adding " << mlOfMilk << " ml of Milk" << endl;
        return new Cappuccino(*this);
    }

    void printCoffeeDetails() const override
    {
        Coffee::printCoffeeDetails();
        cout << "Milk: " << mlOfMilk << " ml" << endl;
    }
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;

public:
    SyrupCappuccino(Intensity intensity, int milk, SyrupType syrupType)
        : Cappuccino(intensity, milk), syrup(syrupType)
    {
        coffeeName = "Syrup Cappuccino";
    }

    SyrupCappuccino *makeSyrupCappuccino() const
    {
        makeCappuccino();
        cout << "Adding " << syrupTypeToString() << " syrup" << endl;
        return new SyrupCappuccino(*this);
    }

    void printCoffeeDetails() const override
    {
        Cappuccino::printCoffeeDetails();
        cout << "Syrup Type: " << syrupTypeToString() << endl;
    }

    string syrupTypeToString() const
    {
        switch (syrup)
        {
            case MACADAMIA: return "Macadamia";
            case VANILLA: return "Vanilla";
            case COCONUT: return "Coconut";
            case CARAMEL: return "Caramel";
            case CHOCOLATE: return "Chocolate";
            case POPCORN: return "Popcorn";
        }
        return "Unknown";
    }
};

class PumpkinSpiceLatte : public Cappuccino {
protected:
    int mgOfPumpkinSpice;

public:
    PumpkinSpiceLatte(Intensity intensity, int milk, int spice)
        : Cappuccino(intensity, milk), mgOfPumpkinSpice(spice)
    {
        coffeeName = "Pumpkin Spice Latte";
    }

    PumpkinSpiceLatte *makePumpkinSpiceLatte() const
    {
        makeCappuccino();
        cout << "Adding " << mgOfPumpkinSpice << " mg of Pumpkin Spice" << endl;
        return new PumpkinSpiceLatte(*this);
    }

    void printCoffeeDetails() const override
    {
        Cappuccino::printCoffeeDetails();
        cout << "Pumpkin Spice: " << mgOfPumpkinSpice << " mg" << endl;
    }
};

int main()
{
    // Create instances of different coffee types (Create Menu)
    Americano menuAmericano(NORMAL, 200);
    Cappuccino menuCappuccino(LIGHT, 150);
    SyrupCappuccino menuSyrupCappuccino(NORMAL, 200, MACADAMIA);
    PumpkinSpiceLatte menuPumpkinSpiceLatte(LIGHT, 200, 20);

    // Call make functions and print details
    Americano *madeAmericano = menuAmericano.makeAmericano();
    // madeAmericano->printCoffeeDetails();

    Cappuccino *madeCappuccino = menuCappuccino.makeCappuccino();
    // madeCappuccino->printCoffeeDetails();

    SyrupCappuccino *madeSyrupCappuccino = menuSyrupCappuccino.makeSyrupCappuccino();
    // madeSyrupCappuccino->printCoffeeDetails();

    PumpkinSpiceLatte *madePumpkinSpiceLatte = menuPumpkinSpiceLatte.makePumpkinSpiceLatte();
    // madePumpkinSpiceLatte->printCoffeeDetails();

    // Clean up dynamically allocated objects
    delete madeAmericano;
    delete madeCappuccino;
    delete madeSyrupCappuccino;
    delete madePumpkinSpiceLatte;

    return 0;
}
