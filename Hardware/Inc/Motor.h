//
// Created by nanaue on 2024/7/30.
//

#ifndef CAR_V2_MOTOR_H
#define CAR_V2_MOTOR_H
#define Z_Down "G01 Z15F5000\n"
#define Z_Reset "G01 Z0F5000\n"
#define Move(x, y, z, t) sprintf(cmd,"G01 X%dY%dZ%dF%d\n",x,y,z,t)

void Motor_Init();

void SeizeChess();

void FreeChess();

#endif //CAR_V2_MOTOR_H
