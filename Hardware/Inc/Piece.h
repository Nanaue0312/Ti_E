//
// Created by nanaue on 2024/7/30.
//

#ifndef CAR_V2_PIECE_H
#define CAR_V2_PIECE_H


extern uint8_t WhiteGridId;
extern uint8_t BlackGridId;
extern char cmd[30];

void LED_Init();

void LED_Control();

void Move_Control(int16_t x, int16_t y, int16_t z, int16_t t);

#endif //CAR_V2_PIECE_H
