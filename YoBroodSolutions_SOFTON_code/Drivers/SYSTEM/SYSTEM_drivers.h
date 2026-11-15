/** ==================================================================================== 
 * @file SYSTEM_drivers.h                                                             
 * @author K.Vijlbrief                                   
 * @date 15-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief Header file which contains all of the system core functions, such as GPIO, UART and TIM init
 * Houses all of the renamed ST functions, instead of bloating the main.c and main.h files
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

extern UART_HandleTypeDef huart2;



/* Function prototypes */
void SYSTEM_USART2_Init(void);
void SYSTEM_TIM1_Init(void);
void SYSTEM_TIM2_Init(void);
void SYSTEM_GPIO_Init(void);

void SYSTEM_systemclock_config(void);
void SYSTEM_error_handler(void);