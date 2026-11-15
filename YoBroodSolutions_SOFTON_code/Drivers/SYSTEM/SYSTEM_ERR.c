/** ==================================================================================== 
 * @file SYSTEM_ERR.c                                                          
 * @author K.Vijlbrief                                    
 * @date 15-11-2026              
 * @version a0.1
 *                                                                                      
 * @brief Contains all of the different error reporting functions for the projects
 * @attention Is currently being worked on, not ready for use                                              
 *==================================================================================== */

 #include "main.h"
 #include "SYSTEM_drivers.h"

 /*
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void SYSTEM_error_handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
