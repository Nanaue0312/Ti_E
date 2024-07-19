//
// Created by nanaue on 2024/7/3.
//

#ifndef CAR_V2_ENCODER_H
#define CAR_V2_ENCODER_H

#define Left_EPort GPIOA
#define Left_E1A GPIO_Pin_6
#define Left_E1B GPIO_Pin_7

#define Right_EPort GPIOA
#define Right_E1A GPIO_Pin_0
#define Right_E1B GPIO_Pin_1

void Encoder_Init();

void Left_Encoder_Init();

void Right_Encoder_Init();

int16_t Encoder_Left_Get();

int16_t Encoder_Right_Get();

int16_t Velocity_FeedbackControl(int16_t targetVelocity, int16_t currentVelocity);

#endif //CAR_V2_ENCODER_H
