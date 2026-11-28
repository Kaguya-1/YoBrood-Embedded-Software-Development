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
#include "stm32f407xx.h"
#include "stm32f4xx_hal_cortex.h"
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

  // Decrease USART2 and SysTick_IRQn priority so that TIM2 gets full interrupt priority
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);

  // Set target address for the DMA
  DMA2_Stream5->PAR = VGA_GPIOE_ODR_ADDRESS;
}

int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved)
{
    return 0;
}

int API_clearscreen(int color)
{
  uint16_t xp,yp;

  for(yp = 0; yp < VGA_DISPLAY_Y; yp++) {
    for(xp = 0; xp < VGA_DISPLAY_X; xp++) {
      API_internalcall_setpixel(xp, yp, color);
    }
    VGA_RAM1[(yp * (VGA_DISPLAY_X + 1)) + VGA_DISPLAY_X] = VGA_COLOR_BLACK;
  }

  return 0;
}


//--------------------------------------------------------------
// put one Pixel on the screen with one color
// Important : the last Pixel+1 from every line must be black
// This last pixel is used internally by the monitor to calibrate to 0V
// So that the next line of pixels has the correct 0V reference
//--------------------------------------------------------------
void API_internalcall_setpixel(uint16_t xp, uint16_t yp, uint8_t color)
{
  // Maybe consider marking this as an error for user feedback?
  if(xp >= VGA_DISPLAY_X)
    xp = 0;
  if(yp >= VGA_DISPLAY_Y)
    yp = 0;

  // Write pixel to ram
  VGA_RAM1[(yp * (VGA_DISPLAY_X + 1)) + xp] = color;
}

int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved, int reserved2)
{
  int error_code = 0;

  // TODO: infill needs to somehow be processed, so the current line drawing method does not satisfy this requirement

  // We draw the lines of the rectangle with API_draw_line
  // First we start with the upper left coordinate, and then draw the rest of the lines clockwise
  error_code = API_draw_line(x, y, x + width, y, color, 0, 0);
  error_code = API_draw_line(x + width, y, x + width, y + height, color, 0, 0);
  error_code = API_draw_line(x + width, y + height, x, y + height, color, 0, 0);
  error_code = API_draw_line(x, y + height, x, y, color, 0, 0);

  return error_code;
}


// TODO: weight needs to be realised
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
  int error_code = 0;


  if(abs(x_2 - x_1) > abs(y_2 - y_1))
  {
    // If weight == 0, no thickness is being applied, we draw the line normally
    if(weight == 0)
    {
      error_code = API_internalcall_drawLineH(x_1, y_1, x_2, y_2, color);
    } else {
      // If thickness is wanted, we draw weight amount of lines, we want to draw the same amount
      // of lines on either side of the specified coordinates, so we start i with -weight, and count
      // towards positive weight
      for(int i = -weight; i < weight; i++)
      {
        error_code = API_internalcall_drawLineH(x_1 + i, y_1, x_2 + i, y_2, color);
      }
    }
    
  } else {
    if(weight == 0)
    {
      error_code = API_internalcall_drawLineV(x_1, y_1, x_2, y_2, color);
    } else {
      for(int i = -weight; i < weight; i++)
      {
        error_code = API_internalcall_drawLineV(x_1 + i, y_1, x_2 + i, y_2, color);
      }
    }
    
  }

  return error_code;
}



// Adaptation of Bresenham's line drawing algorithm, (soon te be) optimised for c-code execution
// This function specifically draws the horizontal lines
int API_internalcall_drawLineH(int x_1, int y_1, int x_2, int y_2, int color)
{
  int error_code = 0;
  // Rotate the coordinates if the x_1 coordinate is larger, this means we have to draw in reverse
  if(x_1 > x_2)
  {
    int temp = x_1;
    x_1 = x_2;
    x_2 = temp;

    temp = y_1;
    y_1 = y_2;
    y_2 = temp;
  }

  // Calculate x and y delta's
  int dx = x_2 - x_1;
  int dy = y_2 - y_1;

  // dy smaller than 0 means the line has to go up, which means we have to add -1 to y later in the code
  int dir = (dy < 0) ? -1 : 1;
  dy *= dir;

  if(dx != 0)
  {
    // We have to start drawing the line at the beginning of y, so remember this value
    int y = y_1;
    // Calculate the first pixel change needed to draw the line
    int p = 2*dy - dx;

    for(int i = 0; i < dx + 1; i++)
    {
      // Draw the current line coordinate to the framebuffer
      API_internalcall_setpixel(x_1 + i, y, color);

      // If there is a change needed, P would be 0 or higher
      if(p >= 0)
      {
        // Add dir to y, dir is either -1 or 1, depending on how the line is oriented
        y += dir;
        // Calculate the next value of p
        p = p - 2*dx;
      }
      // Calculate the rest of the next value of p
      p = p + 2*dy;
    }
  }

  return error_code;
}



// This function specifically draws the vertical lines
int API_internalcall_drawLineV(int x_1, int y_1, int x_2, int y_2, int color)
{
  int error_code = 0;
  // Rotate the coordinates if the y_1 coordinate is larger, this means we have to draw in reverse
  if(y_1 > y_2)
  {
    int temp = x_1;
    x_1 = x_2;
    x_2 = temp;

    temp = y_1;
    y_1 = y_2;
    y_2 = temp;
  }

  // Calculate x and y delta's
  int dx = x_2 - x_1;
  int dy = y_2 - y_1;

  // dy smaller than 0 means the line has to go up, which means we have to add -1 to y later in the code
  int dir = (dx < 0) ? -1 : 1;
  dx *= dir;

  if(dy != 0)
  {
    // We have to start drawing the line at the beginning of y, so remember this value
    int x = x_1;
    // Calculate the first pixel change needed to draw the line
    int p = 2*dx - dy;

    for(int i = 0; i < dy + 1; i++)
    {
      // Draw the current line coordinate to the framebuffer
      API_internalcall_setpixel(x, y_1 + i, color);

      // If there is a change needed, P would be 0 or higher
      if(p >= 0)
      {
        // Add dir to y, dir is either -1 or 1, depending on how the line is oriented
        x += dir;
        // Calculate the next value of p
        p = p - 2*dy;
      }
      // Calculate the rest of the next value of p
      p = p + 2*dx;
    }
  }

  return error_code;
}