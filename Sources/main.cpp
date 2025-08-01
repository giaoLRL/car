
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "ti_msp_dl_config.h"
#include "ti/iqmath/include/IQmathLib.h"
#include "uart_printf.h"
#include "encoders.h"
#include "Motor.hpp"

/* === BEGIN OF Global Variables ===*/
// 走一次直线编码器大概的自增量
const uint32_t averageEncoderIncreaseNum = 120u;

uint8_t cycleNumber = 1; // 记录运行次数
typedef enum
{
    STATE_SETTING,              // 设置圈数
    STATE_START_LINE_FOLLOW,    // 开始循线
} CarState_EnumTypedef;
CarState_EnumTypedef carState = STATE_SETTING;

static TaskHandle_t slotFunctionTask_handle;
static TaskHandle_t blinkTask_handle;
static TaskHandle_t mainTask_handle;
static TaskHandle_t printLogTask_handle;

/* === END OF Global Variables ===*/

/* === BEGIN OF GraySensor === */
/* 读取灰度传感器，由于代码简单就直接Static inline掉了 */
/* 反正静态内联函数性能高一点 */
__STATIC_INLINE uint8_t GraySensor_readGPIO()
{
    return \
    (   (DL_GPIO_readPins(SENSOR_PORTB_PORT,SENSOR_PORTB_SENSOR_IN7_PIN) ? (1u << 6) : 0u) | \
        (DL_GPIO_readPins(SENSOR_PORTB_PORT,SENSOR_PORTB_SENSOR_IN6_PIN) ? (1u << 5) : 0u) | \
        (DL_GPIO_readPins(SENSOR_PORTB_PORT,SENSOR_PORTB_SENSOR_IN5_PIN) ? (1u << 4) : 0u) | \
        (DL_GPIO_readPins(SENSOR_PORTB_PORT,SENSOR_PORTB_SENSOR_IN4_PIN) ? (1u << 3) : 0u) | \
        (DL_GPIO_readPins(SENSOR_PORTA_PORT,SENSOR_PORTA_SENSOR_IN3_PIN) ? (1u << 2) : 0u) | \
        (DL_GPIO_readPins(SENSOR_PORTB_PORT,SENSOR_PORTB_SENSOR_IN2_PIN) ? (1u << 1) : 0u) | \
        (DL_GPIO_readPins(SENSOR_PORTB_PORT,SENSOR_PORTB_SENSOR_IN1_PIN) ? (1u << 0) : 0u)
    );
}

__STATIC_INLINE float GraySensor_getBias()
{
    // 系数
    const float coeffArray[7] = {-3,-2,-1,0,1,2,3};
    uint8_t i;
    float blackPointNum = 0;    // 灰度传感器得到的黑点数量
    float totalValue = 0;
    uint8_t ioOut = GraySensor_readGPIO();
    for (i=0; i < 7; i++)
    {
        
        if((ioOut & (1u << i)))
        {
            totalValue += coeffArray[i];
            blackPointNum += 1;
        }
    }
    if(blackPointNum == 0) return 0.0f;
    else return totalValue / blackPointNum;
}

/* === END OF GraySensor === */

/* === BEGIN OF motorControl === */
extern "C"
{
    void motorControlTask(void *args);
}
// 电机的控制部分
#define MOTOR_SPEED_KP (0.01f)
#define MOTOR_SPEED_KI (1.0e-3f)
#define MOTOR_SPEED_KD (0.0f)

static Motor motor1(
    PID(PID::PID_type::position_type,
        MOTOR_SPEED_KP,
        MOTOR_SPEED_KI,
        MOTOR_SPEED_KD,
        1.2,
        -1.2
    ),
    ENCODER_ID_0,
    585
);

static Motor motor2(
    PID(PID::PID_type::position_type,
        MOTOR_SPEED_KP,
        MOTOR_SPEED_KI,
        MOTOR_SPEED_KD,
        1.2,
        -1.2
    ),
    ENCODER_ID_1,
    585
);

// 本来想塞进RTOS里看起来不行就这样得了
// 100Hz的反馈频率已经不错了
void motorControlTask(void *args)
{
    float pwma_duty,pwmb_duty;
    pwma_duty = motor1.updateDutyCycle(0.01);
    pwmb_duty = motor2.updateDutyCycle(0.01);
    if(pwma_duty >= 0) 
    {
        DL_GPIO_setPins(PORTB_PORT,PORTB_MOTOR_A1_PIN);
        DL_GPIO_clearPins(PORTB_PORT,PORTB_MOTOR_A2_PIN);
        DL_Timer_setCaptureCompareValue(MOTOR_TIM_INST,(uint32_t)(pwma_duty*1000),DL_TIMER_CC_0_INDEX);
    }else 
    {
        DL_GPIO_clearPins(PORTB_PORT,PORTB_MOTOR_A1_PIN);
        DL_GPIO_setPins(PORTB_PORT,PORTB_MOTOR_A2_PIN);
        DL_Timer_setCaptureCompareValue(MOTOR_TIM_INST,(uint32_t)(-pwma_duty*1000),DL_TIMER_CC_0_INDEX);
    }
    if(pwmb_duty >= 0) 
    {
        DL_GPIO_setPins(PORTA_PORT,PORTA_MOTOR_B1_PIN);
        DL_GPIO_clearPins(PORTA_PORT,PORTA_MOTOR_B2_PIN);
        DL_Timer_setCaptureCompareValue(MOTOR_TIM_INST,(uint32_t)(pwmb_duty*1000),DL_TIMER_CC_1_INDEX);
    }else 
    {
        DL_GPIO_clearPins(PORTA_PORT,PORTA_MOTOR_B1_PIN);
        DL_GPIO_setPins(PORTA_PORT,PORTA_MOTOR_B2_PIN);
        DL_Timer_setCaptureCompareValue(MOTOR_TIM_INST,(uint32_t)(-pwmb_duty*1000),DL_TIMER_CC_1_INDEX);
    }
}
// 差分方式控制电机速度
void motorControl_setSpeed_DiffMode(float commonSpeed,float diffSpeed)
{
    motor1.setExpectedSpeed(commonSpeed + diffSpeed/2.0f);
    motor2.setExpectedSpeed(- commonSpeed + diffSpeed/2.0f);
}

/* === END OF End of motorControl === */

/* === BEGIN OF signalSlot === */

extern uint8_t flagButtonPressed;

static void slotFunction_ButtonClicked()
{
    // uart_printf("Button clicked!\r\n");
    if(carState == STATE_SETTING) cycleNumber = (cycleNumber)%6+1;
}


static void slotFunction_ButtonHolded()
{
    // uart_printf("Button holded!\r\n");
    if(carState == STATE_SETTING) carState = STATE_START_LINE_FOLLOW;
    // 只有在停止循线之后才能停下
    // else if(carState == STATE_START_LINE_FOLLOW) carState = STATE_SETTING;
}

static void slotFunctionTask(void *arg)
{
    uint8_t i;
    while (true)
    {
        if(flagButtonPressed)
        {
            // 需要判断是长按还是短按，每10ms判断一次
            // 长按达到500ms作为长按，执行长按的回调函数
            flagButtonPressed = 0;
            for(i=0;i<10;i++)
            {
                // 有以下两种情况：按键在10ms又被按了一次，或者10ms后松开了
                // 第一种暂不考虑进去
                if((flagButtonPressed || DL_GPIO_readPins(PORTB_PORT,PORTB_BUTTON_S2_PIN))) break;
                vTaskDelay(pdMS_TO_TICKS(100));
            }
            if(i == 10){
                slotFunction_ButtonHolded();
                while(!DL_GPIO_readPins(PORTB_PORT,PORTB_BUTTON_S2_PIN)) vTaskDelay(pdMS_TO_TICKS(100));
            }
            else slotFunction_ButtonClicked();
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
}

/* === END OF signalSlot === */

/* === BEGIN OF blinkTask === */

// 这里的闪灯需要判断状态
static void blinkTask(void *arg)
{
    uint8_t i;
    while (true)
    {
        switch (carState)
        {
        case STATE_SETTING:
            for(i=0;i<cycleNumber;i++)
            {
                DL_GPIO_clearPins(PORTA_PORT,PORTA_USER_LED_PIN);
                vTaskDelay(pdMS_TO_TICKS(100));
                DL_GPIO_setPins(PORTA_PORT,PORTA_USER_LED_PIN);
                vTaskDelay(pdMS_TO_TICKS(100));
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
            break;
        case STATE_START_LINE_FOLLOW:
            DL_GPIO_clearPins(PORTA_PORT,PORTA_USER_LED_PIN);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;
        default:
            vTaskDelay(pdMS_TO_TICKS(10));
            break;
        }
    }
    
}

/* === END OF blinkTask === */

/* === BEGIN OF lineFollowTask === */

#define COMMON_SPEED_RPM    90

// 循线PID对象
PID lineFollowPID(PID::PID_type::position_type,
        0.5,
        0.0,
        0.0,
        1,
        -1
        );

// 循线主要逻辑代码
// 这里就专门执行循线任务
static void lineFollowTask(uint8_t num)
{
    uint8_t i;
    uint8_t graySensor_GPIOValues;
    float graySensor_Bias;
    float feedbackSpeedRPM;
    uint8_t cornerCnt = 0;
    uint8_t maxCnt = num * 4; // 经过角点 = 圈数 * 4
    uint32_t t0=0,t1=0,t2=0;
    // 先获取一次FreeRTOS的Tick
    t0 = pdTICKS_TO_MS(xTaskGetTickCount());
    while (true)
    {
        graySensor_GPIOValues = GraySensor_readGPIO();
        graySensor_Bias = GraySensor_getBias();
        if((graySensor_GPIOValues & 0b01000000) && (graySensor_GPIOValues & 0b00000001)) motorControl_setSpeed_DiffMode(0,0);
        else if((graySensor_GPIOValues & 0b00000001) && (graySensor_GPIOValues & 0b00000010) && (~graySensor_GPIOValues & 0b01000000)) // 最左侧的两个LED为黑色同时最右边一个为白色（避免在手上疯转
        {
            // 开环执行一次左转

            // 分步转弯
            // motorControl_setSpeed_DiffMode(60,0);
            // vTaskDelay(pdMS_TO_TICKS(300));
            // motorControl_setSpeed_DiffMode(0,60);
            // vTaskDelay(pdMS_TO_TICKS(950));

            // 平滑转弯
            motorControl_setSpeed_DiffMode(40,60);
            vTaskDelay(pdMS_TO_TICKS(950));
            // motorControl_setSpeed_DiffMode(0,0);
            // vTaskDelay(pdMS_TO_TICKS(25));
            // motorControl_setSpeed_DiffMode(0,0);
            // motorControl_setSpeed_DiffMode(0,0);
            if(cornerCnt == 0)
            {
                t1 = xTaskGetTickCount();
                uart_printf("T1 Encoder1 value: %d\r\n",Encoders_getCounter(ENCODER_ID_0));
                uart_printf("T1 Encoder2 value: %d\r\n",Encoders_getCounter(ENCODER_ID_1));
            }
            else if(cornerCnt == 1)
            {
                t2 = xTaskGetTickCount();
                uart_printf("T2 Encoder1 value: %d\r\n",Encoders_getCounter(ENCODER_ID_0));
                uart_printf("T2 Encoder2 value: %d\r\n",Encoders_getCounter(ENCODER_ID_1));
            }
            cornerCnt += 1;
            // 暂且忽略转向先写循线
            // goto ignore_turning;
            // uart_printf("Turn left. Corner cnt = %d.\r\n",cornerCnt);
        }
        else
        {
            // 根据偏置正常进行循线即可
            // ignore_turning:
            feedbackSpeedRPM = lineFollowPID.calc(graySensor_Bias)*60;
            motorControl_setSpeed_DiffMode(COMMON_SPEED_RPM,feedbackSpeedRPM);
        }
        if(cornerCnt == maxCnt)
        {
            // 再稍微向前走一点再停止
            // motorControl_setSpeed_DiffMode(COMMON_SPEED_RPM,0);
            // vTaskDelay(pdMS_TO_TICKS(1500));
            // motorControl_setSpeed_DiffMode(0,0);
            break;
        }
        // motorControl_setSpeed_DiffMode(30,0);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    // 最后再循线一段秒停止，大概停在黑线中央
    // 这个时间按前面运行的时间估算
    uint8_t finalCycles = (t2 + t0 - 2 * t1) / 20;
    for(i=0;i<finalCycles;i++)
    {
        graySensor_Bias = GraySensor_getBias();
        feedbackSpeedRPM = lineFollowPID.calc(graySensor_Bias)*60;
        motorControl_setSpeed_DiffMode(COMMON_SPEED_RPM,feedbackSpeedRPM);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    // 执行完毕后立即停止电机
    motorControl_setSpeed_DiffMode(0,0);
}

/* === END OF lineFollowTask === */

/* === BEGIN OF mainTask === */

static void testTask()
{
    motorControl_setSpeed_DiffMode(60,90);
    vTaskDelay(pdMS_TO_TICKS(600));
    motorControl_setSpeed_DiffMode(0,0);
    vTaskDelay(pdMS_TO_TICKS(50));
}

static void mainTask(void *args)
{
    while(true)
    {
        if(carState == STATE_START_LINE_FOLLOW)
        {
            lineFollowTask(cycleNumber);
            // testTask();
            carState = STATE_SETTING;
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

/* === END OF mainTask === */

/* === BEGIN OF printLogTask === */

static void printLogTask(void *args)
{
    while (true)
    {
        uart_printf(" ===== LOG TASK ===== \r\n");
        uart_printf("Current heap free size: %d bytes.\r\n",xPortGetFreeHeapSize());
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    
}

/* === END OF printLogTask === */

int main()
{
    // 据我个人测试下来TI板卡特有的抽象问题
    // 上电延迟一段时间直到时钟稳定为止
    // 相当于延迟20ms
    volatile uint32_t waitTicks = 64000;
    while(waitTicks--);
    SYSCFG_DL_init();
    // 复位编码器计数器，使能编码器中断
    Encoders_resetAllCounters();
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
    NVIC_EnableIRQ(CONTROL_TIM_INST_INT_IRQN);
    DL_Timer_startCounter(CONTROL_TIM_INST);
    // 使能电机驱动器
    DL_GPIO_setPins(PORTA_PORT, PORTA_MOTOR_STDBY_PIN);

    
    
    xTaskCreate(slotFunctionTask,"slotFunctionTask",0x80,NULL,configMAX_PRIORITIES-2,&slotFunctionTask_handle);
    xTaskCreate(blinkTask,"blinkTask",0x80,NULL,configMAX_PRIORITIES-2,&blinkTask_handle);
    xTaskCreate(mainTask,"mainTask",0x80,NULL,configMAX_PRIORITIES-1,&mainTask_handle);
    xTaskCreate(printLogTask,"printLogTask",0x80,NULL,configMAX_PRIORITIES-3,&printLogTask_handle);
    vTaskStartScheduler();
}
