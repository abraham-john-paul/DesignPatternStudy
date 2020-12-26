#include <iostream>
#include <memory>
using namespace std;

struct Adaptee {
    void specificRequest() {
        cout << "\nSome Specific Request\n";
    }
};

struct ITarget {
    virtual ~ITarget() {}
    virtual void request() = 0;
};

struct Adapter : ITarget {
    unique_ptr<Adaptee> p_Adaptee;
    Adapter(Adaptee* a) : p_Adaptee{unique_ptr<Adaptee>(a)} {}
    void request() override {
        p_Adaptee->specificRequest();
    }
};

int main() {
    auto target = unique_ptr<ITarget>(new Adapter(new Adaptee()));
    target->request();
    return 0;
}