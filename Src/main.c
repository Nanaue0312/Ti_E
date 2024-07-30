#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "OLED.h"
#include "Ti_USART.h"
#include "EXTIConfig.h"
#include "Delay.h"
#include "Piece.h"
#include "Motor.h"
#include "Ti_USART.h"
#include "Magnet.h"

int main(void) {
    // 初始化led
    // LED_Init();

    // LED_Control();
    // 初始化电磁铁
    Magnet_Init();
    // 初始化串口
    Serial1_Init();
    Serial2_Init();
    Motor_Init();
    printf("Start\n");
    // 初始化外部中断
    EXTI_Config();
    for (;;) {
    }
}


/**+
 * K3,K4按键中断,用于更新PWM占空比
 */
void EXTI9_5_IRQHandler() {
    if (EXTI_GetITStatus(EXTI_Line8) == SET) {
        if (GPIO_ReadInputDataBit(GPIOC, K3) == SET) {
            FreeChess();
        }
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    if (EXTI_GetITStatus(EXTI_Line9) == SET) {
        if (GPIO_ReadInputDataBit(GPIOC, K4) == SET) {
            SeizeChess();
        }
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}

/**
 * 合并2个字节序列
 * @param buffer
 * @param i
 * @return 合并后的16位数据
 */
uint16_t getDataBytes(const char *buffer, size_t i) {
    uint16_t temp = ((uint16_t) buffer[i] << 8) |
                    (uint16_t) buffer[i + 1];
    return temp;
}

// K210数据解析
void K210DataParse(const char *buffer, int16_t *output, size_t buffer_length) {
    // 将每四个字节转换为浮点数
    for (size_t i = 0; i < buffer_length; i += 2) {
        // 通过类型转换将四个字节合成一个浮点数
        uint16_t temp = getDataBytes(buffer, i);
        int16_t value = *((int16_t *) &temp);
        value = (int) 100 * value + 0.5;
        value /= 100;
        output[i / 2] = value; // 存入输出数组
    }
}

void USART1_IRQHandler() {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        Data1 = USART_ReceiveData(USART1);
        // K210数据包解析
        if (RxFlag1 == 0 && Data1 == 0x2C) {
            RxFlag1 = 1;
        } else if (RxFlag1 == 1 && Data1 == 0x12) {
            RxFlag1 = 2;
        } else if (RxFlag1 == 2 && Data1 == 0x5B) {
            // 重置状态
            RxFlag1 = 0;
            // BufferIndex = 0;
        } else if (RxFlag1 == 2) {
            // 接收数据包数据段
            DataBuffer1[BufferIndex1++] = Data1;
        } else {
            // 重置状态
            RxFlag1 = 0;
            // BufferIndex = 0;
        }
        // BufferIndex==24时数据接收完毕
        if (BufferIndex1 >= 4) {
            // 将字节数组转为K210浮点数据
            // K210DataParse(DataBuffer1, K210_Datas1, BufferIndex1);
            // K210_Val1 = K210_Datas1[1];
            // memset(DataBuffer1, 0, sizeof(DataBuffer1));
            RxFlag1 = 0;
            BufferIndex1 = 0;
        }
    }
}

void USART2_IRQHandler() {
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        Data2 = USART_ReceiveData(USART2);
        // K210数据包解析
        if (RxFlag2 == 0 && Data2 == 0x2C) {
            RxFlag2 = 1;
        } else if (RxFlag2 == 1 && Data2 == 0x12) {
            RxFlag2 = 2;
        } else if (RxFlag2 == 2 && Data2 == 0x5B) {
            // 重置状态
            RxFlag2 = 0;
            // BufferIndex = 0;
        } else if (RxFlag2 == 2) {
            // 接收数据包数据段
            DataBuffer2[BufferIndex2++] = Data2;
        } else {
            // 重置状态
            RxFlag2 = 0;
            // BufferIndex = 0;
        }
        // BufferIndex==24时数据接收完毕
        if (BufferIndex2 >= 4) {
            // 将字节数组转为K210浮点数据
            // K210DataParse(DataBuffer2, K210_Datas2, BufferIndex2);
            // K210_Val2 = K210_Datas2[1];
            // memset(DataBuffer2, 0, sizeof(DataBuffer2));
            RxFlag2 = 0;
            BufferIndex2 = 0;
        }
    }
}