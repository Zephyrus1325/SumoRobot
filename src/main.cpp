#include <Arduino.h>

#include "instances.h"
#include "webServer.h"


void setup() {
    Serial.begin(115200);
    InitializeInstances();
<<<<<<< HEAD
    InitializeServer();
=======
    //InitializeServer();
>>>>>>> ebcda89ba25bc649980483570155a5a3e9bcf982
}

void loop() {
    updateInstances();
}