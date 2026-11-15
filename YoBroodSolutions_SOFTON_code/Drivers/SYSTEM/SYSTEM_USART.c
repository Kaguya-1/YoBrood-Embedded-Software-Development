/** ==================================================================================== 
 * @file SYSTEM_USART.c                                                          
 * @author K.Vijlbrief                                    
 * @date 15-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief Contains all of the usart configurations for the project
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

#include "SYSTEM_drivers.h"

UART_HandleTypeDef huart2;

 /**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void SYSTEM_USART2_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    SYSTEM_error_handler();
  }
}