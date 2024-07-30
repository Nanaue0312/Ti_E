#include "../Inc/sys.h"
#include "Ti_USART.h"

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
void WFI_SET(void) {
    __ASM volatile("wfi");
}

//关闭所有中断
void INTX_DISABLE(void) {
    __ASM volatile("cpsid i");
}

//开启所有中断
void INTX_ENABLE(void) {
    __ASM volatile("cpsie i");
}

// 重写printf底层函数
__attribute__((weak)) int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; ++i) {
        Serial_SendByte(ptr[i]);
    }
    return len;
}