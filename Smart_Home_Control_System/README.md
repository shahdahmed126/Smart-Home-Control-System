# Smart Home Control System (C++)

A console-based Smart Home Control System built with C++. It lets users add and manage devices, switch them on or off, adjust device settings, and save device information to a text file.

## Features

- Add smart devices, lights, and audio devices.
- List all registered devices and their current settings.
- Turn devices on or off.
- Adjust light brightness and audio volume (0–100).
- Turn on a device by its index or name.
- Turn on multiple devices using a `vector`.
- Save device information to `devices.txt`.
- Demonstrates core Object-Oriented Programming (OOP) concepts.

## OOP and C++ Concepts

- **Encapsulation:** device state and settings are stored in classes.
- **Inheritance:** `SmartDevice`, `LightDevice`, and `AudioDevice` inherit from `Device`.
- **Polymorphism:** virtual methods such as `turnOn()`, `display()`, and `save()` are overridden.
- **Function overloading:** `controlDevice()` supports different parameter lists.
- **STL:** `vector` stores and controls devices.
- **File handling:** `ofstream` saves device information.
- **Dynamic memory management:** `DeviceManager` owns and deletes the device objects.

## Device Types

1. **Smart Device** — can be switched on/off and enables/disables Wi-Fi along with its power state.
2. **Light Device** — supports brightness adjustment.
3. **Audio Device** — supports volume adjustment.

## Requirements

- A C++ compiler that supports **C++11 or later** (for example, g++, GCC, or MinGW).
- A terminal or C++ IDE such as Visual Studio or Code::Blocks.

## How to Compile and Run

### Windows (g++ / MinGW)

Open a terminal in the project folder and run:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o SmartHome
SmartHome.exe
```

### Linux / macOS

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o SmartHome
./SmartHome
```

## Menu

The program displays a menu with options to:

1. List devices
2. Add a new device
3. Remove a device
4. Turn a device on
5. Turn a device off
6. Adjust a device setting
7. Save devices to a file
8. Exit
9. Turn on a device using the overloaded function
10. Turn on multiple devices
11. Turn on a device by name

## Example Run

```text
=== Home Control System ===
1. List Devices
2. Add New Device
3. Remove Device
4. Turn ON Device
5. Turn OFF Device
6. Adjust Device Setting
7. Save Devices to File
8. Exit
9. Turn ON Device (by index - overload)
10. Turn ON Multiple Devices (vector)
11. Turn ON Device (by name)
Enter your choice (1-11): 2
Enter device name: Living Room Light
Type 1-Normal or 2-Smart Device: 1
Type 1-Light or 2-Audio Device: 1
Device added successfully!

=== Home Control System ===
Enter your choice (1-11): 1

=== Devices List ===
1. Living Room Light is OFF | Brightness: 50%
```

## Files

- `main.cpp` — complete C++ source code.
- `README.md` — project overview, features, compilation instructions, and example output.
- `devices.txt` — created automatically when you select **Save Devices to File**.

## Notes

- Device data is saved to `devices.txt` in the program's current working directory.
- This version saves device details to a file; it does not load previously saved devices when the program starts.
- The example run above is illustrative; actual console output depends on the choices you make.
