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


/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = VGA_TIM1_PRESCALE;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = VGA_TIM1_PERIOD;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = VGA_TIM2_HSYNC_PRESCALE;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = VGA_TIM2_HSYNC_PERIOD;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = VGA_TIM2_HTRIGGER_START - VGA_TIM2_DMA_DELAY;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  sConfigOC.Pulse = VGA_TIM2_HSYNC_IMP;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
      /**
      @attention This system error caller is obviously the wrong implementation of error handling, this needs to be fixed
      Errors should be handled with error codes, that could be returned to layer 2, so this should change the error code instead of calling SYSTEM_error_handler()
      */
      SYSTEM_error_handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}




void MX_GPIO_Init(void)
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
}

void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

}
