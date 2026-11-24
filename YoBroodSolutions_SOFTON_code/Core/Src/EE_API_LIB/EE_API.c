/** ==================================================================================== 
 * @file EE_API.c                                                             
 * @author K.vijlbrief                                     
 * @date 13-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief EE API VGA driver source file, contains all the logic that is used to write 
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

// Dit is echt een druiventest met die branch enzo


 // Rest of the includes for the global libraries
 #include "main.h"
 #include "EE_API.h"
 // Must be included for now, because we are still using system_error_handler
 #include "SYSTEM_drivers.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_tim.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim1_up;

uint8_t VGA_RAM1[(VGA_DISPLAY_X+1)*VGA_DISPLAY_Y] = {255};

VGA_t VGA = {0};

void API_Init(void)
{

  VGA.hsync_cnt = 0;
  VGA.start_adr = (uint32_t)&VGA_RAM1[0];

  MX_DMA_Init();
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();

  // Enable the DMA update request for timer 1
  __HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_UPDATE);
  // Start channel 4 of timer 2, non-interrupt mode, this channel is connected to HSYNC
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  // Start channel 3 of timer 2, interrupt mode, this interrupt is used in code to start timer 1 and drive VSYNC
  HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);
}

int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved)
{
    return 0;
}

void UB_VGA_FillScreen(uint8_t color)
{
  uint16_t xp,yp;

  for(yp = 0; yp < VGA_DISPLAY_Y; yp++) {
    for(xp = 0; xp < VGA_DISPLAY_X; xp++) {
      UB_VGA_SetPixel(xp, yp, color);
    }
    VGA_RAM1[(yp * (VGA_DISPLAY_X + 1)) + VGA_DISPLAY_X] = VGA_COLOR_BLACK;
  }
}


//--------------------------------------------------------------
// put one Pixel on the screen with one color
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
void UB_VGA_SetPixel(uint16_t xp, uint16_t yp, uint8_t color)
{
  if(xp >= VGA_DISPLAY_X)
    xp = 0;
  if(yp >= VGA_DISPLAY_Y)
    yp = 0;

  // Write pixel to ram
  VGA_RAM1[(yp * (VGA_DISPLAY_X + 1)) + xp] = color;
}