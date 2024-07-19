//
// Created by nanaue on 2024/7/4.
//

#ifndef CAR_V2_PID_H
#define CAR_V2_PID_H
/**
 * PID类型
 */
typedef enum {
    POSITION_PID, // 位置式PID
    DELTA_PID // 增量式PID
} PID_MODE;

/**
 * PID结构体
 */
typedef struct {
    float target; // 目标值
    float now; // 当前值
    float bias[3]; // 误差数组
    float p, i, d; // kp,ki,kd
    float pout, iout, dout;
    float out; // 占空比输出值
    PID_MODE pidMode; // pid类型
} t_PID;

typedef enum {
    Straight = 1,
    Back = 2,
    Turn_Left = 3,
    Turn_Right = 4,
} t_RunStatus;


extern t_PID PID_Velocity_Left;
extern t_PID PID_Velocity_Right;
extern t_PID PID_Angle;

extern t_PID PID_Turn;

extern int16_t encode_left;
extern int16_t encode_right;

extern float Out_Left;
extern float Out_Right;

extern t_RunStatus runStatus;


void PID_Init(t_PID *pid, PID_MODE pidMode, float p, float i, float d);

void PID_SetTarget(t_PID *pid, float target);

void PID_Control();

void PID_Cal(t_PID *pid);

void PID_Out_Limit(float *ccr);

void Left_Turn_Control();

void Right_Turn_Control();

void Straight_Control();

void PID_Reset(t_PID *pid);

void Turning_Control();

#endif //CAR_V2_PID_H
