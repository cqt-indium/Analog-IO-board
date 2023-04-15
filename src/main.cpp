#include "analog_io.h"
#include "fsm.hpp"
#include "trigger.h"
#include "servo/servo_system.hpp"


void setup() {
    while (!Serial)
        ;
    Serial.begin(115200);
    init_trigger();
    init_chips();
    init_fsm();
}

void loop() {  
   state_machine_loop();
}
