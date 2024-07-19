//
// Created by nanaue on 2024/7/2.
//
#include "stm32f10x.h"
#include "TB6612.h"
#include "Motor.h"


/**
 * 初始化电机控制
 */
void Motor_Init() {
    TB6612_Init();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = Left_In1 | Left_In2 | Right_In1 | Right_In2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, Left_In1 | Left_In2 | Right_In1 | Right_In2);
}

/**
 * 左电机方向控制
 * @param motorDir 运动方向
 */
void Motor_Left_Dir_Control(Motor_Dir motorDir) {
    if (motorDir == GO) {
        GPIO_SetBits(GPIOB, Left_In1);
        GPIO_ResetBits(GPIOB, Left_In2);
    }
    if (motorDir == BACK) {
        GPIO_SetBits(GPIOB, Left_In2);
        GPIO_ResetBits(GPIOB, Left_In1);
    }
    if (motorDir == STOP) {
        GPIO_ResetBits(GPIOB, Left_In1);
        GPIO_ResetBits(GPIOB, Left_In2);
    }
}

/**
 * 右电机方向控制
 * @param motorDir 运动方向
 */
void Motor_Right_Dir_Control(Motor_Dir motorDir) {
    if (motorDir == GO) {
        GPIO_SetBits(GPIOB, Right_In2);
        GPIO_ResetBits(GPIOB, Right_In1);
    }
    if (motorDir == BACK) {
        GPIO_SetBits(GPIOB, Right_In1);
        GPIO_ResetBits(GPIOB, Right_In2);
    }
    if (motorDir == STOP) {
        GPIO_ResetBits(GPIOB, Right_In1);
        GPIO_ResetBits(GPIOB, Right_In2);
    }
}

/**
 * 电机速度控制
 * @param speed_l -7199-7199
 * @param speed_r -7199-7199
 */
void Motor_Control(int16_t leftCCR, int16_t rightCCR) {
    if (leftCCR >= 0) {
        Motor_Left_Dir_Control(GO);
        Left_SetPWM(leftCCR);
    }
    if (leftCCR < 0) {
        Motor_Left_Dir_Control(BACK);
        Left_SetPWM(-leftCCR);
    }
    if (rightCCR >= 0) {
        Motor_Right_Dir_Control(GO);
        Right_SetPWM(rightCCR);
    }
    if (rightCCR < 0) {
        Motor_Right_Dir_Control(BACK);
        Right_SetPWM(-rightCCR);
    }
}
