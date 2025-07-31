
#include "uart_printf.h"

#define __ABS(x) (((x)>=0)?(x):-(x))

int uart_printf(const char *fmt, ...)
{
    static char buf[128];
    uint32_t i,len;
    va_list args;
    va_start(args,fmt);
    len = vsnprintf((char *)buf,sizeof(buf),(char *)fmt,args);
    va_end(args);
    i=0;
    while(i<len)
    {
        // 若串口FIFO满了就等待再输出，之前是等FIFO清空，性能还是比较烂的
        while(DL_UART_isTXFIFOFull(UART0));
        DL_UART_transmitData(UART0_INST,buf[i]);
        i++;
    }
    return len;
}

// 重写了print浮点数的逻辑
void uart_print_float(float value, uint8_t precision)
{
    uint8_t i;
    int32_t i32Part = (int32_t)value;
    uart_printf("%d.",i32Part);
    float f32Part = __ABS(value-i32Part);
    for(i=0;i<precision;i++)
    {
        f32Part *= 10;
        i32Part = (int32_t) f32Part;
        uart_printf("%1d",i32Part%10);
    }
}