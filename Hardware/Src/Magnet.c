//
// Created by nanaue on 2024/7/31.
//
#include "stm32f10x.h"
#include "Magnet.h"

/**
 * 电磁铁初始化
 */
void Magnet_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = Magnet_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(Magnet_Port, &GPIO_InitStructure);
    GPIO_ResetBits(Magnet_Port, Magnet_Pin);
}

/**
 * 释放磁力
 */
void Magnet_SeizeChess() {
    GPIO_SetBits(Magnet_Port, Magnet_Pin);
}

/**
 * 解除磁力
 */
void Magnet_FreeChess() {
    GPIO_ResetBits(Magnet_Port, Magnet_Pin);
}