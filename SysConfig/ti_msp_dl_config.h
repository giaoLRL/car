/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the LP_MSPM0G3507
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_LP_MSPM0G3507
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for MOTOR_TIM */
#define MOTOR_TIM_INST                                                     TIMA0
#define MOTOR_TIM_INST_IRQHandler                               TIMA0_IRQHandler
#define MOTOR_TIM_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define MOTOR_TIM_INST_CLK_FREQ                                         10000000
/* GPIO defines for channel 0 */
#define GPIO_MOTOR_TIM_C0_PORT                                             GPIOA
#define GPIO_MOTOR_TIM_C0_PIN                                      DL_GPIO_PIN_8
#define GPIO_MOTOR_TIM_C0_IOMUX                                  (IOMUX_PINCM19)
#define GPIO_MOTOR_TIM_C0_IOMUX_FUNC                 IOMUX_PINCM19_PF_TIMA0_CCP0
#define GPIO_MOTOR_TIM_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_MOTOR_TIM_C1_PORT                                             GPIOA
#define GPIO_MOTOR_TIM_C1_PIN                                     DL_GPIO_PIN_22
#define GPIO_MOTOR_TIM_C1_IOMUX                                  (IOMUX_PINCM47)
#define GPIO_MOTOR_TIM_C1_IOMUX_FUNC                 IOMUX_PINCM47_PF_TIMA0_CCP1
#define GPIO_MOTOR_TIM_C1_IDX                                DL_TIMER_CC_1_INDEX



/* Defines for CONTROL_TIM */
#define CONTROL_TIM_INST                                                (TIMG12)
#define CONTROL_TIM_INST_IRQHandler                            TIMG12_IRQHandler
#define CONTROL_TIM_INST_INT_IRQN                              (TIMG12_INT_IRQn)
#define CONTROL_TIM_INST_LOAD_VALUE                                    (199999U)




/* Defines for I2C0 */
#define I2C0_INST                                                           I2C0
#define I2C0_INST_IRQHandler                                     I2C0_IRQHandler
#define I2C0_INST_INT_IRQN                                         I2C0_INT_IRQn
#define GPIO_I2C0_SDA_PORT                                                 GPIOA
#define GPIO_I2C0_SDA_PIN                                         DL_GPIO_PIN_28
#define GPIO_I2C0_IOMUX_SDA                                       (IOMUX_PINCM3)
#define GPIO_I2C0_IOMUX_SDA_FUNC                        IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_I2C0_SCL_PORT                                                 GPIOA
#define GPIO_I2C0_SCL_PIN                                         DL_GPIO_PIN_31
#define GPIO_I2C0_IOMUX_SCL                                       (IOMUX_PINCM6)
#define GPIO_I2C0_IOMUX_SCL_FUNC                        IOMUX_PINCM6_PF_I2C0_SCL


/* Defines for UART0 */
#define UART0_INST                                                         UART0
#define UART0_INST_FREQUENCY                                            40000000
#define UART0_INST_IRQHandler                                   UART0_IRQHandler
#define UART0_INST_INT_IRQN                                       UART0_INT_IRQn
#define GPIO_UART0_RX_PORT                                                 GPIOA
#define GPIO_UART0_TX_PORT                                                 GPIOA
#define GPIO_UART0_RX_PIN                                         DL_GPIO_PIN_11
#define GPIO_UART0_TX_PIN                                         DL_GPIO_PIN_10
#define GPIO_UART0_IOMUX_RX                                      (IOMUX_PINCM22)
#define GPIO_UART0_IOMUX_TX                                      (IOMUX_PINCM21)
#define GPIO_UART0_IOMUX_RX_FUNC                       IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART0_IOMUX_TX_FUNC                       IOMUX_PINCM21_PF_UART0_TX
#define UART0_BAUD_RATE                                                 (115200)
#define UART0_IBRD_40_MHZ_115200_BAUD                                       (21)
#define UART0_FBRD_40_MHZ_115200_BAUD                                       (45)
/* Defines for UART1 */
#define UART1_INST                                                         UART1
#define UART1_INST_FREQUENCY                                            40000000
#define UART1_INST_IRQHandler                                   UART1_IRQHandler
#define UART1_INST_INT_IRQN                                       UART1_INT_IRQn
#define GPIO_UART1_RX_PORT                                                 GPIOB
#define GPIO_UART1_TX_PORT                                                 GPIOB
#define GPIO_UART1_RX_PIN                                          DL_GPIO_PIN_7
#define GPIO_UART1_TX_PIN                                          DL_GPIO_PIN_6
#define GPIO_UART1_IOMUX_RX                                      (IOMUX_PINCM24)
#define GPIO_UART1_IOMUX_TX                                      (IOMUX_PINCM23)
#define GPIO_UART1_IOMUX_RX_FUNC                       IOMUX_PINCM24_PF_UART1_RX
#define GPIO_UART1_IOMUX_TX_FUNC                       IOMUX_PINCM23_PF_UART1_TX
#define UART1_BAUD_RATE                                                   (9600)
#define UART1_IBRD_40_MHZ_9600_BAUD                                        (260)
#define UART1_FBRD_40_MHZ_9600_BAUD                                         (27)





/* Port definition for Pin Group SENSOR_PORTA */
#define SENSOR_PORTA_PORT                                                (GPIOA)

/* Defines for SENSOR_IN3: GPIOA.7 with pinCMx 14 on package pin 49 */
#define SENSOR_PORTA_SENSOR_IN3_PIN                              (DL_GPIO_PIN_7)
#define SENSOR_PORTA_SENSOR_IN3_IOMUX                            (IOMUX_PINCM14)
/* Port definition for Pin Group PORTA */
#define PORTA_PORT                                                       (GPIOA)

/* Defines for USER_LED: GPIOA.0 with pinCMx 1 on package pin 33 */
#define PORTA_USER_LED_PIN                                       (DL_GPIO_PIN_0)
#define PORTA_USER_LED_IOMUX                                      (IOMUX_PINCM1)
/* Defines for MOTOR_STDBY: GPIOA.27 with pinCMx 60 on package pin 31 */
#define PORTA_MOTOR_STDBY_PIN                                   (DL_GPIO_PIN_27)
#define PORTA_MOTOR_STDBY_IOMUX                                  (IOMUX_PINCM60)
/* Defines for MOTOR_B1: GPIOA.24 with pinCMx 54 on package pin 25 */
#define PORTA_MOTOR_B1_PIN                                      (DL_GPIO_PIN_24)
#define PORTA_MOTOR_B1_IOMUX                                     (IOMUX_PINCM54)
/* Defines for MOTOR_B2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define PORTA_MOTOR_B2_PIN                                      (DL_GPIO_PIN_15)
#define PORTA_MOTOR_B2_IOMUX                                     (IOMUX_PINCM37)
/* Port definition for Pin Group PORTB */
#define PORTB_PORT                                                       (GPIOB)

/* Defines for ENCODER1_A: GPIOB.1 with pinCMx 13 on package pin 48 */
// pins affected by this interrupt request:["ENCODER1_A","ENCODER2_A","BUTTON_S2"]
#define PORTB_INT_IRQN                                          (GPIOB_INT_IRQn)
#define PORTB_INT_IIDX                          (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define PORTB_ENCODER1_A_IIDX                                (DL_GPIO_IIDX_DIO1)
#define PORTB_ENCODER1_A_PIN                                     (DL_GPIO_PIN_1)
#define PORTB_ENCODER1_A_IOMUX                                   (IOMUX_PINCM13)
/* Defines for ENCODER1_B: GPIOB.4 with pinCMx 17 on package pin 52 */
#define PORTB_ENCODER1_B_PIN                                     (DL_GPIO_PIN_4)
#define PORTB_ENCODER1_B_IOMUX                                   (IOMUX_PINCM17)
/* Defines for ENCODER2_A: GPIOB.12 with pinCMx 29 on package pin 64 */
#define PORTB_ENCODER2_A_IIDX                               (DL_GPIO_IIDX_DIO12)
#define PORTB_ENCODER2_A_PIN                                    (DL_GPIO_PIN_12)
#define PORTB_ENCODER2_A_IOMUX                                   (IOMUX_PINCM29)
/* Defines for ENCODER2_B: GPIOB.17 with pinCMx 43 on package pin 14 */
#define PORTB_ENCODER2_B_PIN                                    (DL_GPIO_PIN_17)
#define PORTB_ENCODER2_B_IOMUX                                   (IOMUX_PINCM43)
/* Defines for MOTOR_A1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define PORTB_MOTOR_A1_PIN                                      (DL_GPIO_PIN_24)
#define PORTB_MOTOR_A1_IOMUX                                     (IOMUX_PINCM52)
/* Defines for MOTOR_A2: GPIOB.9 with pinCMx 26 on package pin 61 */
#define PORTB_MOTOR_A2_PIN                                       (DL_GPIO_PIN_9)
#define PORTB_MOTOR_A2_IOMUX                                     (IOMUX_PINCM26)
/* Defines for BUTTON_S2: GPIOB.21 with pinCMx 49 on package pin 20 */
#define PORTB_BUTTON_S2_IIDX                                (DL_GPIO_IIDX_DIO21)
#define PORTB_BUTTON_S2_PIN                                     (DL_GPIO_PIN_21)
#define PORTB_BUTTON_S2_IOMUX                                    (IOMUX_PINCM49)
/* Port definition for Pin Group SENSOR_PORTB */
#define SENSOR_PORTB_PORT                                                (GPIOB)

/* Defines for SENSOR_IN1: GPIOB.10 with pinCMx 27 on package pin 62 */
#define SENSOR_PORTB_SENSOR_IN1_PIN                             (DL_GPIO_PIN_10)
#define SENSOR_PORTB_SENSOR_IN1_IOMUX                            (IOMUX_PINCM27)
/* Defines for SENSOR_IN2: GPIOB.11 with pinCMx 28 on package pin 63 */
#define SENSOR_PORTB_SENSOR_IN2_PIN                             (DL_GPIO_PIN_11)
#define SENSOR_PORTB_SENSOR_IN2_IOMUX                            (IOMUX_PINCM28)
/* Defines for SENSOR_IN4: GPIOB.22 with pinCMx 50 on package pin 21 */
#define SENSOR_PORTB_SENSOR_IN4_PIN                             (DL_GPIO_PIN_22)
#define SENSOR_PORTB_SENSOR_IN4_IOMUX                            (IOMUX_PINCM50)
/* Defines for SENSOR_IN5: GPIOB.23 with pinCMx 51 on package pin 22 */
#define SENSOR_PORTB_SENSOR_IN5_PIN                             (DL_GPIO_PIN_23)
#define SENSOR_PORTB_SENSOR_IN5_IOMUX                            (IOMUX_PINCM51)
/* Defines for SENSOR_IN6: GPIOB.25 with pinCMx 56 on package pin 27 */
#define SENSOR_PORTB_SENSOR_IN6_PIN                             (DL_GPIO_PIN_25)
#define SENSOR_PORTB_SENSOR_IN6_IOMUX                            (IOMUX_PINCM56)
/* Defines for SENSOR_IN7: GPIOB.26 with pinCMx 57 on package pin 28 */
#define SENSOR_PORTB_SENSOR_IN7_PIN                             (DL_GPIO_PIN_26)
#define SENSOR_PORTB_SENSOR_IN7_IOMUX                            (IOMUX_PINCM57)





/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSCTL_CLK_init(void);
void SYSCFG_DL_MOTOR_TIM_init(void);
void SYSCFG_DL_CONTROL_TIM_init(void);
void SYSCFG_DL_I2C0_init(void);
void SYSCFG_DL_UART0_init(void);
void SYSCFG_DL_UART1_init(void);

void SYSCFG_DL_SYSTICK_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
