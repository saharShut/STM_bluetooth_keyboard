/*
 * sender.h - prepare frame to send to ESP32
 */

#ifndef __SENDER_H__
#define __SENDER_H__

#include "stm32f1xx_hal.h"
#include <list>

class ESP_Writer
{
private:

	ESP_Writer();

	static ESP_Writer *writer;

	static UART_HandleTypeDef uart;
public:
	ESP_Writer(ESP_Writer &other) = delete;

	void operator=(const ESP_Writer &) = delete;

	static ESP_Writer *get_instance();

	void send(uint8_t *array);
};

#endif
