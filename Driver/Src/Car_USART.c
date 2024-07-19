#include <stdio.h>
#include "stm32f10x.h"
#include "Car_USART.h"
#include "cJSON.h"

// 串口1
uint16_t BufferIndex1 = 0;
char DataBuffer1[255];
uint8_t Data1 = 0;
uint8_t RxFlag1 = 0;
// 串口2
uint16_t BufferIndex2 = 0;
char DataBuffer2[255];
uint8_t Data2 = 0;
uint8_t RxFlag2 = 0;

void Car_Serial1_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = USART1_TX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = USART1_RX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_PORT, &GPIO_InitStructure);
    /*USART初始化*/
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    /*中断输出配置*/
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    /*USART使能*/
    USART_Cmd(USART1, ENABLE);
}

void Car_Serial2_Init() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = USART2_TX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = USART2_RX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_PORT, &GPIO_InitStructure);
    /*USART初始化*/
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART2, &USART_InitStructure);

    /*中断输出配置*/
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    /*USART使能*/
    USART_Cmd(USART2, ENABLE);
}

void Serial_SendByte(uint8_t data) {
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendString(char *str) {
    for (int i = 0; *(str + i) != '\0'; i++) {
        Serial_SendByte(*(str + i));
    }
}

/*void parseData() {
    cJsonData = cJSON_Parse(DataBuffer1);
    // 速度环调试
    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "stv")) != NULL) {
        PID_Init(&pidMotorLeftSpeed, pidMotorLeftSpeed.kp, pidMotorLeftSpeed.ki, pidMotorLeftSpeed.kd,
                 cJsonValue->valuedouble);
        PID_Init(&pidMotorRightSpeed, pidMotorRightSpeed.kp, pidMotorRightSpeed.ki, pidMotorRightSpeed.kd,
                 cJsonValue->valuedouble);
    }
    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "sp1")) != NULL) {
        PID_Init(&pidMotorLeftSpeed, cJsonValue->valuedouble, pidMotorLeftSpeed.ki, pidMotorLeftSpeed.kd,
                 pidMotorLeftSpeed.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "si1")) != NULL) {
        PID_Init(&pidMotorLeftSpeed, pidMotorLeftSpeed.kp, cJsonValue->valuedouble, pidMotorLeftSpeed.kd,
                 pidMotorLeftSpeed.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "sd1")) != NULL) {
        PID_Init(&pidMotorLeftSpeed, pidMotorLeftSpeed.kp, pidMotorLeftSpeed.ki, cJsonValue->valuedouble,
                 pidMotorLeftSpeed.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "sp2")) != NULL) {
        PID_Init(&pidMotorRightSpeed, cJsonValue->valuedouble, pidMotorRightSpeed.ki, pidMotorRightSpeed.kd,
                 pidMotorRightSpeed.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "si2")) != NULL) {
        PID_Init(&pidMotorRightSpeed, pidMotorRightSpeed.kp, cJsonValue->valuedouble, pidMotorRightSpeed.kd,
                 pidMotorRightSpeed.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "sd2")) != NULL) {
        PID_Init(&pidDistance, pidDistance.kp, pidDistance.ki, cJsonValue->valuedouble,
                 pidDistance.target_val);
    }
    // 距离环调试
    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "dtv")) != NULL) {
        PID_Init(&pidDistance, pidDistance.kp, pidDistance.ki, pidDistance.kd,
                 cJsonValue->valuedouble);
    }
    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "dp")) != NULL) {
        PID_Init(&pidDistance, cJsonValue->valuedouble, pidDistance.ki, pidDistance.kd,
                 pidDistance.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "di")) != NULL) {
        PID_Init(&pidDistance, pidDistance.kp, cJsonValue->valuedouble, pidDistance.kd,
                 pidDistance.target_val);
    }

    if ((cJsonValue = cJSON_GetObjectItem(cJsonData, "dd")) != NULL) {
        PID_Init(&pidDistance, pidDistance.kp, pidDistance.ki, cJsonValue->valuedouble,
                 pidDistance.target_val);
    }
}*/


