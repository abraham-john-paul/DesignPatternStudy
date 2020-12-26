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
    SingletonClass(int t_value) : m_value{t_value} {}
    int m_value;
};

int main() {
    auto obj = SingletonClass::getInstance(20);
    cout << obj.getValue() << "\n";
    return 0;
}