/** ==================================================================================== 
 * @file EE_API.h                                                             
 * @author A.Kamphuis, C.Fletcher, K.Vijlbrief                                     
 * @date 13-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief main function for executing the program
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

#include <stdint.h>
#include "SYSTEM_drivers.h"
#include "EE_API.h"
#include "stm32f4xx_hal.h"
#include "main.h"



int main(void)
{
    /* Init SYSTEM functionality */
    HAL_Init();
    SYSTEM_systemclock_config();

    SYSTEM_GPIO_Init();
    //SYSTEM_DMA_Init();
    SYSTEM_TIM1_Init();
    SYSTEM_TIM2_Init();
    SYSTEM_USART2_Init();


    /* Init API functionality */
    //API_screen_init();

    // Undefined reference, is not written yet
    //API_clearscreen(2);

    while(1)
    {
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

    }

}
