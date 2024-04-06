# Tutorial: upload sketch to Teensy

## Pre-requisite
The following software should be installed: 
1. VS Code;
2. Arduino IDE; 
3. Teensyduino

Moreover, the following extensions are recommended:

- C/C++; 
- Serial Monitor. 

## Goal

1. Exposure to the `analog_io` library API; 
2. Familiarize with VS Code;
3. Familiarize with makefile. 

## Steps:

1. Clone the repository from Github.  
```
git clone https://github.com/cqt-indium/Analog-IO-board.git
``` 

2. Open it with VS code. This is the root folder of this project, meaning every code change happens inside this folder. 
```
code Analog-IO-board 
```

3. Press `<ctrl>+<shift>+~` to toggle a new terminal and checkout the branch for this task. 
```
git checkout blank-io
```

4. Navigate to `src/main.cpp`. Confirm the file contents is as follows. If not, this means the original folder is corrupted and you should ask Travis for help.  
```
#include "analog_io/analog_io.h"

void setup() {
    init_chips();
    while (!Serial)
        ;
    Serial.begin(115200);
}

void loop() {
    analogio_write(0, 32768);
    analogio_read(AIN0);

    Serial.println("Hello world!");
    delay(1000);
}
```

5. Press `<ctrl>+<shift>+B`, and select `Build`. This should initiate compilation of the core library and the user library. A new panel should show up recording the compilation process and confirm it is ended with things as follow. If not, it means the build system is corrupted or the contents of the origin folder is corrupted and you should ask Travis for help.  
```
CORE [AR] .vsteensy/build/core.a 
Teensy core built successfully 

USER [CPP] SPI.cpp 

[LD]  .vsteensy/build/v1.0.elf
Memory region         Used Size  Region Size  %age Used
            ITCM:       15436 B       512 KB      2.94%
            DTCM:        6688 B       512 KB      1.28%
             RAM:       12384 B       512 KB      2.36%
           FLASH:         32 KB      7936 KB      0.40%
            ERAM:          0 GB        16 MB      0.00%
User code built and linked to libraries 

[SYM] .vsteensy/build/blank_io.sym
[HEX] .vsteensy/build/blank_io.hex
[LST] .vsteensy/build/blank_io.lst
Sucessfully built project 
```

6. Press `<ctrl>+<shift>+B`, and select `Upload`. This would upload the just-compiled sketch to the Teensy board. 

7. Press `<ctrl>+<shift>+P`, enter `serial`, and select `View: Toggle Serial Monitor`. This would turn on the serial monitor. Select the Teensy communication port from the `Port` menu and click `Start Monitoring`. Confirm that you can see `Hello world!` line by line. 

## Questions 

After you pass all the steps, submit your answer to the following questions to Travis. 

- Q0: What is this program, `main.cpp`, about? Can you explain what is going on in each line? 
- Q1: Where does the compiled files go? 
- Q2: After compilation, the target (executable like `.elf`) is named `v1.0` at the output. Can you change the name into `hello_world`? 
- Q3: What is the purpose of the `core` folder? What does it include? 
- Q4: How does the `makefile` find out the compiler? Can you write down the absolute path of the `gcc`-like compiler used? 
- Q5: Suppose this project needed to be uploaded from a different computer (indium desktop 3, for instance), which part of `makefile` needs to change? 
- Q6: What does the task `Clean` (yes, every entry from the `<ctrl>+<shift>+B` menu is a task) do? Can you think of when it becomes helpful? 
