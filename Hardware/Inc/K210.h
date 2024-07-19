//
// Created by nanaue on 2024/7/12.
//

#ifndef CAR_V2_K210_H
#define CAR_V2_K210_H

typedef enum {
    RED_STOP = 10,
    RED_GO,
    RED_BACK,
    RED_TURN_LEFT,
    RED_TURN_RIGHT
} RedFlag;
typedef enum {
    BlackSquare_STOP = 30,
    BlackSquare_GO,
    BlackSquare_BACK,
    BlackSquare_TURN_LEFT,
    BlackSquare_TURN_RIGHT
} BlackSquareFlag;
typedef enum {
    BArea_STOP = 40,
    BArea_GO,
    BArea_BACK,
    BArea_TURN_LEFT,
    BArea_TURN_RIGHT
} BAreaFlag;

extern int16_t K210_Datas1[2];
extern uint8_t K210_Index;
extern uint8_t goods_flag;
extern uint8_t goods_count;
extern uint8_t K210_Val1;
extern uint8_t K210_Val2;
extern int16_t K210_Datas2[2];

void K210_BlackSquareFlagControl();

void K210_BAreaControl();

void K210_Control();

void K210_RedFlagControl();

#endif //CAR_V2_K210_H
