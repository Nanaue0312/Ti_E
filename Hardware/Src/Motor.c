//
// Created by nanaue on 2024/7/30.
//
#include <string.h>
#include "stm32f10x.h"
#include "stdio.h"
#include "Motor.h"
#include "Delay.h"
#include "Magnet.h"
#include "Board.h"
#include "Ti_USART.h"

char cmd[30];

/**
 * @brief 设置当前位置为原点
 */
void Motor_Init() {
    Serial1_SendString("G92 X0Y0Z0\n");
}

/**
 * 抓取棋子
 */
void SeizeChess() {
    Magnet_SeizeChess();
    Serial1_SendString(Z_Down);
    Delay_ms(50);
    Serial1_SendString(Z_Reset);
    Delay_ms(50);
}

/**
 * 释放棋子
 */
void FreeChess() {
    Serial1_SendString(Z_Down);
    Delay_ms(50);
    Magnet_FreeChess();
    Serial1_SendString(Z_Reset);
    Delay_ms(50);
}

void Motor_Move(int16_t x, int16_t y, int16_t z, int16_t t) {
    Move(x, y, z);
    Serial1_SendString(cmd);
    memset(cmd, 0, strlen(cmd));
}