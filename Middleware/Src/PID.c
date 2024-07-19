//
// Created by nanaue on 2024/7/4.
//
#include "stm32f10x.h"
#include "PID.h"
#include "Encoder.h"
#include "Motor.h"
#include "Delay.h"
#include "K210.h"

// 速度环PID
t_PID PID_Velocity_Left;
t_PID PID_Velocity_Right;
// 角度环PID
t_PID PID_Angle;
// 转向环PID
t_PID PID_Turn;

int16_t encode_left;
int16_t encode_right;
float Out_Left = 0;
float Out_Right = 0;
extern uint8_t Lock;

/**
 * 初始化PID
 * @param pid 需要初始化的PID结构体
 * @param pidMode PID模式
 * @param p p参数
 * @param i i参数
 * @param d d参数
 * @param target 目标值,时间间隔10ms
 */
void PID_Init(t_PID *pid, PID_MODE pidMode, float p, float i, float d) {
    pid->pidMode = pidMode;
    pid->p = p;
    pid->i = i;
    pid->d = d;
}

/**
 * 重置PID积分量
 * @param pid PID结构体
 */
void PID_Reset(t_PID *pid) {
    pid->pout = 0;
    pid->dout = 0;
    pid->iout = 0;
}

/**
 * 设置PID结构体目标值
 * @param pid 需要设置的PID结构体
 * @param target 目标值
 */
void PID_SetTarget(t_PID *pid, float target) {
    pid->target = target;
}

/**
 * PID控制函数
 */
// void PID_Control() {
//     if (runStatus == Straight) {
//         Straight_Control();
//     } else if (runStatus == Back) {
//         Straight_Control();
//     } else {
//         Left_Turn_Control();
//     }
// }


/**
 * 小车左转
 */
void Left_Turn_Control() {
    PID_SetTarget(&PID_Velocity_Left, 0);
    PID_SetTarget(&PID_Velocity_Right, 0);
    // 所有传感器都检测到黑线，后退并转弯
    Motor_Control(0, 1600);
}

/**
 * 小车右转
 */
void Right_Turn_Control() {
    PID_SetTarget(&PID_Velocity_Left, 0);
    PID_SetTarget(&PID_Velocity_Right, 0);
    // 所有传感器都检测到黑线，后退并转弯
    Motor_Control(1600, 0);
}


/**
 * 小车直行
 */
void Straight_Control() {
    // PID_Angle.now = kalmanAngle.Yaw;
    // PID_Cal(&PID_Angle);
    // PID速度环控制
    // 解码得出1s的圈数

    PID_Velocity_Left.now = encode_left / (0.01 * 1040);
    PID_Velocity_Right.now = encode_right / (0.01 * 1040);
    PID_Cal(&PID_Velocity_Left);
    PID_Cal(&PID_Velocity_Right);
    Out_Left = PID_Velocity_Left.out;
    Out_Right = PID_Velocity_Right.out;
    PID_Out_Limit(&Out_Left);
    PID_Out_Limit(&Out_Right);
    Motor_Control(Out_Left, Out_Right);
}

/**
 * PID计算函数
 * @param pid 用于计算的PID结构体
 */
void PID_Cal(t_PID *pid) {
    pid->bias[0] = pid->target - pid->now;
    if (pid->pidMode == DELTA_PID) {
        pid->pout = pid->p * (pid->bias[0] - pid->bias[1]);
        pid->iout = pid->i * pid->bias[0];
        pid->dout = pid->d * (pid->bias[0] - 2 * pid->bias[1] + pid->bias[2]);
        pid->out += pid->pout + pid->iout + pid->dout;
    } else if (pid->pidMode == POSITION_PID) {
        pid->pout = pid->p * pid->bias[0];
        pid->iout += pid->i * pid->bias[0];
        pid->dout = pid->d * (pid->bias[0] - pid->bias[1]);
        pid->out = pid->pout + pid->iout + pid->dout;
    }
    pid->bias[2] = pid->bias[1];
    pid->bias[1] = pid->bias[0];
}

void PID_Out_Limit(float *ccr) {
    if (*ccr >= 6000) {
        *ccr = 6000;
    } else if (*ccr <= -6000) {
        *ccr = -6000;
    }
}

