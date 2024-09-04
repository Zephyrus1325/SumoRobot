#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H
#include "sensors.h"

class SensorHandler{
    private:
    // Esse é um quick-fix que eu espero que não seja fixo
    // Vai existir um limite de 10 sensores de cada tipo, que eu acho que é razoável, espero
    // TODO: usar alocação dinâmica para os sensores, a fim de otimizar um pouco o uso de memoria, e organizar tudo no geral
    #define maxSensors 10
    unsigned int totalUltrassound = 0;              // Total atual de sensores Ultrassonicos
    unsigned int totalInfrared = 0;                 // Total atual de sensores Infravermelho
    Ultrassound ultrassoundSensors[maxSensors];     // Array com todos os sensores Ultrassonicos Criados
    Infrared infraredSensors[maxSensors];           // Array com todos os sensores Infravermelhos Criados

    public:
    SensorHandler(){}

    // Função que atualiza todos os sensores
    // Eventualmente adicionar leitura generica
    // Adicionar leitura automatica com timer ou algo do tipo, sei la
    void update(){
        // Atualiza Ultrassons
        for(int i = 0; i < totalUltrassound; i++){
            Ultrassound &sensor = ultrassoundSensors[i];
            sensor.update();
        }
        // Atualiza Infravermelhos
        for(int i = 0; i < totalInfrared; i++){
            Infrared &sensor = infraredSensors[i];
            sensor.update();
        }
    }

    // Funções de adicionar Sensor Ultrassonico
    void addUltrassound(unsigned int triggerPin, unsigned int echoPin){
        if(totalUltrassound < maxSensors){ultrassoundSensors[totalUltrassound++] = Ultrassound(triggerPin, echoPin);}
    }

    void addUltrassound(unsigned int triggerPin, unsigned int echoPin, unsigned long maxTime){
        if(totalUltrassound < maxSensors){ultrassoundSensors[totalUltrassound++] = Ultrassound(triggerPin, echoPin, maxTime);}
    }

    //Funções de adicionar Sensor Infravermelho
    void addInfrared(unsigned int pin){
        if(totalInfrared < maxSensors){infraredSensors[totalInfrared++] = Infrared(pin);}
    }

    void addInfrared(unsigned int pin, bool mode){
        if(totalInfrared < maxSensors){infraredSensors[totalInfrared++] = Infrared(pin, mode);}
    }

};
#endif