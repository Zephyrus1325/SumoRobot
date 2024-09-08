#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

/*-------------------------------------------------------------------+
|    Classe de motor - Marco Aurélio (08/09/2024)                    |
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
    unsigned int encoderPin; // Pino do encoder rotativo

    // Parametros caso queira controlar o motor com PID (espero que meu sofrimento valha a pena)
    float actualSpeed; // Velocidade atual do motor
    float setpoint;    // Velocidade de objetivo do motor
    float PIDIntegral; // Integral usada no controlador PID
    float lastSpeed;   // Ultimo valor lido, usado no calculo da derivada no controlador PID
    float Kp, Ki, Kd;  // Parametros de calibração do controlador PID
    
    public:
    Motor(unsigned int dirA, unsigned int dirB, unsigned int pwm) : dirAPin(dirA), dirBPin(dirB), pwmPin(pwm){}

    // Inicializador do motor
    void begin(){
        pinMode(dirAPin, OUTPUT);
        pinMode(dirBPin, OUTPUT);
        pinMode(pwmPin, OUTPUT);
    }
    
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