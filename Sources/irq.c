
#include "ti_msp_dl_config.h"
#include "encoders.h"
#include "uart_printf.h"

void ButtonPressed_Callback();

void GROUP1_IRQHandler()
{
    // uart_printf("GROUP1_IRQHandler()\r\n");
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
    {
    case PORTB_INT_IIDX:
        {
            switch (DL_GPIO_getPendingInterrupt(PORTB_PORT))
            {
            case PORTB_ENCODER1_A_IIDX:
                if(DL_GPIO_readPins(PORTB_PORT,PORTB_ENCODER1_B_PIN))
                {
                    Encoders_increaseCounter(ENCODER_ID_0,1);
                }
                else
                {
                    Encoders_increaseCounter(ENCODER_ID_0,-1);
                }
                DL_GPIO_clearInterruptStatus(PORTB_PORT,PORTB_ENCODER1_A_PIN);
                break;
            case PORTB_ENCODER2_A_IIDX:
                if(DL_GPIO_readPins(PORTB_PORT,PORTB_ENCODER2_B_PIN))
                {
                    Encoders_increaseCounter(ENCODER_ID_1,1);
                }
                else
                {
                    Encoders_increaseCounter(ENCODER_ID_1,-1);
                }
                DL_GPIO_clearInterruptStatus(PORTB_PORT,PORTB_ENCODER2_A_PIN);
                break;
            case PORTB_BUTTON_S2_IIDX:
                ButtonPressed_Callback();
                DL_GPIO_clearInterruptStatus(PORTB_PORT,PORTB_BUTTON_S2_PIN);
            default:
                break;
            }
        }
        DL_Interrupt_clearGroup(DL_INTERRUPT_GROUP_1,PORTB_INT_IIDX);
        break;
    
    default:
        break;
    }
}

void CONTROL_TIM_INST_IRQHandler()
{
    extern void motorControlTask(void *args);
    motorControlTask(NULL);
    // uart_printf("CONTROL_TIM_INST_IRQHandler()\r\n");
}

uint8_t flagButtonPressed;

void ButtonPressed_Callback()
{
    flagButtonPressed = 1u;
    // uart_printf("Button pressed!\r\n");
}