//
// Created by nanaue on 2024/7/5.
//

#ifndef CAR_V2_HMC5883L_H
#define CAR_V2_HMC5883L_H
/* HMC5883L Register */
#define HMC5883_ADDRESS 0x3C

#define HMC5883_CONFIGURATION_A 0x00
#define HMC5883_CONFIGURATION_B 0x01

#define HMC5883_Mode 0x02

#define HMC5883_XOUT_MSB 0x03
#define HMC5883_XOUT_LSB 0x04
#define HMC5883_ZOUT_MSB 0x05
#define HMC5883_ZOUT_LSB 0x06
#define HMC5883_YOUT_MSB 0x07
#define HMC5883_YOUT_LSB 0x08

#define HMC5883_STATUS 0x09
#define HMC5883_IDA 0x0A
#define HMC5883_IDB 0x0B
#define HMC5883_IDC 0x0C
/* END */


typedef struct {
    int16_t GaX, GaY, GaZ;
} tHMC5883;

extern tHMC5883 hmc5883;
extern float hmcYaw;

void HMC5883L_Init();

uint32_t HMC5883L_GetID();

void HMC5883L_GetData(tHMC5883 *hmc5883);

void HMC5883L_DateAnalyze(tHMC5883 *hmc5883);

#endif //CAR_V2_HMC5883L_H
