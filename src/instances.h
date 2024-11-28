#pragma once
#include <defines.h>
#include <pins.h>
#include "motor.h"
#include "receiverReader.h"
#include "ESP32Servo.h"

// instances.h
// Lugar onde salva todas as instancias de cada coisa

Motor leftMotor(PIN_MOTOR_LEFT_A, PIN_MOTOR_LEFT_B, PIN_MOTOR_LEFT_PWM);
Motor rightMotor(PIN_MOTOR_RIGHT_A, PIN_MOTOR_RIGHT_B, PIN_MOTOR_RIGHT_PWM);

Servo ramp;
Receiver receiver(PIN_RC_CHANNEL_1, PIN_RC_CHANNEL_2, PIN_RC_CHANNEL_3, PIN_RC_CHANNEL_4,
                  PIN_RC_CHANNEL_5, PIN_RC_CHANNEL_6, PIN_RC_CHANNEL_7, PIN_RC_CHANNEL_8);
int16_t throttle_left = 0;
int16_t throttle_right = 0;

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
    // Begin all Motors
    leftMotor.begin();
    rightMotor.begin();

    // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	ramp.setPeriodHertz(50);    // standard 50 hz servo
    ramp.attach(PIN_SERVO_RAMP);
    receiver.begin(); // Begin receiver

    // Set up interrupts for all the rc channels
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
    const int ramp_min = 75; // Angulo quando ativado
    const int ramp_max = 120; // Angulo de repouso

    // leitura de cada um dos canais
    int throttle_input = receiver.read(1);
    int throttle_min = receiver.getMin(1);
    int throttle_max = receiver.getMax(1);
    int steering_input = receiver.read(0);
    int steering_min = receiver.getMin(0);
    int steering_max = receiver.getMax(0);
    int reverse_input = receiver.readButton(2) ? -1 : 1;
    int ramp_input = !receiver.readButton(7);
    int ramp_angle = constrain(100 * ramp_input, ramp_min, ramp_max);

    // Mapeamento de cada 
    int forward = map(throttle_input, throttle_min, throttle_max, -255, 255);
    int turn = map(steering_input, steering_min, steering_max, -255, 255);

    throttle_left = constrain(forward + turn, -255, 255); 
    throttle_right = constrain(forward - turn, -255, 255);
    
    leftMotor.setThrottle(throttle_left);
    rightMotor.setThrottle(throttle_right);
    ramp.write(ramp_angle);
}

void updateInstances(){
    receiver.update();
    updateThrottles();
}
