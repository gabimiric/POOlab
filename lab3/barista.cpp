#include <bits/stdc++.h>
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
    Coffee(Intensity intensity, const string &name) : coffeeIntensity(intensity), coffeeName(name)
    {}

    virtual void printCoffeeDetails() const
    {
        cout << "\nCoffee Name: " << coffeeName
                << "\nIntensity: " << coffeeIntensity << endl;
    }
};

class Americano : public Coffee {
protected:
    int mlOfWater;

public:
    Americano(Intensity intensity, int water) : Coffee(intensity, "Americano"), mlOfWater(water)
    {}

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
    Cappuccino(Intensity intensity, int milk) : Coffee(intensity, "Cappuccino"), mlOfMilk(milk)
    {}

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

    void printCoffeeDetails() const override
    {
        Cappuccino::printCoffeeDetails();
        cout << "Syrup Type: " << syrup << endl;
    }
};

class PumpkinSpiceLatte : public Cappuccino {
protected:
    int mgOfPumpkinSpice;

public:
    PumpkinSpiceLatte(Intensity intensity, int milk, SyrupType syrupType, int spice)
        : Cappuccino(intensity, milk), mgOfPumpkinSpice(spice)
    {
        coffeeName = "Pumpkin Spice Latte";
    }

    void printCoffeeDetails() const override
    {
        Cappuccino::printCoffeeDetails();
        cout << "Pumpkin Spice: " << mgOfPumpkinSpice << " mg" << endl;
    }
};

int main()
{
    Americano coffee1(NORMAL, 200);
    Cappuccino coffee2(LIGHT, 150);
    SyrupCappuccino coffee3(STRONG, 200, VANILLA);
    PumpkinSpiceLatte coffee4(LIGHT, 200, CARAMEL, 20);

    coffee1.printCoffeeDetails();
    coffee2.printCoffeeDetails();
    coffee3.printCoffeeDetails();
    coffee4.printCoffeeDetails();

    return 0;
}
