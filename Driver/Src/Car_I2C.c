#include "stm32f10x.h"
#include "Car_I2C.h"
#include "Delay.h"

void Car_I2C_WriteSCL(uint8_t val) {
    GPIO_WriteBit(GPIOB, I2C_SCL, (BitAction) val);
}

void Car_I2C_WriteSDA(uint8_t val) {
    GPIO_WriteBit(GPIOB, I2C_SDA, (BitAction) val);
}


uint8_t Car_I2C_ReadSDA() {
    uint8_t data = GPIO_ReadInputDataBit(GPIOB, I2C_SDA);
    return data;
}

/**
 * 初始化I2C，使用模拟I2C
*/
void Car_I2C_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = I2C_SDA | I2C_SCL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    Car_I2C_WriteSDA(1);
    Car_I2C_WriteSCL(1);
}

/**
 * 开启I2C通信
*/
void Car_I2C_Start() {
    Car_I2C_WriteSDA(1);
    Car_I2C_WriteSCL(1);

    Car_I2C_WriteSDA(0);
    Car_I2C_WriteSCL(0);
}

/**
 * 停止I2C通信
*/
void Car_I2C_Stop() {
    Car_I2C_WriteSDA(0);
    Car_I2C_WriteSCL(1);
    Car_I2C_WriteSDA(1);
}

/**
 * I2C发送数据
*/
void Car_I2C_SendData(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        Car_I2C_WriteSDA(data & (0x80 >> i));
        Car_I2C_WriteSCL(1);
        Car_I2C_WriteSCL(0);
    }
}

/**
 * I2C接收数据
*/
uint8_t Car_I2C_ReceiveData() {
    uint8_t data = 0x00;
    Car_I2C_WriteSDA(1);
    for (int i = 0; i < 8; i++) {
        Car_I2C_WriteSCL(1);
        if (Car_I2C_ReadSDA()) {
            data |= 0x80 >> i;
        }
        Car_I2C_WriteSCL(0);
    }
    return data;
}


void Car_I2C_SendAck(uint8_t ack) {
    Car_I2C_WriteSDA(ack);
    Car_I2C_WriteSCL(1);
    Car_I2C_WriteSCL(0);
}

uint8_t Car_I2C_ReceiveAck() {
    // 先释放对SDA的操控
    Car_I2C_WriteSDA(1);
    Car_I2C_WriteSCL(1);
    uint8_t ack = Car_I2C_ReadSDA();
    Car_I2C_WriteSCL(0);
    return ack;
}
