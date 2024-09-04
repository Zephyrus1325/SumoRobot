#include <Arduino.h>

// Classe mãe de todos os sensores usados
class Sensor{
    virtual void update();  // Função de atualização do Sensor
};

//
class Ultrassound : public Sensor {
    private:
    float distance;                 // Distancia lida pelo Sensor Ultrassonico em cm
    const unsigned int triggerPin;        // Pino Trigger do Sensor
    const unsigned int echoPin;           // Pino Echo do Sensor
    unsigned long maxTime = 2000;   // Tempo máximo que vai se esperar pelo echo do sensor em microssegundos

    public:

    Ultrassound(const unsigned int trigger, const unsigned int echo) : triggerPin(trigger), echoPin(echoPin){}

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
    float distance;
    bool state;
    bool mode;
    unsigned int pin;

    public:
    #define ON_OFF 0
    #define ANALOG 1
    Infrared(unsigned int pin) : pin(pin){mode = ON_OFF;}
    Infrared(unsigned int pin, bool mode) : pin(pin), mode(mode){}

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