#include "stm32f10x.h"
#include "PID.h"

//仿原子延时，不进入systic中断
void delay_us(u32 nus) {
    u32 temp;
    SysTick->LOAD = 9 * nus;
    SysTick->VAL = 0X00;//清空计数器
    SysTick->CTRL = 0X01;//使能，减到零是无动作，采用外部时钟源
    do {
        temp = SysTick->CTRL;//读取当前倒计数值
    } while ((temp & 0x01) && (!(temp & (1 << 16))));//等待时间到达
    SysTick->CTRL = 0x00; //关闭计数器
    SysTick->VAL = 0X00; //清空计数器
}

void delay_ms(u16 nms) {
    u32 temp;
    SysTick->LOAD = 9000 * nms;
    SysTick->VAL = 0X00;//清空计数器
    SysTick->CTRL = 0X01;//使能，减到零是无动作，采用外部时钟源
    do {
        temp = SysTick->CTRL;//读取当前倒计数值
    } while ((temp & 0x01) && (!(temp & (1 << 16))));//等待时间到达
    SysTick->CTRL = 0x00; //关闭计数器
    SysTick->VAL = 0X00; //清空计数器
    PID_Reset(&PID_Velocity_Left);
    PID_Reset(&PID_Velocity_Right);
}

//仿原子延时，不进入systic中断
void Delay_us(u32 nus) {
    delay_ms(nus);
}

void Delay_ms(u16 nms) {
    delay_ms(nms);
}
