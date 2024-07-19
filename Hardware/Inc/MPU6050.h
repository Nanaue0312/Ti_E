//
// Created by nanaue on 2024/7/5.
//

#ifndef CAR_V2_MPU6050_H
#define CAR_V2_MPU6050_H

/* MPU6050_REG */
#define    MPU6050_ADDRESS       0xD0

#define    MPU6050_SMPLRT_DIV        0x19
#define    MPU6050_CONFIG            0x1A
#define    MPU6050_GYRO_CONFIG        0x1B
#define    MPU6050_ACCEL_CONFIG    0x1C

#define    MPU6050_ACCEL_XOUT_H    0x3B
#define    MPU6050_ACCEL_XOUT_L    0x3C
#define    MPU6050_ACCEL_YOUT_H    0x3D
#define    MPU6050_ACCEL_YOUT_L    0x3E
#define    MPU6050_ACCEL_ZOUT_H    0x3F
#define    MPU6050_ACCEL_ZOUT_L    0x40
#define    MPU6050_TEMP_OUT_H        0x41
#define    MPU6050_TEMP_OUT_L        0x42
#define    MPU6050_GYRO_XOUT_H        0x43
#define    MPU6050_GYRO_XOUT_L        0x44
#define    MPU6050_GYRO_YOUT_H        0x45
#define    MPU6050_GYRO_YOUT_L        0x46
#define    MPU6050_GYRO_ZOUT_H        0x47
#define    MPU6050_GYRO_ZOUT_L        0x48

#define    MPU6050_PWR_MGMT_1        0x6B
#define    MPU6050_PWR_MGMT_2        0x6C
#define    MPU6050_WHO_AM_I         0x75

#define MPU6050_INT 0x38
#define MPU6050_INT_CFG 0x37
#define MPU6050_INT_STATUS 0x3A

/* end */

#define q30  1073741824.0f // 用于dmp数据获取


typedef struct {
    int16_t AccX, AccY, AccZ;
    int16_t GyroX, GyroY, GyroZ;
} tMPU6050;

typedef struct {
    float RollAcc, PitchAcc, YawAcc;
    float RollGyro, PitchGyro, YawGyro;
} tMPU6050_Angle;

extern int16_t AccX;
extern int16_t AccY;
extern int16_t AccZ;
extern int16_t GyroX;
extern int16_t GyroY;
extern int16_t GyroZ;

extern float RollGyro;
extern float PitchGyro;
extern float YawGyro;
extern float RollAcc;
extern float PitchAcc;
extern float YawAcc;

// void MPU6050_WriteReg(uint8_t address, uint8_t data);
uint8_t MPU6050_Write(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

uint8_t MPU6050_Read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

void MPU6050_WriteReg(uint8_t reg, uint8_t data);

uint8_t MPU6050_ReadReg(uint8_t reg);

void MPU6050_Init(void);

uint8_t MPU6050_GetID();

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

void MPU6050_Data_Analyze();


#endif //CAR_V2_MPU6050_H
