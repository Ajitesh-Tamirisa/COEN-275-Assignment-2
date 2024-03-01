#include <iostream>
#include <string>
using namespace std;

class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
};

class DecafCoffee : public Coffee {
public:
    string getDescription() override {
        return "Decaf Coffee - $2.0";
    }

    double getCost() override {
        return 2.0; // This will return the cost of DecafCoffee without any extra condiments
    }
};

class EspressoCoffee : public Coffee {
public:
    string getDescription() override {
        return "Espresso Coffee - $2.5";
    }

    double getCost() override {
        return 2.5; // This will return the cost of EspressoCoffee without any extra condiments
    }
};

// This is the base class for the decorator
class CondimentDecorator : public Coffee {
protected:
    Coffee* coffee;
public:
    CondimentDecorator(Coffee* coffee) : coffee(coffee) {}
    string getDescription() override {
        return coffee->getDescription();
    }

    double getCost() override {
        return coffee->getCost();
    }
};

// Concrete decorator classes for Creamer, Sugar, OatMilk and Milk
class Creamer : public CondimentDecorator {
public:
    Creamer(Coffee* coffee) : CondimentDecorator(coffee) {}

    string getDescription() override {
        return coffee->getDescription() + ", Creamer - $0.5";
    }

    double getCost() override {
        return coffee->getCost() + 0.5; // Additional cost for Creamer
    }
};

class Sugar : public CondimentDecorator {
public:
    Sugar(Coffee* coffee) : CondimentDecorator(coffee) {}

    string getDescription() override {
        return coffee->getDescription() + ", Sugar - $0.3";
    }

    double getCost() override {
        return coffee->getCost() + 0.3; // Additional cost for Sugar
    }
};

class OatMilk : public CondimentDecorator {
public:
    OatMilk(Coffee* coffee) : CondimentDecorator(coffee) {}

    string getDescription() override {
        return coffee->getDescription() + ", Oat Milk - $0.7";
    }

    double getCost() override {
        return coffee->getCost() + 0.7; // Additional cost for Oat Milk
    }
};

class Milk : public CondimentDecorator {
public:
    Milk(Coffee* coffee) : CondimentDecorator(coffee) {}

    string getDescription() override {
        return coffee->getDescription() + ", Milk - $0.5";
    }

    double getCost() override {
        return coffee->getCost() + 0.5; // Additional cost for Milk
    }
};

int main() {
    Coffee* decaf = new DecafCoffee();

    Coffee* decafWithCreamer = new Creamer(decaf);
    Coffee* decafWithCreamerAndSugar = new Sugar(decafWithCreamer);

    cout <<"\n**********************Order No 101 **********************\n";
    cout << "Decaf with Creamer and Sugar" << endl;
    cout << "Description: " << decafWithCreamerAndSugar->getDescription() << endl;
    cout << "Cost: $" << decafWithCreamerAndSugar->getCost() << endl;

    Coffee* espresso = new EspressoCoffee();

    Coffee* espressoWithSugar = new Sugar(espresso);
    Coffee* espressoWithSugarAndOatMilk = new OatMilk(espressoWithSugar);

    cout <<"\n**********************Order No 102 **********************\n";
    cout << "Espresso With Sugar and Oat Milk" << endl;
    cout << "Description: " << espressoWithSugarAndOatMilk->getDescription() << endl;
    cout << "Total Cost: $" << espressoWithSugarAndOatMilk->getCost() << endl;

    return 0;
}
