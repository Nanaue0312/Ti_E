//
// Created by nanaue on 2024/7/2.
//

#ifndef CAR_V2_MOTOR_H
#define CAR_V2_MOTOR_H
typedef enum {
    GO,
    BACK,
    STOP
} Motor_Dir;


#define Motor_Left 0
#define Motor_Right 1

// 左轮电机控制引脚
#define Left_In1 GPIO_Pin_12
#define Left_In2 GPIO_Pin_13
// 右轮电机控制引脚
#define Right_In1 GPIO_Pin_14
#define Right_In2 GPIO_Pin_15

void Motor_Left_Dir_Control(Motor_Dir motorDir);

void Motor_Right_Dir_Control(Motor_Dir motorDir);

void Motor_Init();

void Motor_Control(int16_t leftCCR, int16_t rightCCR);

#endif //CAR_V2_MOTOR_H
