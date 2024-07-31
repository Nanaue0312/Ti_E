//
// Created by nanaue on 2024/7/31.
//
#include "stm32f10x.h"
#include "MaxiCam.h"

int8_t DataType = 0;

int16_t WhiteChess[5][2] = {{0, 0}};
int16_t BlackChess[5][2] = {{0, 0}};
int16_t Centers[9][2] = {{0, 0}};
