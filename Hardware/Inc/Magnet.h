//
// Created by nanaue on 2024/7/31.
//

#ifndef CAR_V2_MAGNET_H
#define CAR_V2_MAGNET_H

#define Magnet_Port GPIOA
#define Magnet_Pin GPIO_Pin_11

void Magnet_Init();

void Magnet_SeizeChess();

void Magnet_FreeChess();

#endif //CAR_V2_MAGNET_H
