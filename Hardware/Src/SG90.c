//
// Created by nanaue on 2024/7/8.
//
#include "stm32f10x.h"
#include "SG90.h"

void Servo_Init() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 初始化输出引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = Servo_Init_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Servo_Init_PORT, &GPIO_InitStructure);
    // 初始化时基单元
    TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
    TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBaseInitStructure.TIM_Period = 20000 - 1;
    TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM5, &TimeBaseInitStructure);

    // 初始化左/右轮为PWM1
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0x00;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC3Init(TIM5, &TIM_OCInitStructure);

    TIM_Cmd(TIM5, ENABLE);
}

/**
 * 舵机角度控制
 * @param Angle 角度0-180
 */
void Servo_SetAngle(float Angle) {
    TIM_SetCompare3(TIM5, Angle / 180 * 2000 + 500);
}

/**
 * 抓取装置升起
 */
void Servo_Up() {
    Servo_SetAngle(50);
}

/**
 * 抓取装置下降
 */
void Servo_Down() {
    Servo_SetAngle(70);
}