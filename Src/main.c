#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "Car.h"
#include "OLED.h"
#include "Car_USART.h"
#include "Car_EXTI.h"
#include "Encoder.h"
#include "PID.h"
#include "GrayTrack.h"
#include "K210.h"

uint8_t Running = 0;
uint8_t Lock = 0;
uint8_t FindB = 0;
uint8_t FindC = 0;

int main(void) {
    Car_Init();
    Car_Config();
    for (;;) {
        // OLED_ShowNum(1, 1, GPIO_ReadInputDataBit(GPIOA, OUT1), 1);
        // OLED_ShowNum(1, 3, GPIO_ReadInputDataBit(GPIOA, OUT2), 1);
        // OLED_ShowNum(1, 5, GPIO_ReadInputDataBit(GPIOA, OUT3), 1);
        // OLED_ShowNum(1, 7, GPIO_ReadInputDataBit(GPIOA, OUT4), 1);
        // OLED_ShowNum(1, 9, GPIO_ReadInputDataBit(GPIOC, OUT5), 1);
        OLED_ShowNum(1, 1, FindB, 1);
        OLED_ShowNum(1, 3, FindC, 1);
        OLED_ShowNum(2, 1, PID_Velocity_Left.target, 2);
        OLED_ShowNum(2, 5, PID_Velocity_Right.target, 2);
        OLED_ShowNum(3, 1, K210_Val1, 2);
        OLED_ShowNum(3, 5, K210_Val2, 2);

        OLED_ShowNum(4, 1, goods_flag, 1);
        OLED_ShowNum(4, 3, goods_count, 1);
        if (Running == 1) {
        }
    }
}


/**
 * K3,K4按键中断,用于更新PWM占空比
 */
void EXTI9_5_IRQHandler() {
    // 按键k3，修改左轮ccr
    if (EXTI_GetITStatus(EXTI_Line8) == SET) {
        if (GPIO_ReadInputDataBit(GPIOC, K3) == RESET) {
            Running = 1;
            FindB = 1;
        }
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    // 按键k4，修改右轮ccr
    if (EXTI_GetITStatus(EXTI_Line9) == SET) {
        if (GPIO_ReadInputDataBit(GPIOC, K4) == RESET) {
            Running = 1;
            FindC = 1;
        }
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
    // MPU6050外部中断，读取数据
    // todo 读取不灵敏，暂不使用
    if (EXTI_GetITStatus(EXTI_Line6) == RESET) {
        if (GPIO_ReadInputDataBit(MPU6050_INT_PORT, MPU6050_INT_PIN) == RESET) {


        }
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
    // 磁力计外部中断，读取数据
    if (EXTI_GetITStatus(EXTI_Line7) == SET) {
        if (GPIO_ReadInputDataBit(HMC_INT_PORT, HMC_INT_PIN) == RESET) {


        }
    }
}


/**
 * 全局定时中断,10ms定时
 */
void TIM1_UP_IRQHandler() {
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
        encode_left = Encoder_Left_Get();
        encode_right = Encoder_Right_Get();
        // MPU6050_GetData(&AccX, &AccY, &AccZ, &GyroX, &GyroY, &GyroZ);
        // MPU6050_Data_Analyze();
        // printf("%d\t%.2f,%.2f,%.2f\t%.2f,%.2f,%.2f\n", MPU6050_GetID(), RollGyro, PitchGyro, YawGyro, RollAcc, PitchAcc,
        //        YawAcc);
        // HMC5883L_GetData(&hmc5883);
        // HMC5883L_DateAnalyze(&hmc5883);
        // kalmanAngle.Roll = Kalman_Filter(&KF_Roll, RollAcc, GyroX / 16.4);
        // kalmanAngle.Pitch = Kalman_Filter(&KF_Pitch, PitchAcc, GyroY / 16.4);
        // kalmanAngle.Yaw = Kalman_Filter(&KF_Yaw, hmcYaw, GyroZ / 16.4);
        // if (kalmanAngle.Yaw >= 180) {
        //     kalmanAngle.Yaw = 180;
        // } else if (kalmanAngle.Yaw <= -180) {
        //     kalmanAngle.Yaw = -180;
        // }
        if (Running == 1) {
            K210_Control();
            if (Lock == 0) {
                GrayTrack_Track();
            }
            Straight_Control();
        }

        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
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

// 2C 12 3F 1F C0 16 BF CF 6F E9 C0 DC 0B 61 43 32 CB A7 40 8A 30 EA 43 2E 65 FC 5B
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
            K210DataParse(DataBuffer1, K210_Datas1, BufferIndex1);
            K210_Val1 = K210_Datas1[1];
            memset(DataBuffer1, 0, sizeof(DataBuffer1));
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
            K210DataParse(DataBuffer2, K210_Datas2, BufferIndex2);
            K210_Val2 = K210_Datas2[1];
            memset(DataBuffer2, 0, sizeof(DataBuffer2));
            RxFlag2 = 0;
            BufferIndex2 = 0;
        }
    }
}