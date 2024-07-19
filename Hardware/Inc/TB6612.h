//
// Created by nanaue on 2024/7/2.
//

#ifndef CAR_V2_TB6612_H
#define CAR_V2_TB6612_H

#define Left_PWM_OP_Pin GPIO_Pin_8
#define Right_PWM_OP_Pin GPIO_Pin_9

void TB6612_Init();

void Left_SetPWM(uint16_t moto_l);

void Right_SetPWM(uint16_t moto_r);

#endif //CAR_V2_TB6612_H
