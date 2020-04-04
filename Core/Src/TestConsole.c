#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;

static void TestConsole_GetByte(uint8_t * _pRxByte);
uint8_t RxCalback[13] = "RxCalback \r\n";
uint8_t ErrCalback[13] = "ErrCalback \r\n";
uint8_t RxBuffer[20];

void StartConsol(void const * argument)
{
  /* USER CODE BEGIN StartConsol */
  /* Infinite loop */

  for(;;)
  {

	  /*
    osDelay(1000);
    if(HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_2))
    {
    	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_3,GPIO_PIN_SET);
    }
    else
    {
    	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_3,GPIO_PIN_RESET);
    }
    */
   // HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, 1, 0xFFFF);
  }
  /* USER CODE END StartConsol */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_3);
}
uint8_t UART_IRQ_Handler(UART_HandleTypeDef * usart)
{
//	if (usart->Instance == USART1)
	{
	    UART_HandleTypeDef *huart = &huart1;
	    uint32_t isrflags   = READ_REG(huart->Instance->ISR);
	    uint32_t cr1its     = READ_REG(huart->Instance->CR1);
			uint32_t cr3its     = READ_REG(huart->Instance->CR3);
			/* UART Over-Run interrupt occurred -----------------------------------------*/
		if (((isrflags & USART_ISR_ORE) != 0U)
					&& (((cr1its & USART_CR1_RXNEIE) != 0U) ||
							((cr3its & USART_CR3_EIE) != 0U)))
		{
			__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_OREF);
		}


	    if (((isrflags & USART_ISR_RXNE) != 0U) && ((cr1its & USART_CR1_RXNEIE) != 0U))
		{
            // CallBack
	    	TestConsole_GetByte(&RxBuffer[0]);

	    	 __HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
			return 1;
		}

	    if (((isrflags & USART_ISR_TXE) != 0U) && ((cr1its & USART_CR1_TXEIE) != 0U))
		{
            // Transmit
			return 1;
		}
		if(( huart1.Instance->ISR & USART_ISR_RTOF)==USART_ISR_RTOF)
		{

			huart1.Instance->ICR |= USART_ICR_RTOCF ;
            return 1;
		}
	}
	return 0;
}

static void TestConsole_GetByte(uint8_t * _pRxByte)
{
*_pRxByte = (uint8_t)(huart1.Instance->RDR & (uint8_t)0x00FF);
}

