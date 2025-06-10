/*
 * time.h
 *
 *  Created on: May 29, 2025
 *      Author: col
 */

#ifndef INC_TIME_H_
#define INC_TIME_H_

#include <stdint.h>

// Get the current time in microseconds
uint16_t micros(void);

// Calculate the difference between an initial and final time in microseconds
uint16_t time_diff(uint16_t initial_t, uint16_t final_t);

#endif /* INC_TIME_H_ */
