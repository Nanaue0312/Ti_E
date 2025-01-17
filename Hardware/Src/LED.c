//
// Created by nanaue on 2024/7/31.
//
#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"

void LED_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void LED_Control() {
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
    Delay_ms(3000);
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

