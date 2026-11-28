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


int moving_counter_1 = 0;
int moving_counter_2 = 0;
int moving_counter_3 = 0;
int moving_counter_4 = 0;

void main_test(void);


int main(void)
{
    /* Init SYSTEM functionality */
    HAL_Init();
    SYSTEM_systemclock_config();

    API_clearscreen(VGA_COLOR_WHITE);


    for(int i = 0; i <= 239; i++)
    {
        API_internalcall_setpixel(50, i, VGA_COLOR_BLACK);
        //UB_VGA_SetPixel(319, i, VGA_COLOR_BLACK);
    }
    for (int i = 0; i <= 319; i++)
    {
        API_internalcall_setpixel(i, 50, VGA_COLOR_BLACK);
        //UB_VGA_SetPixel(i, 239, VGA_COLOR_BLACK);
    }

    API_draw_line(150, 50, 300, 178, VGA_COLOR_BLUE, 0, 0);
    API_draw_line(315, 215, 20, 150, VGA_COLOR_RED, 0, 0);
    API_draw_line(315, 215, 315, 150, VGA_COLOR_MAGENTA, 0, 0);
    API_draw_line(315, 215, 20, 215, VGA_COLOR_CYAN, 0, 0);


    API_draw_rectangle(20, 20, 100, 200, VGA_COLOR_BLUE, 0, 0, 0);


    API_draw_line(20, 20, 50, 70, VGA_COLOR_BLACK, 15, 0);
    


    SYSTEM_GPIO_Init();
    SYSTEM_USART2_Init();
    API_Init();

    HAL_Delay(1000);


    /* Init API functionality */
    //API_screen_init();

    // Undefined reference, is not written yet
    //API_clearscreen(2);

    while(1)
    {
        // HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
        // HAL_Delay(100);
        // HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
        // HAL_Delay(100);
        // HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
        // HAL_Delay(100);
        // HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
        // HAL_Delay(100);
        // HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

        // for(int i = 0; i <= 319; i++)
        // {
        //     API_internalcall_setpixel(i, moving_line_vertical - 1, VGA_COLOR_WHITE);
        //     API_internalcall_setpixel(i, moving_line_vertical, VGA_COLOR_BLACK);
        // }

        // for(int i = 0; i <= 239; i++)
        // {
        //     API_internalcall_setpixel(moving_line_horizontal - 1, i, VGA_COLOR_WHITE);
        //     API_internalcall_setpixel(moving_line_horizontal, i, VGA_COLOR_BLACK);
        // }
        
        // if(moving_line_horizontal >= 320)
        // {
        //     moving_line_horizontal = 0;
        // } else 
        // {
        //     moving_line_horizontal++;
        // }

        // if(moving_line_vertical >= 240)
        // {
        //     moving_line_vertical = 0;
        // } else 
        // {
        //     moving_line_vertical++;
        // }
        // HAL_Delay(20);

        main_test();

    }

}

void main_test(void)
{
        API_draw_line(0, moving_counter_1, 319, moving_counter_2, VGA_COLOR_BLUE, 5, 0);
        //API_draw_line(0, moving_counter_1-50, 319, moving_counter_2-20, VGA_COLOR_YELLOW, 15, 0);
        API_draw_line(0, moving_counter_3, 319, moving_counter_4, VGA_COLOR_RED, 15, 0);
        //API_draw_line(0, moving_counter_3-150, 319, moving_counter_4-80, VGA_COLOR_MAGENTA, 0, 0);

        if(moving_counter_1 >= 240)
        {
            moving_counter_1 = 0;
        } else {
            moving_counter_1 += 2;
        }

        if(moving_counter_2 >= 240)
        {
            moving_counter_2 = 0;
        } else {
            moving_counter_2 += 1;
        }

        if(moving_counter_3 >= 240)
        {
            moving_counter_3 = 0;
        } else {
            moving_counter_3 += 3;
        }

        if(moving_counter_4 >= 240)
        {
            moving_counter_4 = 0;
        } else {
            moving_counter_4 += 5;
        }

        HAL_Delay(10);
}
