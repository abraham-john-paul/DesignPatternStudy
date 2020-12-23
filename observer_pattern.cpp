#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class IObserver {
    public:
    virtual ~IObserver() = default;
    virtual void onTemperatureChanged(float newTemperature) = 0;
    virtual string getDeviceName() const = 0;
};

class IObservable {
    public:
    virtual ~IObservable() = default;
    virtual void add(IObserver*) = 0;
    virtual void remove(IObserver*) = 0;
    virtual void notifyTemperatureChanged(float newTemperature) = 0;
};

class WeatherStation : public IObservable {
    vector<unique_ptr<IObserver>> observers;
    float temperature;
    public:
    void add(IObserver* observer) override {
        observers.emplace_back(unique_ptr<IObserver>(observer));
    }
    void remove(IObserver* to_be_removed) override {
        observers.erase(find_if(observers.begin(), 
                                observers.end(), 
                                [to_be_removed](auto& observer) -> bool {
                                    return to_be_removed->getDeviceName() == observer->getDeviceName();
                                }));
    }
    void notifyTemperatureChanged(float newTemperature) override {
        for(const auto& observer : observers) {
            observer->onTemperatureChanged(newTemperature);
        }
    }
    float getTemperature() const {
        return temperature;
    }
    void setTemperature(const float newTemperature) {
        if(newTemperature != temperature) {
            temperature = newTemperature;
            notifyTemperatureChanged(temperature);
        }
    }
    void removeDeviceByIndex(int index) {
        if(index >= 0 && index < observers.size()) {
            remove(observers[index].get());
        }
    }
};

class PhoneDisplay : public IObserver {
    string phoneName;
    public:
    PhoneDisplay(string name) : phoneName {std::move(name)} {}
    ~PhoneDisplay() {
        cout << "\nDestroying Device : " << phoneName;
    }
    void onTemperatureChanged(float newTemperature) override {
        cout << "\nNew Temperature : " << newTemperature << " updated on " << phoneName;
    }
    string getDeviceName() const override{
        return phoneName;
    }
};

int main() {
    WeatherStation station;
    vector<string> phoneNames = {"phone1", "phone2", "phone3", "phone4", "phone5"};
    
    for(const auto& name : phoneNames) {
        station.add(new PhoneDisplay(name));
    }
    station.setTemperature(100);
    station.removeDeviceByIndex(2);
    station.setTemperature(100);
    station.setTemperature(150);
    return 0;
}