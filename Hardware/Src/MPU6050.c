#include <math.h>
#include "stm32f10x.h" // Device header
#include "MPU6050.h"
#include "Car_I2C.h"

int16_t AccX;
int16_t AccY;
int16_t AccZ;
int16_t GyroX;
int16_t GyroY;
int16_t GyroZ;

float RollGyro;
float PitchGyro;
float YawGyro;
float RollAcc;
float PitchAcc;
float YawAcc;

tMPU6050 mpu6050;
tMPU6050_Angle mpu6050Angle;

void MPU6050_WriteReg(uint8_t address, uint8_t data) {
    Car_I2C_Start();
    Car_I2C_SendData(MPU6050_ADDRESS);
    Car_I2C_ReceiveAck();
    Car_I2C_SendData(address);
    Car_I2C_ReceiveAck();
    Car_I2C_SendData(data);
    Car_I2C_ReceiveAck();
    Car_I2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t address) {
    Car_I2C_Start();
    Car_I2C_SendData(MPU6050_ADDRESS);
    Car_I2C_ReceiveAck();
    Car_I2C_SendData(address);
    Car_I2C_ReceiveAck();

    Car_I2C_Start();
    Car_I2C_SendData(MPU6050_ADDRESS | 0x01);
    Car_I2C_ReceiveAck();
    uint8_t data = Car_I2C_ReceiveData();
    Car_I2C_SendAck(1);
    Car_I2C_Stop();
    return data;
}

void MPU6050_Init() {
    Car_I2C_Init();
    /*MPU6050寄存器初始化，需要对照MPU6050手册的寄存器描述配置，此处仅配置了部分重要的寄存器*/
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x02);        //电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);        //电源管理寄存器2，保持默认值0，所有轴均不待机
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x27);        //采样率分频寄存器，配置采样率
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);            //配置寄存器，配置DLPF
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);    //陀螺仪配置寄存器，选择满量程为±2000°/s
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);    //加速度计配置寄存器，选择满量程为±16g
}

uint8_t MPU6050_GetID() {
    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

// void MPU6050_GetData(tMPU6050 *mpu6050) {
//     int16_t DataH, DataL;
//     DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
//     DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
//     mpu6050->AccX = (DataH << 8) | DataL;
//     DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
//     DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
//     mpu6050->AccY = (DataH << 8) | DataL;
//     DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
//     DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
//     mpu6050->AccZ = (DataH << 8) | DataL;
//
//     DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
//     DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
//     mpu6050->GyroX = (DataH << 8) | DataL;
//     DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
//     DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
//     mpu6050->GyroY = (DataH << 8) | DataL;
//     DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
//     DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
//     mpu6050->GyroZ = DataH << 8 | DataL;
// }
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ) {
    int16_t DataH, DataL;
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    *(AccX) = (DataH << 8) | DataL;
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    *(AccY) = (DataH << 8) | DataL;
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    *(AccZ) = (DataH << 8) | DataL;

    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    *(GyroX) = (DataH << 8) | DataL;
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    *(GyroY) = (DataH << 8) | DataL;
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    *(GyroZ) = DataH << 8 | DataL;
}

/**
 * 解析MPU6050数据
 * @param mpu6050 mpu6050原始数据
 * @param mpu6050Angle mpu6050解析后的数据
 */
void MPU6050_Data_Analyze() {
    // 获取陀螺仪角度
    RollGyro += (float) GyroX / 16.4 * 0.001;
    PitchGyro += (float) GyroY / 16.4 * 0.001;
    YawGyro += (float) GyroZ / 16.4 * 0.001;
    // 获取加速度计角度
    RollAcc = atan((float) AccY / AccZ) * 57.296;
    PitchAcc = -atan((float) AccX / AccZ) * 57.296;
    YawAcc = atan((float) AccY / AccX) * 57.296;
}