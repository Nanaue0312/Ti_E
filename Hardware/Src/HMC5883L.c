//
// Created by nanaue on 2024/7/5.
//
#include "stm32f10x.h"
#include "Car_I2C.h"
#include "HMC5883L.h"
#include "Car_EXTI.h"
#include <math.h>

tHMC5883 hmc5883;

float hmcYaw = 0;

void HMC5883L_WriteReg(uint8_t RegAddress, uint8_t data) {
    Car_I2C_Start();
    Car_I2C_SendData(HMC5883_ADDRESS);
    Car_I2C_ReceiveAck();
    Car_I2C_SendData(RegAddress);
    Car_I2C_ReceiveAck();
    Car_I2C_SendData(data);
    Car_I2C_ReceiveAck();
    Car_I2C_Stop();
}

uint8_t HMC5883L_ReadReg(uint8_t RegAddress) {
    uint8_t Data;
    Car_I2C_Start();
    Car_I2C_SendData(HMC5883_ADDRESS);
    Car_I2C_ReceiveAck();
    Car_I2C_SendData(RegAddress);
    Car_I2C_ReceiveAck();
    Car_I2C_Start();
    Car_I2C_SendData(HMC5883_ADDRESS | 0x01);
    Car_I2C_ReceiveAck();
    Data = Car_I2C_ReceiveData();
    Car_I2C_SendAck(1);
    Car_I2C_Stop();
    return Data;
}

void HMC5883L_Init() {
    Car_I2C_Init();
    HMC5883L_WriteReg(HMC5883_CONFIGURATION_A, 0x78); // 75hz输出
    HMC5883L_WriteReg(HMC5883_CONFIGURATION_B, 0x20);
    HMC5883L_WriteReg(HMC5883_Mode, 0x00);
}

uint32_t HMC5883L_GetID() {
    return HMC5883L_ReadReg(HMC5883_IDA) << (2 * 8) |
           HMC5883L_ReadReg(HMC5883_IDB) << (1 * 8) |
           HMC5883L_ReadReg(HMC5883_IDC);
}

void HMC5883L_GetData(tHMC5883 *hmc5883) {
    uint8_t DataH, DataL;
    DataH = HMC5883L_ReadReg(HMC5883_XOUT_MSB);
    DataL = HMC5883L_ReadReg(HMC5883_XOUT_LSB);
    hmc5883->GaX = DataH << 8 | DataL;

    DataH = HMC5883L_ReadReg(HMC5883_YOUT_MSB);
    DataL = HMC5883L_ReadReg(HMC5883_YOUT_LSB);
    hmc5883->GaY = DataH << 8 | DataL;

    DataH = HMC5883L_ReadReg(HMC5883_ZOUT_MSB);
    DataL = HMC5883L_ReadReg(HMC5883_ZOUT_LSB);
    hmc5883->GaZ = DataH << 8 | DataL;
}

void HMC5883L_DateAnalyze(tHMC5883 *hmc5883) {
    hmcYaw = atan2(hmc5883->GaX, hmc5883->GaY) * 57.296;
}