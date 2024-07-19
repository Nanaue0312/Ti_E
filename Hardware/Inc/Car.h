//
// Created by nanaue on 2024/7/3.
//

#ifndef CAR_V2_CAR_H
#define CAR_V2_CAR_H

typedef struct {
    float Roll, Pitch, Yaw;
} Kalman_Angle;

extern float K210_Data[18];
extern Kalman_Angle kalmanAngle;

void Car_Init();

void Car_Config();


#endif //CAR_V2_CAR_H
