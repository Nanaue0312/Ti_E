//
// Created by nanaue on 2024/7/3.
//
#include "stm32f10x.h"
#include "Car.h"
#include "Motor.h"
#include "OLED.h"
#include "Car_USART.h"
#include "Car_EXTI.h"
#include "Encoder.h"
#include "Car_Global_TIM.h"
#include "PID.h"
#include "MPU6050.h"
#include "SG90.h"
#include "HMC5883L.h"
#include "GrayTrack.h"

/**
 * 硬件初始化函数，初始化:电机、OLED、串口
 */
void Car_Init() {
    // 初始化OLED
    OLED_Init();
    OLED_Clear();
    // 初始化电机
    Motor_Init();
    // 初始化编码器
    Encoder_Init();
    // 初始化按键中断
    Car_EXTI_Config();
    // 初始化MPU6050
    MPU6050_Init();
    // 初始化HMC5883
    HMC5883L_Init();
    // 初始化舵机
    Servo_Init();
    // 初始化串口
    Car_Serial1_Init();
    Car_Serial2_Init();
    // 初始化灰度传感器
    GrayTrack_Init();
    // 初始化全局定时器
    Car_Global_TIM();
}


void Car_Config() {
    PID_Init(&PID_Velocity_Left, DELTA_PID, 10, 25.0f, 0);
    PID_Init(&PID_Velocity_Right, DELTA_PID, 10, 25.0f, 0);

    PID_SetTarget(&PID_Velocity_Left, 2);
    PID_SetTarget(&PID_Velocity_Right, 2);

    PID_Init(&PID_Turn, POSITION_PID, 0.005f, 0, 0);
    PID_SetTarget(&PID_Turn, 160);
}
