//
// Created by nanaue on 2024/7/31.
//
#include "stm32f10x.h"
#include "MaxiCam.h"
#include "Board.h"
#include "Motor.h"
#include "stdio.h"
#include "Ti_USART.h"
#include "Delay.h"

int16_t max = INT16_MIN;
int16_t min = INT16_MAX;
uint8_t DataCount = 0;
uint8_t RectFound = 0;

int16_t BlackChess[5][2] = {
        {25,  -85},
        {48,  -85},
        {61,  -85},
        {84,  -85},
        {107, -85}};

int16_t WhiteChess[5][2] = {
        {25,  -245},
        {48,  -245},
        {61,  -245},
        {84,  -245},
        {107, -245}};

void Board_FindRect() {
    for (int i = 0; i < sizeof(Centers) / sizeof(Centers[0]); ++i) {
        if (Centers[i][0] > max) {
            max = Centers[i][0];
        }
        if (Centers[i][0] < min) {
            min = Centers[i][0];
        }
    }
}

/**
 * 寻找棋子
 * @param id 棋子id,0-5
 * @param type 棋子类型,1:白色,2:黑色
 */
void Board_GotoChess(uint8_t id, int8_t type) {
    // 寻找白棋
    if (type == 1) {
        Move(WhiteChess[id][0], WhiteChess[id][1], 1500);
        Serial1_SendString(cmd);
        Delay_ms(200);
        SeizeChess();
    } else if (type == -1) {
        Move(BlackChess[id][0], BlackChess[id][1], 1500);
        Serial1_SendString(cmd);
        Delay_ms(200);
        SeizeChess();
    }
}