//
// Created by nanaue on 2024/7/30.
//

#ifndef CAR_V2_MOTOR_H
#define CAR_V2_MOTOR_H
#define Z_Down "G01 Z15F5000\n"
#define Z_Reset "G01 Z5F3000\n"
#define Move(x, y, t) sprintf(cmd,"G01 X%dY%dF%d\n",x,y,t)
#define X_BIAS 59
#define Y_BIAS -126

extern char cmd[30];

void Motor_Init();

void SeizeChess();

void FreeChess();

void Motor_Move(int16_t x, int16_t y, int16_t z, int16_t t);

#endif //CAR_V2_MOTOR_H
