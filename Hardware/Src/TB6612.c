//
// Created by nanaue on 2024/7/2.
//
#include "stm32f10x.h"
#include "TB6612.h"

/**
 * 初始化TB6612的PWM输出,10khz
 */
void TB6612_Init() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // 初始化输出引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = Left_PWM_OP_Pin | Right_PWM_OP_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // 初始化时基单元
    TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
    TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBaseInitStructure.TIM_Period = 7200 - 1;
    TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
    TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM4, &TimeBaseInitStructure);

    // 初始化左/右轮为PWM1
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0x00;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);

    TIM_Cmd(TIM4, ENABLE);
}

/**
 * 设置左轮转速
 * @param moto_l 0-100
 */
void Left_SetPWM(uint16_t moto_l) {
    TIM_SetCompare3(TIM4, moto_l);
}

/**
 * 设置右轮转速
 * @param moto_r 0-100
 */
void Right_SetPWM(uint16_t moto_r) {
    TIM_SetCompare4(TIM4, moto_r);
}