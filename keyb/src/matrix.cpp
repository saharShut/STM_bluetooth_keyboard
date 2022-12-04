/*
 * matrix.cpp - class that control keyboard matrix
 *
 *  Created on: 15 нояб. 2022 г.
 *      Author: User
 */
#include "matrix.h"
#include "gpio_map.h"
#include "key_codes.h"


void Matrix::outputs_init()
{
	gpio_pin_init(Line1_Pin, GPIO_MODE_OUTPUT_PP, Line1_GPIO_Port);
	gpio_pin_init(Line2_Pin, GPIO_MODE_OUTPUT_PP, Line2_GPIO_Port);
	gpio_pin_init(Line3_Pin, GPIO_MODE_OUTPUT_PP, Line3_GPIO_Port);
	gpio_pin_init(Line4_Pin, GPIO_MODE_OUTPUT_PP, Line4_GPIO_Port);
	gpio_pin_init(Line5_Pin, GPIO_MODE_OUTPUT_PP, Line5_GPIO_Port);
	gpio_pin_init(Line6_Pin, GPIO_MODE_OUTPUT_PP, Line6_GPIO_Port);
	gpio_pin_init(Line7_Pin, GPIO_MODE_OUTPUT_PP, Line7_GPIO_Port);
	gpio_pin_init(Line8_Pin, GPIO_MODE_OUTPUT_PP, Line8_GPIO_Port);
	gpio_pin_init(Line9_Pin, GPIO_MODE_OUTPUT_PP, Line9_GPIO_Port);
	gpio_pin_init(Line10_Pin, GPIO_MODE_OUTPUT_PP, Line10_GPIO_Port);
	gpio_pin_init(Line11_Pin, GPIO_MODE_OUTPUT_PP, Line11_GPIO_Port);
	gpio_pin_init(Line12_Pin, GPIO_MODE_OUTPUT_PP, Line12_GPIO_Port);
}

void Matrix::inputs_init()
{
	gpio_pin_init(Line13_Pin, GPIO_MODE_INPUT, Line13_GPIO_Port);
	gpio_pin_init(Line14_Pin, GPIO_MODE_INPUT, Line14_GPIO_Port);
	gpio_pin_init(Line15_Pin, GPIO_MODE_INPUT, Line15_GPIO_Port);
	gpio_pin_init(Line16_Pin, GPIO_MODE_INPUT, Line16_GPIO_Port);
	gpio_pin_init(Line17_Pin, GPIO_MODE_INPUT, Line17_GPIO_Port);
	gpio_pin_init(Line18_Pin, GPIO_MODE_INPUT, Line18_GPIO_Port);
	gpio_pin_init(Line19_Pin, GPIO_MODE_INPUT, Line19_GPIO_Port);
	gpio_pin_init(Line20_Pin, GPIO_MODE_INPUT, Line20_GPIO_Port);
	gpio_pin_init(Line21_Pin, GPIO_MODE_INPUT, Line21_GPIO_Port);
	gpio_pin_init(Line22_Pin, GPIO_MODE_INPUT, Line22_GPIO_Port);
	gpio_pin_init(Line23_Pin, GPIO_MODE_INPUT, Line23_GPIO_Port);
	gpio_pin_init(Line24_Pin, GPIO_MODE_INPUT, Line24_GPIO_Port);
}

void Matrix::gpio_pin_init(uint32_t pin, uint32_t mode, GPIO_TypeDef *gpio_port)
{
	GPIO_InitTypeDef initStructure = {
		.Pin = pin,
		.Mode = mode,
		.Pull = GPIO_PULLDOWN,
		.Speed = GPIO_SPEED_FREQ_HIGH,
	};

	HAL_GPIO_Init(gpio_port, &initStructure);
}

void Matrix::matrix_init()
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	outputs_init();
	inputs_init();
}

Matrix::Matrix()
{
	matrix_init();
}

Matrix* Matrix::matrix = nullptr;

// Static methods must be defined out class
Matrix *Matrix::get_instance()
{
	if(matrix == nullptr)
	{
		matrix = new Matrix();
	}
	return matrix;
}

std::list<uint8_t> Matrix::scan()
{
	// Created a list containing pressed keys codes
	std::list<uint8_t> pressedKeys;
	pressedKeys.clear();
	// set hight voltage on first pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_VOLUMEUP);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_PROPS);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_PAUSE);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_PAGEUP);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP7);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP5);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP0);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPENTER);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F11);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F13);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_POWER);
	}
	//set hight voltage on 2 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_PROPS);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_PREVIOUSSONG);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_REFRESH);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPMINUS);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_NUMLOCK);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_LEFTMETA);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_EDIT);
	}
	// set hight voltage on 3 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F14);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_STOP);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_LEFTSHIFT);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_RIGHTSHIFT);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_SPACE);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPPLUS);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_GRAVE);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F3);
	}
	// set hight voltage on 4 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_ESC);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_PLAYPAUSE);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F15);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_CAPSLOCK);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPEQUAL);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP6);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		// Not Use
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F10);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_END);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F2);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_FORWARD);
	}
	// set hight voltage on 5 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_LEFTCTRL);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_VOLUMEDOWN);
	}
	if (HAL_GPIO_ReadPin(Line16_GPIO_Port, Line16_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_RIGHTCTRL);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		// Not Use
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		// Not Use
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_TAB);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_SYSRQ);
	}
	// set hight voltage on 6 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_LEFTALT);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_RIGHTALT);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_Q);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_COMMA);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F12);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F7);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MEDIA_MUTE);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F1);
	}
	// set hight voltage on 7 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F9);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPASTERISK);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_1);
	}
	if (HAL_GPIO_ReadPin(Line16_GPIO_Port, Line16_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(0xA5); // Fn
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_3);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_LEFT);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_BACKSPACE);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_8);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP3);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_102ND);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F4);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_INSERT);
	}
	// set hight voltage on 8 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_HOME);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F8);
	}
	if (HAL_GPIO_ReadPin(Line16_GPIO_Port, Line16_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_2);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_DOWN);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F6);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_9);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP9);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_Z);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPSLASH);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KPDOT);
	}
	// set hight voltage on 9 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_PAGEDOWN);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_V);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_4);
	}
	if (HAL_GPIO_ReadPin(Line16_GPIO_Port, Line16_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_SLASH);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_M);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_MINUS);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F5);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_I);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_RIGHT);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_A);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_SEMICOLON);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_UP);
	}
	// set hight voltage on 10 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_ENTER);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_5);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_S);
	}
	if (HAL_GPIO_ReadPin(Line16_GPIO_Port, Line16_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_0);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_U);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_F);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_B);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_DOT);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_K);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_W);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_RIGHTBRACE);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP4);
	}
	// set hight voltage on 11 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_BACKSPACE);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_X);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_H);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_E);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_J);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_N);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_P);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_L);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_APOSTROPHE);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_6);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP1);
	}
	// set hight voltage on 12 pin and scan other ports
	HAL_GPIO_WritePin(Line1_GPIO_Port, Line1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line2_GPIO_Port, Line2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line3_GPIO_Port, Line3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line4_GPIO_Port, Line4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line5_GPIO_Port, Line5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line6_GPIO_Port, Line6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line7_GPIO_Port, Line7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line8_GPIO_Port, Line8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line9_GPIO_Port, Line9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line10_GPIO_Port, Line10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line11_GPIO_Port, Line11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Line12_GPIO_Port, Line12_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	// scan inputs
	if (HAL_GPIO_ReadPin(Line13_GPIO_Port, Line13_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_C);
	}
	if (HAL_GPIO_ReadPin(Line14_GPIO_Port, Line14_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP2);
	}
	if (HAL_GPIO_ReadPin(Line15_GPIO_Port, Line15_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_R);
	}
	if (HAL_GPIO_ReadPin(Line16_GPIO_Port, Line16_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_LEFTBRACE);
	}
	if (HAL_GPIO_ReadPin(Line17_GPIO_Port, Line17_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_G);
	}
	if (HAL_GPIO_ReadPin(Line18_GPIO_Port, Line18_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_D);
	}
	if (HAL_GPIO_ReadPin(Line19_GPIO_Port, Line19_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_Y);
	}
	if (HAL_GPIO_ReadPin(Line20_GPIO_Port, Line20_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_O);
	}
	if (HAL_GPIO_ReadPin(Line21_GPIO_Port, Line21_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_KP7);
	}
	if (HAL_GPIO_ReadPin(Line22_GPIO_Port, Line22_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_T);
	}
	if (HAL_GPIO_ReadPin(Line23_GPIO_Port, Line23_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_7);
	}
	if (HAL_GPIO_ReadPin(Line24_GPIO_Port, Line24_Pin) == GPIO_PIN_SET)
	{
		pressedKeys.push_front(KEY_102ND);
	}

	return pressedKeys;

}




