#include <Arduino.h>

#include "instances.h"
#include "webServer.h"


void setup() {
    Serial.begin(115200);
    InitializeInstances();
    //InitializeServer();
}

void loop() {
    updateInstances();
}