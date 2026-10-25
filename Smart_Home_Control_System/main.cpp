#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Device {
protected:
    string name;
    bool isOn;

public:
    Device(string n = "Unknown") : name(n), isOn(false) {}
    virtual ~Device() = default;

    virtual void turnOn() {
        isOn = true;
        cout << name << " turned ON.\n";
    }

    virtual void turnOff() {
        isOn = false;
        cout << name << " turned OFF.\n";
    }

    string getName() const {
        return name;
    }

    bool getStatus() const {
        return isOn;
    }

    virtual void display() const {
        cout << name << " is " << (isOn ? "ON" : "OFF") << '\n';
    }

    virtual void save(ofstream& out) const {
        out << "Device " << name << ' ' << isOn << '\n';
    }

    virtual void adjustSetting() {}
};

class SmartDevice : public Device {
private:
    bool wifiEnabled;

public:
    SmartDevice(string n = "Unknown Smart Device")
        : Device(n), wifiEnabled(false) {}

    void enableWiFi() {
        wifiEnabled = true;
        cout << name << " WiFi enabled.\n";
    }

    void disableWiFi() {
        wifiEnabled = false;
        cout << name << " WiFi disabled.\n";
    }

    void turnOn() override {
        Device::turnOn();
        enableWiFi();
    }

    void turnOff() override {
        disableWiFi();
        Device::turnOff();
    }

    void display() const override {
        cout << name << " is " << (isOn ? "ON" : "OFF")
             << " | WiFi: " << (wifiEnabled ? "Enabled" : "Disabled") << '\n';
    }

    void save(ofstream& out) const override {
        out << "SmartDevice " << name << ' ' << isOn << ' ' << wifiEnabled << '\n';
    }
};

class LightDevice : public Device {
private:
    int brightness;

public:
    LightDevice(string n = "Unknown Light")
        : Device(n), brightness(50) {}

    void adjustSetting() override {
        int value;
        cout << "Enter brightness (0-100) for " << name << ": ";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Brightness was not changed.\n";
            return;
        }
        if (value < 0) value = 0;
        if (value > 100) value = 100;
        brightness = value;
        cout << "Brightness set to " << brightness << "%\n";
    }

    void display() const override {
        cout << name << " is " << (isOn ? "ON" : "OFF")
             << " | Brightness: " << brightness << "%\n";
    }

    void save(ofstream& out) const override {
        out << "Light " << name << ' ' << isOn << ' ' << brightness << '\n';
    }
};

class AudioDevice : public Device {
private:
    int volume;

public:
    AudioDevice(string n = "Unknown Audio Device")
        : Device(n), volume(50) {}

    void adjustSetting() override {
        int value;
        cout << "Enter volume (0-100) for " << name << ": ";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Volume was not changed.\n";
            return;
        }
        if (value < 0) value = 0;
        if (value > 100) value = 100;
        volume = value;
        cout << "Volume set to " << volume << "%\n";
    }

    void display() const override {
        cout << name << " is " << (isOn ? "ON" : "OFF")
             << " | Volume: " << volume << "%\n";
    }

    void save(ofstream& out) const override {
        out << "Audio " << name << ' ' << isOn << ' ' << volume << '\n';
    }
};

class DeviceManager {
private:
    vector<Device*> devices;

public:
    DeviceManager() = default;
    DeviceManager(const DeviceManager&) = delete;
    DeviceManager& operator=(const DeviceManager&) = delete;

    void addDevice(Device* device) {
        if (device == nullptr) return;
        devices.push_back(device);
        cout << "Device added successfully!\n";
    }

    void removeDevice(int index) {
        if (index >= 0 && index < static_cast<int>(devices.size())) {
            delete devices[index];
            devices.erase(devices.begin() + index);
            cout << "Device removed successfully!\n";
        } else {
            cout << "Invalid index!\n";
        }
    }

    void listDevices() const {
        cout << "\n=== Devices List ===\n";
        if (devices.empty()) {
            cout << "No devices have been added yet.\n";
            return;
        }
        for (int i = 0; i < static_cast<int>(devices.size()); ++i) {
            cout << i + 1 << ". ";
            devices[i]->display();
        }
    }

    void controlDevice(int index, bool turnOnDevice) {
        if (index >= 0 && index < static_cast<int>(devices.size())) {
            if (turnOnDevice) devices[index]->turnOn();
            else devices[index]->turnOff();
        } else {
            cout << "Invalid index!\n";
        }
    }

    // Function overloading: turn on a device by index.
    void controlDevice(int index) {
        controlDevice(index, true);
    }

    // Function overloading: turn multiple devices on/off.
    void controlDevice(const vector<int>& indices, bool turnOnDevice) {
        for (int idx : indices) {
            controlDevice(idx, turnOnDevice);
        }
    }

    // Function overloading: find a device by name.
    void controlDevice(const string& deviceName, bool turnOnDevice) {
        for (int i = 0; i < static_cast<int>(devices.size()); ++i) {
            if (devices[i]->getName() == deviceName) {
                controlDevice(i, turnOnDevice);
                return;
            }
        }
        cout << "Device with name \"" << deviceName << "\" not found!\n";
    }

    void adjustDeviceSetting(int index) {
        if (index >= 0 && index < static_cast<int>(devices.size())) {
            devices[index]->adjustSetting();
        } else {
            cout << "Invalid index!\n";
        }
    }

    void saveDevices(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving devices!\n";
            return;
        }
        for (const auto* device : devices) {
            device->save(file);
        }
        if (!file) {
            cout << "An error occurred while writing the file.\n";
            return;
        }
        cout << "Devices saved successfully to " << filename << '\n';
    }

    ~DeviceManager() {
        for (auto* device : devices) delete device;
    }
};

int main() {
    DeviceManager manager;
    int choice = 0;

    do {
        cout << "\n=== Home Control System ===\n";
        cout << "1. List Devices\n";
        cout << "2. Add New Device\n";
        cout << "3. Remove Device\n";
        cout << "4. Turn ON Device\n";
        cout << "5. Turn OFF Device\n";
        cout << "6. Adjust Device Setting\n";
        cout << "7. Save Devices to File\n";
        cout << "8. Exit\n";
        cout << "9. Turn ON Device (by index - overload)\n";
        cout << "10. Turn ON Multiple Devices (vector)\n";
        cout << "11. Turn ON Device (by name)\n";
        cout << "Enter your choice (1-11): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                manager.listDevices();
                break;

            case 2: {
                int smartType, deviceType;
                string deviceName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter device name: ";
                getline(cin, deviceName);
                if (deviceName.empty()) {
                    cout << "Device name cannot be empty.\n";
                    break;
                }

                cout << "Type 1-Normal or 2-Smart Device: ";
                if (!(cin >> smartType)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input!\n";
                    break;
                }

                if (smartType == 1) {
                    cout << "Type 1-Light or 2-Audio Device: ";
                    if (!(cin >> deviceType)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input!\n";
                        break;
                    }
                    if (deviceType == 1)
                        manager.addDevice(new LightDevice(deviceName));
                    else if (deviceType == 2)
                        manager.addDevice(new AudioDevice(deviceName));
                    else
                        cout << "Invalid device type!\n";
                } else if (smartType == 2) {
                    manager.addDevice(new SmartDevice(deviceName));
                } else {
                    cout << "Invalid smart type!\n";
                }
                break;
            }

            case 3: {
                int index;
                manager.listDevices();
                cout << "Enter device number to remove: ";
                if (cin >> index) manager.removeDevice(index - 1);
                else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input!\n";
                }
                break;
            }

            case 4:
            case 5:
            case 6:
            case 9: {
                int index;
                manager.listDevices();
                if (choice == 4) cout << "Enter device number to turn ON: ";
                else if (choice == 5) cout << "Enter device number to turn OFF: ";
                else if (choice == 6) cout << "Enter device number to adjust setting: ";
                else cout << "Enter device number to turn ON (using overload): ";

                if (!(cin >> index)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input!\n";
                    break;
                }

                if (choice == 4) manager.controlDevice(index - 1, true);
                else if (choice == 5) manager.controlDevice(index - 1, false);
                else if (choice == 6) manager.adjustDeviceSetting(index - 1);
                else manager.controlDevice(index - 1);
                break;
            }

            case 7:
                manager.saveDevices("devices.txt");
                break;

            case 8:
                cout << "Exiting... Goodbye!\n";
                break;

            case 10: {
                int count, id;
                vector<int> ids;
                manager.listDevices();
                cout << "How many devices to turn ON? ";
                if (!(cin >> count) || count < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid count!\n";
                    break;
                }
                for (int i = 0; i < count; ++i) {
                    cout << "Enter device number " << (i + 1) << ": ";
                    if (!(cin >> id)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input; operation cancelled.\n";
                        ids.clear();
                        break;
                    }
                    ids.push_back(id - 1);
                }
                if (static_cast<int>(ids.size()) == count)
                    manager.controlDevice(ids, true);
                break;
            }

            case 11: {
                string deviceName;
                manager.listDevices();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter device name to turn ON: ";
                getline(cin, deviceName);
                manager.controlDevice(deviceName, true);
                break;
            }

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
