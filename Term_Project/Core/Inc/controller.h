/*
 * controller.h
 *
 *  Created on: May 29, 2025
 *      Author: col
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

#include <stdint.h>

/**
 * @brief Class for implementing a generic PID controller with the option of feed forward
 */
class Controller
{
public:

	float KP = 1; /**< @brief Proportional controller Gain */
	float KF = 0; /**< @brief Feed forward controller Gain */
	float KI = 0; /**< @brief Integral controller Gain */
	float KD = 0; /**< @brief Derivative controller Gain */

	// Constructor for Controller object
	Controller(float K_P, float K_F, float K_I, float K_D);

	int32_t PID(int32_t input, int32_t feedback); // Run one loop of PID control

private:

	int32_t _prev_PV = 0; /**< @brief Previous Process Variable (feedback) */
	int32_t _sum_err = 0; /**< @brief Sum of Errors */
	uint16_t _prev_time; /**< @brief Previous Time */
};

#endif /* INC_CONTROLLER_H_ */
