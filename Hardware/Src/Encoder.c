//
// Created by nanaue on 2024/7/3.
//
#include "stm32f10x.h"
#include "Encoder.h"

void Encoder_Init() {
    Left_Encoder_Init();
    Right_Encoder_Init();
}

/**
 * 使用TIM3_CH1和TIM3_CH2作为左轮编码器接口
 */
void Left_Encoder_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = Right_E1A | Right_E1B;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Right_EPort, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
    TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
    TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM2, &TimeBaseInitStructure);
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    // 初始化编码器接口模式
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
    TIM_Cmd(TIM2, ENABLE);
    TIM_SetCounter(TIM2, 0);
}

/**
 * 使用TIM4_CH1和TIM4_CH2作为左轮编码器接口
 */
void Right_Encoder_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = Left_E1A | Left_E1B;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Left_EPort, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
    TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
    TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM3, &TimeBaseInitStructure);
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    // 初始化编码器接口模式
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_Cmd(TIM3, ENABLE);
    TIM_SetCounter(TIM3, 0);
}

/**
 * 获取左电机转速
 * @return 电机转速(round/s)
 */
int16_t Encoder_Left_Get() {
    int16_t speed = (int16_t) TIM_GetCounter(TIM2);
    TIM_SetCounter(TIM2, 0);
    return speed;
}

/**
 * 获取右电机转速
 * @return 电机转速(round/s)
 */
// float Encoder_Right_Get() {
//     float speed = (int16_t) TIM_GetCounter(TIM3) / (0.01 * 1040);
//     TIM_SetCounter(TIM3, 0);
//     return speed;
// }

int16_t Encoder_Right_Get() {
    int16_t speed = (int16_t) TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0);
    return speed;
}
