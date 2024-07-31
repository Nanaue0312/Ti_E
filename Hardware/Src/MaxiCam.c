//
// Created by nanaue on 2024/7/31.
//
#include "stm32f10x.h"
#include "MaxiCam.h"

int8_t DataType = 0;


int16_t Centers[9][2] = {{0, 0}};

void insertionSort(int16_t arr[][2], int size) {
    for (int i = 1; i < size; i++) {
        int16_t key[2] = {arr[i][0], arr[i][1]}; // 选择当前元素作为关键字
        int j = i - 1;

        // 将大于 key 的元素向后移动
        while (j >= 0 && arr[j][1] > key[1]) {
            arr[j + 1][0] = arr[j][0];
            arr[j + 1][1] = arr[j][1];
            j--;
        }
        // 插入当前元素
        arr[j + 1][0] = key[0];
        arr[j + 1][1] = key[1];
    }
}