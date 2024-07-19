//
// Created by nanaue on 2024/7/14.
//
#include "stm32f10x.h"
#include "GrayTrack.h"
#include "PID.h"
#include "Delay.h"
#include "Motor.h"
#include "K210.h"
#include "OLED.h"

extern uint8_t Lock;

/**
 * 初始化灰度传感器
 */
void GrayTrack_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = OUT1 | OUT2 | OUT3 | OUT4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = OUT5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}

/**
 * 避障函数
 */
void GrayTrack_Track() {
    uint8_t sensor1 = GPIO_ReadInputDataBit(GPIOA, OUT1); // 最左侧传感器
    uint8_t sensor2 = GPIO_ReadInputDataBit(GPIOA, OUT2); // 左中传感器
    uint8_t sensor3 = GPIO_ReadInputDataBit(GPIOA, OUT3); // 中间传感器
    uint8_t sensor4 = GPIO_ReadInputDataBit(GPIOA, OUT4); // 右中传感器
    uint8_t sensor5 = GPIO_ReadInputDataBit(GPIOC, OUT5); // 最右侧传感器

    if ((sensor1 && sensor2 && sensor4 && sensor5) || (sensor1 && sensor5) ||
        (sensor1 && sensor4) ||
        (sensor2 && sensor5) ||
        (sensor2 && sensor4)) {
        Lock = 1;
        // 所有传感器都检测到黑线，后退并转弯
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Motor_Control(-1200, 0);
        // todo 疑似存在误判导致特殊角度倒车过头
        Delay_ms(900);
        PID_Reset(&PID_Velocity_Left);
        PID_Reset(&PID_Velocity_Right);
        Lock = 0;
    } else {
        PID_SetTarget(&PID_Velocity_Left, 2);
        PID_SetTarget(&PID_Velocity_Right, 2);
    }

}