#pragma once
#include <defines.h>
#include <pins.h>
<<<<<<< HEAD
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
=======
#include "motor.h"
#include "receiverReader.h"
#include "ESP32Servo.h"
// Lugar onde salva todas as instancias de cada coisa

Servo ramp;
//Motor leftMotor(PIN_MOTOR_LEFT_A, PIN_MOTOR_LEFT_B, PIN_MOTOR_LEFT_PWM);
//Motor rightMotor(PIN_MOTOR_RIGHT_A, PIN_MOTOR_RIGHT_B, PIN_MOTOR_RIGHT_PWM);
Receiver receiver(PIN_RC_CHANNEL_1, PIN_RC_CHANNEL_2, PIN_RC_CHANNEL_3, PIN_RC_CHANNEL_4,
                  PIN_RC_CHANNEL_5, PIN_RC_CHANNEL_6, PIN_RC_CHANNEL_7, PIN_RC_CHANNEL_8);
int16_t throttle_left = 0;
int16_t throttle_right = 0;
>>>>>>> ebcda89ba25bc649980483570155a5a3e9bcf982

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
<<<<<<< HEAD
    sensors.addInfrared(PIN_IR_LEFT, MODE_DIGITAL, 100);
    sensors.addInfrared(PIN_IR_FRONT_LEFT, MODE_DIGITAL, 100);
    sensors.addInfrared(PIN_IR_RIGHT, MODE_DIGITAL, 100);
    sensors.addInfrared(PIN_IR_FRONT_RIGHT, MODE_DIGITAL, 100);
    leftMotor.begin();
    leftMotor.setMode(1);
    rightMotor.begin();
    rightMotor.setMode(1);
    receiver.begin();
=======
    //leftMotor.begin();
    //leftMotor.setMode(1); // Ativa modo Manual
    //rightMotor.begin();
    //rightMotor.setMode(1); // Ativa modo Manual
    // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	ramp.setPeriodHertz(50);    // standard 50 hz servo
    ramp.attach(PIN_SERVO_RAMP);
    receiver.begin();
    receiver.resetCalibration(0);
    receiver.resetCalibration(1);
    receiver.resetCalibration(2);
    pinMode(PIN_MOTOR_LEFT_A, OUTPUT);
    pinMode(PIN_MOTOR_LEFT_B, OUTPUT);
    pinMode(PIN_MOTOR_LEFT_PWM, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT_A, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT_B, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT_PWM, OUTPUT);

>>>>>>> ebcda89ba25bc649980483570155a5a3e9bcf982
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
<<<<<<< HEAD
    if(manual){
        int forward = map(receiver.read(1), 1000, 2000, -255, 255);
        int turn = map(receiver.read(2), 1000, 2000, -255, 255);
        throttle_left = constrain(forward + turn, -255, 255); 
        throttle_right = constrain(forward - turn, -255, 255); 
    } else {
        // Inserir codigo do Fight by Wire aqui
    }
=======
    int forward = map(receiver.read(0), receiver.getMin(0), receiver.getMax(0), -255, 255);
    int turn = map(receiver.read(1), receiver.getMin(1), receiver.getMax(1), -255, 255);
    throttle_left = constrain(forward + turn, -255, 255); 
    throttle_right = constrain(forward - turn, -255, 255);
    if(throttle_left < 0){
            digitalWrite(PIN_MOTOR_LEFT_A, HIGH);
            digitalWrite(PIN_MOTOR_LEFT_B, LOW);
        } else {
            digitalWrite(PIN_MOTOR_LEFT_A, LOW);
            digitalWrite(PIN_MOTOR_LEFT_B, HIGH);
        }
    if(throttle_right < 0){
            digitalWrite(PIN_MOTOR_RIGHT_A, HIGH);
            digitalWrite(PIN_MOTOR_RIGHT_B, LOW);
        } else {
            digitalWrite(PIN_MOTOR_RIGHT_A, LOW);
            digitalWrite(PIN_MOTOR_RIGHT_B, HIGH);
        }
    analogWrite(PIN_MOTOR_LEFT_PWM, constrain(abs(throttle_left), 0, 255));
    analogWrite(PIN_MOTOR_RIGHT_PWM, constrain(abs(throttle_right), 0, 255));
    ramp.write(0);
    Serial.print(receiver.getMin(2));
    Serial.print(" | ");
    Serial.print(receiver.getMax(2));
    Serial.print(" | ");
    Serial.print(receiver.read(2));
    Serial.print(" | ");
    Serial.println(receiver.readButton3(2));
>>>>>>> ebcda89ba25bc649980483570155a5a3e9bcf982

}

void updateInstances(){
<<<<<<< HEAD
    sensors.update();
    updateThrottles();
    leftMotor.update();
    rightMotor.update();
=======
    updateThrottles();
    receiver.update();
>>>>>>> ebcda89ba25bc649980483570155a5a3e9bcf982
}
