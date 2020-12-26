#include <iostream>
#include <memory>
#include <map>

using namespace std;

enum class LightCommandType {
    ON_LightCommand,
    OFF_LightCommand,
    Dim_LightCommand,
    Brighten_LightCommand
};

struct IReceiver {
    virtual ~IReceiver() {}
    virtual void action(LightCommandType) = 0;
};

struct LightReceiver: IReceiver {
    void action(LightCommandType commandType) override {
        cout << "\nThe Light is ";
        switch(commandType) {
            case LightCommandType::ON_LightCommand:
                cout << "ON\n";
                break;
            case LightCommandType::OFF_LightCommand:
                cout << "OFF\n";
                break;
            case LightCommandType::Dim_LightCommand:
                cout << "Dimmed\n";
                break;
            case LightCommandType::Brighten_LightCommand:
                cout << "Brightened\n";
                break;
        }
    }
};

struct ICommand {
    virtual ~ICommand() {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

struct LightONCommand : ICommand {
    unique_ptr<IReceiver> p_LightReceiver;
    LightONCommand(IReceiver* t_preceiver) : p_LightReceiver(unique_ptr<IReceiver>(t_preceiver)) {}
    void execute() override {
        p_LightReceiver->action(LightCommandType::ON_LightCommand);
    }
    void unexecute() override {
        p_LightReceiver->action(LightCommandType::OFF_LightCommand);
    }
};

struct LightOFFCommand : ICommand {
    unique_ptr<IReceiver> p_LightReceiver;
    LightOFFCommand(IReceiver* t_preceiver) : p_LightReceiver(unique_ptr<IReceiver>(t_preceiver)) {}
    void execute() override {
        p_LightReceiver->action(LightCommandType::OFF_LightCommand);
    }
    void unexecute() override {
        p_LightReceiver->action(LightCommandType::ON_LightCommand);
    }
};

struct LightDimCommand : ICommand {
    unique_ptr<IReceiver> p_LightReceiver;
    LightDimCommand(IReceiver* t_preceiver) : p_LightReceiver(unique_ptr<IReceiver>(t_preceiver)) {}
    void execute() override {
        p_LightReceiver->action(LightCommandType::Dim_LightCommand);
    }
    void unexecute() override {
        p_LightReceiver->action(LightCommandType::Brighten_LightCommand);
    }
};

struct LightBrightenCommand : ICommand {
    unique_ptr<IReceiver> p_LightReceiver;
    LightBrightenCommand(IReceiver* t_preceiver) : p_LightReceiver(unique_ptr<IReceiver>(t_preceiver)) {}
    void execute() override {
        p_LightReceiver->action(LightCommandType::Brighten_LightCommand);
    }
    void unexecute() override {
        p_LightReceiver->action(LightCommandType::Dim_LightCommand);
    }
};

struct Remote { // Invoker
    map<LightCommandType, unique_ptr<ICommand>> buttons;

    Remote(initializer_list<pair<LightCommandType, ICommand*>> buttonList) {
        for(const auto& button : buttonList) {
            buttons.insert({button.first, unique_ptr<ICommand>(button.second)});
        }
    }

    ICommand* getButton(LightCommandType commandType) {
        return buttons[commandType].get();
    }
};

int main() {
    Remote remote = {
        {LightCommandType::ON_LightCommand, new LightONCommand(new LightReceiver())},
        {LightCommandType::OFF_LightCommand, new LightOFFCommand(new LightReceiver())},
        {LightCommandType::Dim_LightCommand, new LightDimCommand(new LightReceiver())},
        {LightCommandType::Brighten_LightCommand, new LightBrightenCommand(new LightReceiver())}
    };
    remote.getButton(LightCommandType::ON_LightCommand)->execute();
    remote.getButton(LightCommandType::ON_LightCommand)->unexecute();
    return 0;
}