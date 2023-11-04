#include "trigger.h"
#include "analog_io.h"
#include "servo/servo_system.hpp"

// pin 37 is dead 
#define TRIG_A0 39

static void trig_isr() {
    // set trigger flag for each channel 
    for (int i = 0; i < 4; ++i) 
        servoes[i]->reference->trigged = true;
}

static void trig_hsp_isr() {
    if (digitalReadFast(GLOBAL_ENABLE_PIN)) {
        // set trigger flag for each channel
        for (int i = 0; i < 4; ++i)
            servoes[i]->reference_hsp->trigged = true;
    } 
    else {
        // clear integrator if HSP is done 
        for (int i = 0; i < 4; ++i)
            servoes[i]->clear();
    }
}

void init_trigger() {
    pinMode(TRIG_A0, INPUT_PULLUP);
    pinMode(GLOBAL_ENABLE_PIN, INPUT_PULLDOWN);
    attachInterrupt(TRIG_A0, trig_isr, RISING);
    attachInterrupt(GLOBAL_ENABLE_PIN, trig_hsp_isr, CHANGE);
}

