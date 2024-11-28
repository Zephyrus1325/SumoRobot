#include <Arduino.h>

#include "instances.h"

void setup() {
    Serial.begin(115200);
    InitializeInstances();
}

void loop() {
    updateInstances();
}