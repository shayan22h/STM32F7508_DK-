#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim3;

static void Timer3_Delay (uint16_t _count);
static void Temp_SetPin_OutPut(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
static void Temp_SetPin_Input(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
static void Temp_StartDHT11 (void);
static uint8_t Temp_Check_Response (void);
static uint8_t DHT11_Read (void);

#define DHT11_PORT GPIOG
#define DHT11_PIN GPIO_PIN_6

void StartTempTask(void const * argument)
{
  /* USER CODE BEGIN StartConsol */
  /* Infinite loop */
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);

	uint8_t presence;
	uint8_t firstbyte;

  for(;;)
  {



	  Temp_StartDHT11();
	  //presence = Temp_Check_Response();
	  //firstbyte = DHT11_Read();

	  HAL_Delay(1000);

  }
  /* USER CODE END StartConsol */
}

static void Temp_StartDHT11 (void)
{
	Temp_SetPin_OutPut(DHT11_PORT,GPIO_PIN_6);// Set the PinOutput

	HAL_GPIO_WritePin(DHT11_PORT,GPIO_PIN_6,0); //pull he pin low
	HAL_Delay(19);


	HAL_GPIO_WritePin(DHT11_PORT,GPIO_PIN_6,1); //pull he pin high

	Timer3_Delay(2520); // 30 us


}
static uint8_t Temp_Check_Response (void)
{
	uint8_t response = 0;
	Temp_SetPin_Input(DHT11_PORT,GPIO_PIN_6); // sets as input
	Timer3_Delay(3360); // 40 us
	if (!HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN))
	{
		Timer3_Delay(6720); // 80 us
		if (HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN))
		{
			response = 1;
		}
		else
		{
			response = -1; //255
		}
	}

	while(HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)); // wait for the response
	return response;

}
static uint8_t DHT11_Read (void)
{
	uint8_t i,j;
	for(j=0;j<8;j++)
	{
		while(!HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)); // wait for the response
		Timer3_Delay(3360);
		if(!HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN))
		{
			i &= ~(1<<(7-j)); // write 0
		}
		else
		{
			i |= (1<<(7-j)); // write 1
		}
		while(HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN));
	}

	return i;
}
static void Timer3_Delay (uint16_t _count)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);
	while(__HAL_TIM_GET_COUNTER(&htim3)< _count);
}

static void Temp_SetPin_OutPut(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void Temp_SetPin_Input(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
