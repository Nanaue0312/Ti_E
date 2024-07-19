//
// Created by nanaue on 2024/7/8.
//

#ifndef CAR_V2_SG90_H
#define CAR_V2_SG90_H

#define Servo_Init_PORT GPIOA
#define Servo_Init_PIN  GPIO_Pin_2

void Servo_Init();

void Servo_SetAngle(float Angle);

void Servo_Up();

void Servo_Down();

#endif //CAR_V2_SG90_H
