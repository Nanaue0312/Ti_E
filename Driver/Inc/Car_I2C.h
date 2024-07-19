#ifndef __CAR_I2C_H
#define __CAR_I2C_H

#define I2C_SCL GPIO_Pin_4
#define I2C_SDA GPIO_Pin_5

void Car_I2C_Init();

void Car_I2C_Start();

void Car_I2C_Stop();

void Car_I2C_SendData(uint8_t data);

uint8_t Car_I2C_ReceiveData();

void Car_I2C_SendAck(uint8_t ack);

uint8_t Car_I2C_ReceiveAck();


#endif