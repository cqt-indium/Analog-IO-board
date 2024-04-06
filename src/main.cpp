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