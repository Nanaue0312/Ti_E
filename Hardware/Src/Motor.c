//
// Created by nanaue on 2024/7/30.
//
#include "stm32f10x.h"
#include "stdio.h"
#include "Motor.h"
#include "Delay.h"
#include "Magnet.h"

/**
 * @brief 设置当前位置为原点
 */
void Motor_Init() {
    printf("G92 X0Y0Z0\n");
}

/**
 * 抓取棋子
 */
void SeizeChess() {
    printf(Z_Down);
    Delay_ms(500);
    Magnet_SeizeChess();
    printf(Z_Reset);
    Delay_ms(500);
}

/**
 * 释放棋子
 */
void FreeChess() {
    printf(Z_Down);
    Delay_ms(500);
    Magnet_FreeChess();
    printf(Z_Reset);
    Delay_ms(500);
}