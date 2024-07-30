//
// Created by nanaue on 2024/7/30.
//
#include "stm32f10x.h"
#include "Piece.h"
#include "stdio.h"
#include "string.h"
#include "Delay.h"

uint8_t board[9];

uint8_t WhiteGridId;
uint8_t BlackGridId;

char cmd[30];

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

void Move_Control(int16_t x, int16_t y, int16_t z, int16_t t) {
    Move(x, y, z, t);
    printf("%s", cmd);
    memset(cmd, 0, strlen(cmd));
}