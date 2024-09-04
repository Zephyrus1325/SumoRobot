#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

class Motor{
    private:
    unsigned int dirAPin; // Pino de direção A
    unsigned int dirBPin; // Pino de direção B
    unsigned int pwmPin;  // Pino de controle de potência
    
    public:
    Motor(unsigned int dirA, unsigned int dirB, unsigned int pwm) : dirAPin(dirA), dirBPin(dirB), pwmPin(pwm){}
    
    // Define direção e potência do motor
    // Recebe valor entre -255 e +255
    void setSpeed(int speed){
        if(speed < 0){
            digitalWrite(dirAPin, HIGH);
            digitalWrite(dirBPin, LOW);
        } else {
            digitalWrite(dirAPin, LOW);
            digitalWrite(dirBPin, HIGH);
        }
        analogWrite(pwmPin, constrain(abs(speed), 0, 255));
    }
};

#endif