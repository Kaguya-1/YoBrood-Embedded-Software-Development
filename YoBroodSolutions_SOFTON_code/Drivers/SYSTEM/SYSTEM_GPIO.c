/** ==================================================================================== 
 * @file SYSTEM_GPIO.c                                                          
 * @author K.Vijlbrief                                    
 * @date 15-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief Contains all of the gpio configurations for the project
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

#include "SYSTEM_drivers.h"

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void SYSTEM_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, VGA_BLUE0_Pin|VGA_BLUE1_Pin|VGA_GREEN0_Pin|VGA_GREEN1_Pin
                          |VGA_GREEN2_Pin|VGA_RED0_Pin|VGA_RED1_Pin|VGA_RED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VGA_HSYNC_Pin|VGA_VSYNC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : VGA_BLUE0_Pin VGA_BLUE1_Pin VGA_GREEN0_Pin VGA_GREEN1_Pin
                           VGA_GREEN2_Pin VGA_RED0_Pin VGA_RED1_Pin VGA_RED2_Pin */
  GPIO_InitStruct.Pin = VGA_BLUE0_Pin|VGA_BLUE1_Pin|VGA_GREEN0_Pin|VGA_GREEN1_Pin
                          |VGA_GREEN2_Pin|VGA_RED0_Pin|VGA_RED1_Pin|VGA_RED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
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