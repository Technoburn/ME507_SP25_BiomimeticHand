/*
 * motor.h
 *
 *  Created on: May 27, 2025
 *      Author: col
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include "stm32g4xx_hal.h"

/**
 * @brief Class for implementing a motor with PH/EN Control,
 * quadrature encoder, current sensing ADC, and current limiting DAC
 */
class Motor
{
public:

	int8_t    effort      = 0;    /**< @brief Most recent effort of motor */
	int32_t   position    = 0;    /**< @brief Total accumulated position of motor */
	int32_t   velocity    = 0;    /**< @brief Most recent velocity of motor */
	uint16_t  current     = 0;    /**< @brief Most recent current draw of motor */
	uint16_t  current_lim = 4095; /**< @brief Most recent current limit of motor */

	// Constructor for Motor object
	Motor(TIM_HandleTypeDef *htim_PWM
	     ,uint32_t PWM_Channel
	     ,GPIO_TypeDef *NSLEEP_GPIO_Port
	     ,uint16_t NSLEEP_Pin
	     ,GPIO_TypeDef *PH_GPIO_Port
	     ,uint16_t PH_Pin
	     ,TIM_HandleTypeDef *htim_ENC
	     ,ADC_HandleTypeDef *hadc
	     ,uint32_t ADC_Channel
	     ,DAC_HandleTypeDef *hdac
	     ,uint32_t DAC_Channel);

	void      start(void);                   // Start Motor and associated peripherals
	void      stop(void);                    // Stop Motor and associated peripherals
	void      enable(void);                  // Enable the motor
	void      disable(void);                 // Disable the motor
	void      set_effort(int32_t duty);      // Set motor effort between -100 and 100
	void      update_enc(void);              // Update encoder count and check for counter reload
	void      set_zero(void);                // Update encoder and set current position to zero
	void      update_current(void);          // Get the current value of the Current-sense ADC
	void      set_current(uint16_t current); // Set the Current Limit using DAC

private:

	TIM_HandleTypeDef* _htim_PWM;         /**< @brief htim TIM Handle for PWM */
	uint32_t           _PWM_Channel;      /**< @brief TIM Channel for PWM */
	GPIO_TypeDef*      _NSLEEP_GPIO_Port; /**< @brief GPIO Port for NSLEEP Pin */
	uint16_t           _NSLEEP_Pin;       /**< @brief GPIO Pin Mask for NSLEEP Pin */
	GPIO_TypeDef*      _PH_GPIO_Port;     /**< @brief GPIO Port for PH Pin */
	uint16_t           _PH_Pin;           /**< @brief GPIO Pin Mask for PH Pin */
	TIM_HandleTypeDef* _htim_ENC;         /**< @brief htim TIM Handle for Encoder */
	ADC_HandleTypeDef* _hadc;             /**< @brief hadc ADC Handle */
	uint32_t           _ADC_Channel;      /**< @brief ADC Channel */
	DAC_HandleTypeDef* _hdac;             /**< @brief hdac DAC Handle */
	uint32_t           _DAC_Channel;      /**< @brief DAC Channel */
	uint16_t           _prev_cnt = 0;     /**< @brief Encoder count from most recent update */
	uint16_t           _prev_time;        /**< @brief Time from most recent update  */
	int32_t            _delta = 0;        /**< @brief Change in count between last 2 updates  */
	int32_t            _dt = 0;           /**< @brief Change in time between last 2 updates  */
};

#endif /* INC_MOTOR_H_ */
