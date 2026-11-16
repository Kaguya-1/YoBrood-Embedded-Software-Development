

#include "EE_API.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "SYSTEM_drivers.h"


/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
  __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_CC3); // uncomment HAL_TIM_IRQHandler(&htim2); ^^

  VGA.hsync_cnt++;
  if (VGA.hsync_cnt >= VGA_VSYNC_PERIODE)
  {
    // -----------
    VGA.hsync_cnt = 0;
    // Adresspointer first dot
    VGA.start_adr = (uint32_t)(&VGA_RAM1[0]);
  }

  // HSync-Pixel
  GPIOB->BSRR = (VGA.hsync_cnt < VGA_VSYNC_IMP) ? VGA_VSYNC_Pin << 16u: VGA_VSYNC_Pin;

  // Test for DMA start
  if((VGA.hsync_cnt >= VGA_VSYNC_BILD_START) && (VGA.hsync_cnt <= VGA_VSYNC_BILD_STOP))
  {
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    if (HAL_DMA_Start_IT(&hdma_tim1_up, VGA.start_adr,
                         VGA_GPIOE_ODR_ADDRESS, VGA_DISPLAY_X + 1) != HAL_OK)
    {
      SYSTEM_error_handler();
    }
    __HAL_TIM_ENABLE(&htim1);

    if(VGA.hsync_cnt & 0x01)
      VGA.start_adr += (VGA_DISPLAY_X + 1); // inc after Hsync
  }
  /* USER CODE END TIM2_IRQn 1 */
}


/**
  * @brief This function handles DMA2 stream5 global interrupt.
  */
void DMA2_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream5_IRQn 0 */

  // if (__HAL_DMA_GET_IT_SOURCE(&hdma_tim1_up, DMA_IT_TC)) // not needed?
  // {
    // Timer1 stop
    __HAL_TIM_DISABLE(&htim1);
    // DMA2 disable
    // __HAL_DMA_DISABLE(&hdma_tim1_up); // not needed?
    // switch on black
    GPIOE->BSRR = VGA_GPIO_HINIBBLE << 16u;
  // }

  /* USER CODE END DMA2_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim1_up);
  /* USER CODE BEGIN DMA2_Stream5_IRQn 1 */

  /* USER CODE END DMA2_Stream5_IRQn 1 */
}