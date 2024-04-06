#include "analog_io/analog_io.h"
void init_chips();
void setup() {
    init_chips();
    while (!Serial)
        ;
    Serial.begin(115200);
    delay(200);
    pinMode(40, OUTPUT);
}

void loop() {
}
