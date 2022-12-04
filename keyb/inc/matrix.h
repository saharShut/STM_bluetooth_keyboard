/*
 * matrix.h
 *
 *  Created on: 15 нояб. 2022 г.
 *      Author: User
 */

#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

#include "stm32f1xx_hal.h"
#include <list>
#include <map>


class Matrix
{
private:
	void outputs_init();

	void inputs_init();

	void gpio_pin_init(uint32_t pin, uint32_t mode, GPIO_TypeDef *gpio_port);

	void matrix_init();

	Matrix();

	static Matrix* matrix;

public:
	/**
	 * Override clone constructor
	 */
	Matrix(Matrix &other) = delete;

	/**
	 * Override assert operator
	 */
	void operator=(const Matrix &) = delete;

	static Matrix *get_instance();

	std::list<uint8_t> scan();
};



#endif /* INC_MATRIX_H_ */
