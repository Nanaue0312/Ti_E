//
// Created by nanaue on 2024/7/12.
//
#include "stm32f10x.h"
#include "K210.h"
#include "PID.h"
#include "Delay.h"
#include "Motor.h"

// 0:CX 1:标志位
// 摄像头1，只用于查找方块
int16_t K210_Datas1[2] = {0};
uint8_t goods_flag = 0;
uint8_t goods_count = 0;
uint8_t K210_Val1;

uint8_t K210_Val2;
int16_t K210_Datas2[2] = {0};
extern uint8_t FindB;
extern uint8_t FindC;
extern uint8_t Lock;

void K210_Control() {
    if (K210_Datas1[1] == 0) {
    } else {
        K210_BlackSquareFlagControl();
        K210_Datas1[1] = 0;
    }
    if (K210_Datas2[1] >= 40 && FindB) {
        K210_BAreaControl();
        K210_Datas2[1] = 0;
    } else if (K210_Datas2[1] >= 10 && FindC) {
        K210_RedFlagControl();
        K210_Datas2[1] = 0;
    }
}


/**
 * 寻找黑色方块
 */
void K210_BlackSquareFlagControl() {
    // if (K210_Datas1[1] == BlackSquare_STOP) {
    //     PID_SetTarget(&PID_Velocity_Left, 2);
    //     PID_SetTarget(&PID_Velocity_Right, 2);
    //     PID_Reset(&PID_Velocity_Left);
    //     PID_Reset(&PID_Velocity_Right);
    //     goods_flag = 1;
    // } else
    if (K210_Datas1[1] == BlackSquare_GO) {
        // 直行解锁
        goods_flag = 1;
    } else if (K210_Datas1[1] == BlackSquare_TURN_LEFT) {
        Lock = 1;
        // 左转
        Left_Turn_Control();
        Delay_ms(50);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    } else if (K210_Datas1[1] == BlackSquare_TURN_RIGHT) {
        Lock = 1;
        // 右转的时候加锁
        Right_Turn_Control();
        Delay_ms(50);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
}

/**
 * 寻找B区
 */
void K210_BAreaControl() {
    if (K210_Datas2[1] == BArea_STOP) {
        Lock = 1;
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        PID_SetTarget(&PID_Velocity_Left, 0);
        PID_SetTarget(&PID_Velocity_Right, 0);
        Motor_Control(1600, 1600);
        Delay_ms(500);
        Motor_Control(-1600, -1600);
        Delay_ms(9000);
        Motor_Control(-1200, 0);
        Delay_ms(2000);
        goods_flag = 0;
        goods_count++;
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
    if (K210_Datas2[1] == BArea_GO) {
        PID_SetTarget(&PID_Velocity_Left, 2);
        PID_SetTarget(&PID_Velocity_Right, 2);
    }
    if (K210_Datas2[1] == BArea_TURN_LEFT) {
        Lock = 1;
        // 左转
        Left_Turn_Control();
        Delay_ms(40);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
    if (K210_Datas2[1] == BArea_TURN_RIGHT) {
        Lock = 1;
        // 右转
        Right_Turn_Control();
        Delay_ms(40);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
}

/**
 * 寻找C区
 */
void K210_RedFlagControl() {
    if (K210_Datas2[1] == RED_STOP) {
        Lock = 1;
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        PID_SetTarget(&PID_Velocity_Left, 0);
        PID_SetTarget(&PID_Velocity_Right, 0);
        Motor_Control(1600, 1600);
        Delay_ms(1000);
        Motor_Control(-1600, -1600);
        Delay_ms(9000);
        Motor_Control(-1200, 0);
        Delay_ms(2000);
        goods_flag = 0;
        goods_count++;
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
    if (K210_Datas2[1] == RED_GO) {
        PID_SetTarget(&PID_Velocity_Left, 2);
        PID_SetTarget(&PID_Velocity_Right, 2);
    }
    if (K210_Datas2[1] == RED_TURN_LEFT) {
        Lock = 1;
        // 左转
        Left_Turn_Control();
        Delay_ms(60);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
    if (K210_Datas2[1] == RED_TURN_RIGHT) {
        Lock = 1;
        // 右转
        Right_Turn_Control();
        Delay_ms(60);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    }
}
