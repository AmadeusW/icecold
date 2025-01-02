# Development Log

## 2025 January 1
Got the code to compile, I'm able to run the icecold-simulator and connect the python dashboard to it over the serial port.
i'm having trouble getting arduino-cli to compile multiple files. Some research showed I should check out https://platformio.org/
This should not only allow me to build a complex project for arduino, but it also has capability for testing that I should leverage


## 2024 December 30
I rewrote the basic infrastructure. There are two entry points:
1. icecold-arcade.ino, which composes modules that intract with arduino
2. icecold-simulator.cpp, which composes the module that transmits the state over the serial port

TODO:
- Implement the module that transmits the state over the serial port
- Write tests that exercise the controller through simulator
- Implement the GameController
- Port arduino modules

## 2024 December - Resuming work
I'm reading the existing source code and I'm not convinced that current approach is correct. For example, we have "digits" module whose role is to output score to the 7-segment display. However, it also has role of keeping track of score. As each module has two responsibilities (keeping track of state and interfacing with microcontroller) it's impossible to take them out and replace with simulated module. I propose that the refactored code will have just a few larger classes:
1. State class that keeps track of the game state, score, etc.
1. Behavior class that mutates the state and outputs based on inputs
1. Class(es) that interacts with Arduino and other peripherals. They will not be compiled for simulation.


I'm not going to use Teensy on the microcontroller side, it will now be Arudino Mega. This means that I can drop Teensy-specific build code and use standard way of compiling C++ into Arduino. This will also allow me to integrate with the instrumentation/testing infrastructure. Here's Claude on how to accomplish this:

Yes, arduino-cli can handle multiple .cpp and .h files across directories. However, you'll need to create a main .ino file to serve as the entry point since the Arduino build system expects one. Here's how to handle this:

```bash
# Initialize config
arduino-cli config init

# Install Arduino AVR core (needed for Mega)
arduino-cli core install arduino:avr

# Compile
arduino-cli compile --fqbn arduino:avr:mega2560 your_sketch_directory

# Upload (replace /dev/ttyACM0 with your port)
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega2560 your_sketch_directory
```

1. Create a main .ino file in your root project directory (it must have the same name as the directory). For example, if your project is called "MyProject":

```bash
MyProject/
  └── MyProject.ino   # New entry point file
  └── src/
      └── main.cpp
      └── other.cpp
      └── include/
          └── header.h
```

2. In MyProject.ino, you just need to include your actual entry point and potentially any Arduino-specific headers:
```cpp
#include "src/include/header.h"

// If you have setup() and loop() in main.cpp, you can just declare them here:
void setup();
void loop();

// Or if you need to define them here, you can call into your existing code:
/*
void setup() {
    yourExistingSetupFunction();
}

void loop() {
    yourExistingLoopFunction();
}
*/
```

3. Then compile as before:
```bash
arduino-cli compile --fqbn arduino:avr:mega2560 MyProject
```

The Arduino build system will automatically include all .cpp files it finds in your project directory and subdirectories. If you need to specify additional include paths or compiler flags, you can create a `compile_flags.txt` file:

```bash
# in compile_flags.txt
-I./src/include
-I./other/include
```

Would you like me to explain more about the build process or help with structuring the entry point file based on your specific codebase?

## 2020 April - Forward declarations
If I need to declare a pointer to an object, I don't need to include its header into my header.
I can just declare `class ClassName;` and compiler will know which size to allocate for pointers to `ClassName`
Specifically, the compiler needs to know that `ClassName` is a class and not a struct.

I need to include object's header only when I actually need to know the implementation,
e.g. in the implementation file or when declaring a descendant class.