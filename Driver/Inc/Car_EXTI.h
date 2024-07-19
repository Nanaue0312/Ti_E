//
// Created by nanaue on 2024/7/2.
//

#ifndef CAR_V2_CAR_EXTI_H
#define CAR_V2_CAR_EXTI_H
#define K4 GPIO_Pin_9
#define K3 GPIO_Pin_8

#define MPU6050_INT_PORT GPIOC
#define MPU6050_INT_PIN GPIO_Pin_6
// HMC中断引脚
#define HMC_INT_PORT GPIOC
#define HMC_INT_PIN GPIO_Pin_7

void Car_EXTI_Config();

void MPU6050_EXTI_Config();

void HMC5883L_EXTI_Config();

#endif //CAR_V2_CAR_EXTI_H
