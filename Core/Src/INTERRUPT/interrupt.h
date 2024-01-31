/*
 * interrupt.h
 *
 *  Created on: Nov 6, 2020
 *      Author: NGUYEN VAN HIEP
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);            	//===> Đã khai báo trong :  stm32g0xx_hal_uart.h
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);		//===> Đã khai báo trong :  stm32g0xx_hal_uart.h
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);		//===> Đã khai báo trong :  stm32g0xx_hal_tim.h
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);		//===> Đã khai báo trong :  stm32g0xx_hal_adc.h
//void HAL_SYSTICK_Callback(void);					//===> Đã khai báo trong :  stm32g0xx_hal_cortex.h

#endif /*_INTERRUPT_H_ */
