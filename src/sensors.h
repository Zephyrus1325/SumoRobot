#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>


// Classe mãe de todos os sensores usados
class Sensor{
    virtual void update();  // Função de atualização do Sensor
};

//
class Ultrassound : public Sensor {
    private:
    float distance;                     // Distancia lida pelo Sensor Ultrassonico em cm
    const unsigned int triggerPin;      // Pino Trigger do Sensor
    const unsigned int echoPin;         // Pino Echo do Sensor
    unsigned long maxTime = 2000;       // Tempo máximo que vai se esperar pelo echo do sensor em microssegundos

    public:

    Ultrassound(const unsigned int trigger, const unsigned int echo) : triggerPin(trigger), echoPin(echoPin){}
    Ultrassound(const unsigned int trigger, const unsigned int echo, const unsigned long maxTime) 
    : triggerPin(trigger), echoPin(echoPin), maxTime(maxTime){}

    Ultrassound& operator=(const Ultrassound&);

    // Faz uma leitura do sensor
    void update(){
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        // Ativa o trigger por 10 microssegundos
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        // A aguarda pelo pino de echo e retorna o tempo até o pulso chegar
        unsigned long duration = pulseIn(echoPin, HIGH, maxTime);
        // retorna a distancia
        distance = duration * 0.034f / 2.0f;
    }

    float getDistance(){return distance;}
    void setMaxTime(unsigned long time){maxTime = time;}
};



class Infrared : public Sensor{
    private:
    float distance;         // Distancia detectada pelo sensor
    bool state;             // Estado do sensor, se está detectando ou não
    bool mode;              // Modo do sensor, pode ser ON_OFF ou ANALOG
    unsigned int pin;       // Pino usado pelo sensor
    // TODO: Adicionar mais um pino e o suporte para, caso o mongol do usuario queira
    // usar o sensor Infravermelho nos dois modos ao mesmo tempo, por algum motivo

    public:
    #define DIGITAL 0    // Sensor no modo Digital
    #define ANALOG 1     // Sensor no modo Analogico

    Infrared(unsigned int pin) : pin(pin){mode = DIGITAL;}
    Infrared(unsigned int pin, bool mode) : pin(pin), mode(mode){}

    Infrared& operator=(const Infrared&);

    // Faz uma leitura do sensor
    void update(){
        if(ANALOG){
            distance = analogRead(pin);
            state = false;
        } else {
            distance = 0;
            state = digitalRead(pin);
        }
    }

    bool getState(){return state;}
    float getDistance(){return distance;}
};

#endif