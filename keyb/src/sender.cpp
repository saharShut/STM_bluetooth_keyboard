/*
 * sender.cpp - file send frame to ESP32
 */

#include "sender.h"

/*
 * frame consist of 9 bytes
 * 1 - start byte
 * 2 - modifier byte
 * 3 - reserved. Must be 0x00
 * 4 - first pushed key code
 * 5 - second pushed key code
 * 6 - third pushed key code
 * 7 - forth pushed key code
 * 8 - fifth pushed key code
 * 9 - ninth pushed key code
 */
ESP_Writer* ESP_Writer::writer = nullptr;
UART_HandleTypeDef ESP_Writer::uart = {0};

ESP_Writer::ESP_Writer()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();

	    /**USART1 GPIO Configuration
	    PA9     ------> USART1_TX
	    PA10     ------> USART1_RX
	    */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	__HAL_RCC_USART1_CLK_ENABLE();

	ESP_Writer::uart.Instance = USART1;
	ESP_Writer::uart.Init.BaudRate = 115200;
	ESP_Writer::uart.Init.WordLength = UART_WORDLENGTH_8B;
	ESP_Writer::uart.Init.StopBits = UART_STOPBITS_1;
	ESP_Writer::uart.Init.Parity = UART_PARITY_NONE;
	ESP_Writer::uart.Init.Mode = UART_MODE_TX_RX;
	ESP_Writer::uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	ESP_Writer::uart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&uart) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}


}

ESP_Writer *ESP_Writer::get_instance()
{
	if(writer == nullptr)
	{
		writer = new ESP_Writer();
	}
	return writer;
}

void ESP_Writer::send(uint8_t *array)
{
	if (ESP_Writer::writer == nullptr)
	{
		ESP_Writer::get_instance();
	}


	HAL_UART_Transmit(&uart, array, 9, 0xff);

}
