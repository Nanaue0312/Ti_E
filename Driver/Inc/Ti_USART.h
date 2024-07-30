#ifndef __CAR_USART_H
#define __CAR_USART_H

#define USART1_PORT GPIOB
#define USART1_TX GPIO_Pin_6
#define USART1_RX GPIO_Pin_7
extern uint16_t BufferIndex1;
extern char DataBuffer1[255];
extern uint8_t Data1;
extern uint8_t RxFlag1;

#define USART2_PORT GPIOA
#define USART2_TX GPIO_Pin_2
#define USART2_RX GPIO_Pin_3
extern uint16_t BufferIndex2;
extern char DataBuffer2[255];
extern uint8_t Data2;
extern uint8_t RxFlag2;

void Serial1_Init();

void Serial2_Init();

void Serial_SendByte(uint8_t data);

void Serial_SendString(char *str);

#endif