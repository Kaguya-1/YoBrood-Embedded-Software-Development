/** ==================================================================================== 
 * @file EE_API.c                                                             
 * @author K.vijlbrief                                     
 * @date 13-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief EE API VGA driver source file, contains all of the internal functions that are used by the library
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */


// Rest of the includes for the global libraries
#include "main.h"
#include "EE_API.h"
// Must be included for now, because we are still using system_error_handler
#include "SYSTEM_drivers.h"
#include "stm32f4xx_hal_tim.h"


void API_TIM1_init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = VGA_TIM1_PRESCALE;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = VGA_TIM1_PERIOD;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    SYSTEM_error_handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    SYSTEM_error_handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    SYSTEM_error_handler();
  }
}

void API_TIM2_init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = VGA_TIM2_HSYNC_PRESCALE;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = VGA_TIM2_HSYNC_PERIOD;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    SYSTEM_error_handler();
  }

  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    SYSTEM_error_handler();
  }


  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    SYSTEM_error_handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = VGA_TIM2_HTRIGGER_START - VGA_TIM2_DMA_DELAY;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    SYSTEM_error_handler();
  } 

  sConfigOC.Pulse = VGA_TIM2_HSYNC_IMP;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    SYSTEM_error_handler();
  }  
}

void API_GPIO_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, VGA_BLUE0_Pin|VGA_BLUE1_Pin|VGA_GREEN0_Pin|VGA_GREEN1_Pin
                          |VGA_GREEN2_Pin|VGA_RED0_Pin|VGA_RED1_Pin|VGA_RED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VGA_HSYNC_Pin|VGA_VSYNC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : VGA_BLUE0_Pin VGA_BLUE1_Pin VGA_GREEN0_Pin VGA_GREEN1_Pin
                          VGA_GREEN2_Pin VGA_RED0_Pin VGA_RED1_Pin VGA_RED2_Pin */
  GPIO_InitStruct.Pin = VGA_BLUE0_Pin|VGA_BLUE1_Pin|VGA_GREEN0_Pin|VGA_GREEN1_Pin
                          |VGA_GREEN2_Pin|VGA_RED0_Pin|VGA_RED1_Pin|VGA_RED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : VGA_HSYNC_Pin VGA_VSYNC_Pin */
  GPIO_InitStruct.Pin = VGA_HSYNC_Pin|VGA_VSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  // RCC clock enable is already present in SYSTEM_GPIO.c
  GPIO_InitStruct.Pin = VGA_HSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(VGA_HSYNC_GPIO_Port, &GPIO_InitStruct);
}

void API_DMA_init(TIM_HandleTypeDef* tim_baseHandle)
{
  __HAL_RCC_TIM1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  hdma_tim1_up.Instance = DMA2_Stream5;
  hdma_tim1_up.Init.Channel = DMA_CHANNEL_6;
  hdma_tim1_up.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_tim1_up.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_tim1_up.Init.MemInc = DMA_MINC_ENABLE;
  hdma_tim1_up.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tim1_up.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_tim1_up.Init.Mode = DMA_NORMAL;
  hdma_tim1_up.Init.Priority = DMA_PRIORITY_VERY_HIGH;
  hdma_tim1_up.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  if (HAL_DMA_Init(&hdma_tim1_up) != HAL_OK)
  {
    SYSTEM_error_handler();
  }

  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

  __HAL_LINKDMA(tim_baseHandle,hdma[TIM_DMA_ID_UPDATE],hdma_tim1_up);
}


void API_IT_init(TIM_HandleTypeDef* tim_pwmHandle)
{
  if(tim_pwmHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    //__HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }  
}