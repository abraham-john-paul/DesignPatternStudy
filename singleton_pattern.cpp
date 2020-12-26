#include <iostream>
using namespace std;

struct SingletonClass {
    static SingletonClass& getInstance(int t_value) {
        static SingletonClass obj{t_value};
        return obj;
    }
    int getValue() const {
        return m_value;
    }

private:
    /* 
        Making Constructor, Copy constructor, Copy assignment operator
        so that only one object exists in the program at all times.
        Move Consrtuctor is not generated because of Rule of 5.
    */
    SingletonClass(int t_value) : m_value{t_value} {} // Parameterized CTOR
    SingletonClass(const SingletonClass&) = default; // Copy CTOR
    SingletonClass& operator =(const SingletonClass&) = default; // Copy Assignment
    int m_value;
};

int main() {
    auto& obj = SingletonClass::getInstance(20);
    cout << obj.getValue() << "\n";
    return 0;
}