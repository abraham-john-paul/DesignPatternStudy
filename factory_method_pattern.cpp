#include <iostream>
#include <memory>
using namespace std;

struct Product {
    virtual ~Product() {}
    virtual string operation() const = 0;
};

struct ProductA : Product {
    string operation() const {
        return "\nOperation on Product A";
    }
};

struct ProductB : Product {
    string operation() const {
        return "\nOperation on Product B";
    }
};

struct Factory {
    virtual ~Factory() {}
    virtual unique_ptr<Product> factoryMethod() const = 0;
    string someOperation() const {
        auto product = factoryMethod();
        return product->operation();
    }
};

template <typename T, typename U>
struct ProductFactory : Factory {
    unique_ptr<T> factoryMethod() const {
        return make_unique<U>();
    }
};

using FactoryProductA = ProductFactory<Product, ProductA>;
using FactoryProductB = ProductFactory<Product, ProductB>;

int main() {
    auto factoryA = make_unique<FactoryProductA>();
    cout << factoryA->someOperation();

    auto factoryB = make_unique<FactoryProductB>();
    cout << factoryB->someOperation();

    return 0;
}