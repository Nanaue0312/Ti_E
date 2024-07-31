//
// Created by nanaue on 2024/7/31.
//

#ifndef CAR_V2_BOARD_H
#define CAR_V2_BOARD_H

extern int16_t max;
extern int16_t min;
extern uint8_t DataCount;
extern int16_t WhiteChess[5][2];
extern int16_t BlackChess[5][2];
extern uint8_t RectFound;

void Board_FindRect();

void Board_GotoChess(uint8_t id, int8_t type);

#endif //CAR_V2_BOARD_H
