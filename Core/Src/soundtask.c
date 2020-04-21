#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

extern ADC_HandleTypeDef hadc3;
extern UART_HandleTypeDef huart1;
uint32_t adcVal;
uint8_t uartBuf[4];
void StartSound(void const * argument)
{
  /* USER CODE BEGIN StartConsol */
  /* Infinite loop */

  for(;;)
  {
	  HAL_ADC_Start_IT(&hadc3);
	  /*
	  HAL_ADC_Start(&hadc3);
	  if(HAL_ADC_PollForConversion(&hadc3,5)==HAL_OK)
	  {
		  adcVal = HAL_ADC_GetValue(&hadc3);
		  HAL_UART_Transmit(&huart1, &adcVal, 4, 0xFFFF);
	  }
	  else
	  {
		  HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_3);
	  }
	  */
	  osDelay(1000);
  }
  /* USER CODE END StartConsol */
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adcVal = HAL_ADC_GetValue(&hadc3);
	uartBuf[0] =(uint8_t)adcVal;
	HAL_UART_Transmit(&huart1, (uint8_t *)&adcVal, 1, 0xFFFF);
	//HAL_UART_Transmit(&huart1, (uint8_t *)&uartBuf, 1, 0xFFFF);
}
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef* hadc)
{
	HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_3);
}
