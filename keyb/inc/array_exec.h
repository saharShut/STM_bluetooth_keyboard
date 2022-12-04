/*
 * array_exec.h - convert incoming array to uint8_t array[8] that
 * 		send to ESP01
 *
 *  Created on: 22 нояб. 2022 г.
 *      Author: User
 */

#ifndef __ARRAY_EXEC_H__
#define __ARRAY_EXEC_H__

#include "stm32f1xx_hal.h"
#include <list>

class ArrayExecutor
{
public:
	static uint8_t *convert_array(std::list<uint8_t> array);
};


#endif /* INC_ARRAY_EXEC_H_ */
