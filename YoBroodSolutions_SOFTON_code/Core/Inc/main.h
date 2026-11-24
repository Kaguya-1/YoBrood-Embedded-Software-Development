/** ==================================================================================== 
 * @file main.h                                                             
 * @author A.Kamphuis, C.Fletcher, K.Vijlbrief                                    
 * @date 15-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief header file for the main function, contains all of the pinouts, software configs, etc.
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "stm32f4xx_hal.h"

/* Defines of all the pins */
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

//define/enum for struct between front and logic layer
#define MAX_STR_PARAM_LENGTH 256

typedef enum 
{
    INT_PARAM_1,
    INT_PARAM_2,
    INT_PARAM_3,
    INT_PARAM_4,
    INT_PARAM_5,
    INT_PARAM_6,
    INT_PARAM_7,
    INT_PARAM_8,
    INT_PARAM_9,
    INT_PARAM_10,
    INT_PARAM_11,
    INT_PARAM_12,
    INT_PARAM_COUNT
} int_parameter_t;

typedef enum 
{
    STR_PARAM_1,
    STR_PARAM_2,
    STR_PARAM_3,
    STR_PARAM_4,
    STR_PARAM_5,
    STR_PARAM_COUNT
} str_parameter_t;

typedef struct 
{
    char command_name[MAX_STR_PARAM_LENGTH];
    int int_params[INT_PARAM_COUNT];
    char str_params[STR_PARAM_COUNT][MAX_STR_PARAM_LENGTH];
} command_t;


#endif