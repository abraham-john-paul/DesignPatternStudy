#include <iostream>
#include <functional>
#include <memory>
using namespace std;

struct Beverage {
    virtual ~Beverage() = default;
    virtual double cost() = 0;
};

struct AddonDecorator : public Beverage {
    unique_ptr<Beverage> m_beverage;
    virtual ~AddonDecorator() = default;
    AddonDecorator(Beverage* beverage) : m_beverage{unique_ptr<Beverage>(beverage)} {}
    double cost() override {
        return m_beverage->cost();
    }
};

struct Espresso : public Beverage {
    ~Espresso() {
        cout << "\nEspresso DTOR";
    }
    double cost() override {
        return 10;
    }
};

struct CaramelDecorator : public AddonDecorator {
    double m_cost = 2;
    CaramelDecorator(Beverage* berverage) : AddonDecorator{berverage} {}
    ~CaramelDecorator() {
        cout << "\nCaramel DTOR";
    }
    double cost() override {
        return m_cost + AddonDecorator::cost();
    }
};

int main() {
    unique_ptr<Beverage> b = unique_ptr<Beverage>(new CaramelDecorator(new CaramelDecorator(new Espresso())));
    cout << b->cost();
    return 0;
}