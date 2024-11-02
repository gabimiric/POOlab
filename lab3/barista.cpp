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
    const string name = "Coffee";

public:
    Coffee(Intensity intensity) : coffeeIntensity(intensity)
    {
    }

    virtual void display() const
    {
        cout << "Coffee Name: " << name << ", Intensity: " << coffeeIntensity << endl;
    }
};

class Americano : public Coffee {
    // Americano inherits from Coffee
protected:
    int mlOfWater;
    const string coffeeName = "Americano";

public:
    Americano(Intensity intensity, int water) : Coffee(intensity), mlOfWater(water)
    {
    }

    void display() const override
    {
        cout << "Coffee Name: " << coffeeName << ", Intensity: " << coffeeIntensity
                << ", Water: " << mlOfWater << " ml" << endl;
    }
};

class Cappuccino : public Coffee {
    // Cappuccino inherits from Americano
protected:
    int mlOfMilk;
    const string coffeeName = "Cappuccino";

public:
    Cappuccino(Intensity intensity, int milk)
        : Coffee(intensity), mlOfMilk(milk)
    {
    }

    void display() const override
    {
        cout << "Coffee Name: " << coffeeName << ", Intensity: " << coffeeIntensity
                << ", Milk: " << mlOfMilk << " ml" << endl;
    }
};

class SyrupCappuccino : public Cappuccino {
    // SyrupCappuccino inherits from Cappuccino
protected:
    SyrupType syrup;
    const string coffeeName = "SyrupCappuccino";

public:
    SyrupCappuccino(Intensity intensity, int milk, SyrupType syrupType)
        : Cappuccino(intensity, milk), syrup(syrupType)
    {
    }

    void display() const override
    {
        cout << "Coffee Name: " << coffeeName << ", Intensity: " << coffeeIntensity
                << ", Milk: " << mlOfMilk << " ml, Syrup Type: " << syrup << endl;
    }
};

class PumpkinSpiceLatte : public Cappuccino {
    // PumpkinSpiceLatte inherits from Cappuccino
protected:
    int mgOfPumpkinSpice;
    const string coffeeName = "PumpkinSpiceLatte";

public:
    PumpkinSpiceLatte(Intensity intensity, int milk, SyrupType syrupType, int spice)
        : Cappuccino(intensity, milk), mgOfPumpkinSpice(spice)
    {
    }

    void display() const override
    {
        cout << "Coffee Name: " << coffeeName << ", Intensity: " << coffeeIntensity
                << ", Water: " << " ml, Milk: " << mlOfMilk << " ml, Pumpkin Spice: "
                << mgOfPumpkinSpice << " mg" << endl;
    }
};

int main()
{
    Americano coffee1(NORMAL, 200);
    Cappuccino coffee2(NORMAL, 150);
    SyrupCappuccino coffee3(NORMAL, 200, VANILLA);
    PumpkinSpiceLatte coffee4(NORMAL, 200, CARAMEL, 20);

    coffee1.display();
    coffee2.display();
    coffee3.display();
    coffee4.display();

    return 0;
}
