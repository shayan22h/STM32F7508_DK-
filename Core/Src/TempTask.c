#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim3;

static void Timer3_Delay (uint16_t _count);

void StartTempTask(void const * argument)
{
  /* USER CODE BEGIN StartConsol */
  /* Infinite loop */

	HAL_TIM_Base_Start(&htim3);
  for(;;)
  {

	  for (int j =0;j<5000;j++)
	  {
		  for (int i =0; i< 1000;i++)
		  {
			  Timer3_Delay(100);
		  }
	  }



	  HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_3);

  }
  /* USER CODE END StartConsol */
}

static void Timer3_Delay (uint16_t _count)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);
	while(__HAL_TIM_GET_COUNTER(&htim3)< _count);
}
