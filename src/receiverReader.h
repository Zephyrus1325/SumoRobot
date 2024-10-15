#pragma once
#include "Arduino.h"

class Receiver{
    private:
    uint8_t pin_channel[8];
    uint16_t reading[8];
    uint16_t lastTime[8] = {0,0,0,0,0,0,0,0};
    uint16_t activeTime[8] = {0,0,0,0,0,0,0,0};
    
    
    public:
    Receiver(uint8_t pin_c1, uint8_t pin_c2, uint8_t pin_c3, uint8_t pin_c4, uint8_t pin_c5, uint8_t pin_c6, uint8_t pin_c7, uint8_t pin_c8){
        pin_channel[0] = pin_c1;
        pin_channel[1] = pin_c2;
        pin_channel[2] = pin_c3;
        pin_channel[3] = pin_c4;
        pin_channel[4] = pin_c5;
        pin_channel[5] = pin_c6;
        pin_channel[6] = pin_c7;
        pin_channel[7] = pin_c8;
        
    };

    void begin(){
        for(int i = 0; i < 8; i++){
            pinMode(pin_channel[i], INPUT);
        }
    }

    void checkPin(uint8_t channel){
        if(digitalRead(pin_channel[channel])){
            lastTime[channel] = micros();
        } else {
            reading[channel] = micros() - lastTime[channel];
        }
    }

    uint16_t read(uint8_t channel){
        return reading[channel];
    }
};