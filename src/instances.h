#pragma once
#include <defines.h>
#include <pins.h>
#include <sensorHandler.h>
#include "sensorHandler.h"
#include "motor.h"
#include "receiverReader.h"
// Lugar onde salva todas as instancias de cada coisa

SensorHandler sensors;
Motor leftMotor(PIN_MOTOR_LEFT_A, PIN_MOTOR_LEFT_B, 0);
Motor rightMotor(PIN_MOTOR_RIGHT_A, PIN_MOTOR_RIGHT_B, 1);
Receiver receiver(PIN_RC_CHANNEL_1, PIN_RC_CHANNEL_2, PIN_RC_CHANNEL_3, PIN_RC_CHANNEL_4,
                  PIN_RC_CHANNEL_5, PIN_RC_CHANNEL_6, PIN_RC_CHANNEL_7, PIN_RC_CHANNEL_8);

int8_t throttle_left = 0;
int8_t throttle_right = 0;
bool manual = true;     // Desativa o Fight By Wire completamente

void receiver_channel1(){
    receiver.checkPin(0);
}

void receiver_channel2(){
    receiver.checkPin(1);
}

void receiver_channel3(){
    receiver.checkPin(2);
}

void receiver_channel4(){
    receiver.checkPin(3);
}

void receiver_channel5(){
    receiver.checkPin(4);
}

void receiver_channel6(){
    receiver.checkPin(5);
}

void receiver_channel7(){
    receiver.checkPin(6);
}
void receiver_channel8(){
    receiver.checkPin(7);
}

void InitializeInstances(){
    sensors.addInfrared(PIN_IR_LEFT, MODE_DIGITAL, 100);
    sensors.addInfrared(PIN_IR_FRONT_LEFT, MODE_DIGITAL, 100);
    sensors.addInfrared(PIN_IR_RIGHT, MODE_DIGITAL, 100);
    sensors.addInfrared(PIN_IR_FRONT_RIGHT, MODE_DIGITAL, 100);
    leftMotor.begin();
    leftMotor.setMode(1);
    rightMotor.begin();
    rightMotor.setMode(1);
    receiver.begin();
    attachInterrupt(PIN_RC_CHANNEL_1, receiver_channel1, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_2, receiver_channel2, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_3, receiver_channel3, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_4, receiver_channel4, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_5, receiver_channel5, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_6, receiver_channel6, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_7, receiver_channel7, CHANGE);
    attachInterrupt(PIN_RC_CHANNEL_8, receiver_channel8, CHANGE);
}

void updateThrottles(){
    if(manual){
        int forward = map(receiver.read(1), 1000, 2000, -255, 255);
        int turn = map(receiver.read(2), 1000, 2000, -255, 255);
        throttle_left = constrain(forward + turn, -255, 255); 
        throttle_right = constrain(forward - turn, -255, 255); 
    } else {
        // Inserir codigo do Fight by Wire aqui
    }

}

void updateInstances(){
    sensors.update();
    updateThrottles();
    leftMotor.update();
    rightMotor.update();
}
