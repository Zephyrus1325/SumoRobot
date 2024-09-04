#include <Arduino.h>

class Motor{
    private:
    unsigned int dirAPin;
    unsigned int dirBPin;
    unsigned int pwmPin;
    
    public:
    Motor(unsigned int dirA, unsigned int dirB, unsigned int pwm) : dirAPin(dirA), dirBPin(dirB), pwmPin(pwm){}
    
    
    void setSpeed(int speed){
        if(speed < 0){
            digitalWrite(dirAPin, HIGH);
            digitalWrite(dirBPin, LOW);
        } else {
            digitalWrite(dirAPin, LOW);
            digitalWrite(dirBPin, HIGH);
        }
        analogWrite(pwmPin, abs(speed));
    }
};