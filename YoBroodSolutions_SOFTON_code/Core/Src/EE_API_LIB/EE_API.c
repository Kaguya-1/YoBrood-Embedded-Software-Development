/** ==================================================================================== 
 * @file EE_API.c                                                             
 * @author K.vijlbrief                                     
 * @date 13-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief EE API VGA driver source file, contains all the logic that is used to write 
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

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

void API_VGA_init(void)
{

  VGA.hsync_cnt = 0;
  VGA.start_adr = (uint32_t)&VGA_RAM1[0];

  GPIOB->BSRR = VGA_VSYNC_Pin;

  __HAL_RCC_TIM1_CLK_ENABLE();
  __HAL_RCC_TIM2_CLK_ENABLE();

  API_TIM1_init();
  API_TIM2_init();
  API_IT_init(&htim2);
  API_GPIO_init();
  API_DMA_init(&htim1);


  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);

  __HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_UPDATE);
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