#pragma once
#include "Arduino.h"

class Receiver{
    private:
    uint8_t pin_channel[8];
    uint16_t reading[8];
    uint16_t lastTime[8] = {0,0,0,0,0,0,0,0};
    uint16_t activeTime[8] = {0,0,0,0,0,0,0,0};
    uint16_t calibration_min[8] = {990, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
    uint16_t calibration_mid[8] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
    uint16_t calibration_max[8] = {1800, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
    uint8_t calibrationMask = 0b00000000; // Mascara de calibração dos sensores

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

    void update(){
        for(int i = 0; i < 8; i++){
            if(read(i) > calibration_max[i] && read(i) < 2100){
                calibration_max[i] = read(i);
                calibration_mid[i] = (calibration_max[i] + calibration_min[i]) / 2;
            }
            if(read(i) < calibration_min[i] && read(i) > 900){
                calibration_min[i] = read(i);
                calibration_mid[i] = (calibration_max[i] + calibration_min[i]) / 2;
            }
        }
    }

    uint16_t read(uint8_t channel){
        return reading[channel];
    }

    uint8_t readButton(uint8_t channel){
        uint8_t state;
        state = read(channel) > 1500 ? 1 : 0;
        return state;
    }

    uint8_t readButton3(uint8_t channel){
        uint8_t state;
        uint16_t reading = read(channel);
        if(reading > 800 && reading < 1300){
            state = 0;
        } else if(reading > 1300 && reading <1600){
            state = 1;
        } else {
            state = 2;
        }

        return state;
    }

    void resetCalibration(uint8_t channel){
        // Reseta as calibrações de todo mundo
        calibration_max[channel] = 1000;
        calibration_min[channel] = 2000;
        calibration_mid[channel] = 1500;
    }

    uint16_t getMin(int channel){
        return calibration_min[channel];
    }

    
    uint16_t getMid(int channel){
        return calibration_mid[channel];
    }

    
    uint16_t getMax(int channel){
        return calibration_max[channel];
    }

};