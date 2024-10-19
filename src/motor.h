 #pragma once
#include <Arduino.h>

/*-------------------------------------------------------------------+
|    Classe de motor - Marco Aurélio (16/10/2024)                    |
|                                                                    |
|   Arquivo com a classe de motor                                    |
|   Possui todos os parametros para controlar um motor adequadamente |
+--------------------------------------------------------------------*/


class Motor{
    private:
    // Pinagem do motor
    unsigned int dirAPin; // Pino de direção A
    unsigned int dirBPin; // Pino de direção B
    unsigned int pwmPin;  // Pino de controle de potência

    public:
    Motor(unsigned int dirA, unsigned int dirB, unsigned int pwm) : dirAPin(dirA), dirBPin(dirB), pwmPin(pwm){}
 
    // Inicializador do motor
    void begin(){
        pinMode(dirAPin, OUTPUT);
        pinMode(dirBPin, OUTPUT);
        pinMode(pwmPin, OUTPUT);
    }

    void setThrottle(int16_t speed){
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
