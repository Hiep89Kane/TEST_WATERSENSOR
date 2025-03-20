#include "myHeader.h"

void (*callbackSystickHandle)(void) =&testWaterSensor_1msIrqHandle;
void (*callbackTimer7IrqHandle)(void) =0;
void (*callbackTimer6IrqHandle)(void) = &UV_CAPSS_periodic_poll;

void (*callbackRxUart1IrqHandle)(void) = 0;
void (*callbackTxCptUart1IrqHandle)(void) = 0;

void (*callbackRxUart2IrqHandle)(void) = 0;
void (*callbackTxCptUart2IrqHandle)(void) = 0;

void (*callbackRxUart3IrqHandle)(void) = 0;
void (*callbackTxCptUart3IrqHandle)(void) = 0;

void (*callbackRxUart4IrqHandle)(void) = 0;
void (*callbackTxCptUart4IrqHandle)(void) = 0;



//void (*debugvTimerHandle)(void) = 0;
//void (*Uart1RxIrqHandle)(void) = 0;
//void (*Uart1TxCompleteIrqHandle)(void) =0;
//void (*Uart2RxIrqHandle)(void) = 0;
//void (*Uart2TxCompleteIrqHandle)(void) = 0;

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

  #ifdef _INIT_USE_UART1
      if(huart->Instance == huart1.Instance){
	   if(callbackRxUart1IrqHandle)
	     callbackRxUart1IrqHandle();
      }
  #endif

  #ifdef _INIT_USE_UART2
      if(huart->Instance == huart2.Instance){
	     if(callbackRxUart2IrqHandle)
	       callbackRxUart2IrqHandle();
      }
  #endif

  #ifdef _INIT_USE_UART3
      if(huart->Instance == huart3.Instance){
	     if(callbackRxUart3IrqHandle)
	       callbackRxUart3IrqHandle();
      }
  #endif

  #ifdef _INIT_USE_UART4
      if(huart->Instance == huart4.Instance){
	       if(callbackRxUart4IrqHandle)
		 callbackRxUart4IrqHandle();
      }
  #endif

}

//CallBack Interrupt when Tx buffer completed
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

  #ifdef _INIT_USE_UART1
       if(huart->Instance == huart1.Instance){
	   if(callbackTxCptUart1IrqHandle)
	     callbackTxCptUart1IrqHandle();
       }
  #endif

  #ifdef _INIT_USE_UART2
       if(huart->Instance == huart2.Instance){
	     if(callbackTxCptUart2IrqHandle)
	       callbackTxCptUart2IrqHandle();
       }
  #endif

  #ifdef _INIT_USE_UART3
       if(huart->Instance == huart3.Instance){
	       if(callbackTxCptUart3IrqHandle)
		 callbackTxCptUart3IrqHandle();
       }
  #endif

#ifdef _INIT_USE_UART4
     if(huart->Instance == huart4.Instance){
	       if(callbackTxCptUart4IrqHandle)
		 callbackTxCptUart4IrqHandle();
     }
#endif
}

/**
  * @brief  Conversion complete callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadcX){
  //80-120us
  if (hadcX->Instance == hadc1.Instance){

  }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

  if (htim->Instance == htim3.Instance)
  {

  }

  if (htim->Instance == htim6.Instance)
  {
//      if(callbackTimer6IrqHandle)
//	callbackTimer6IrqHandle();
      UV_CAPSS_periodic_poll();
  }

  //1ms
  if (htim->Instance == htim7.Instance)
  {
      if(callbackTimer7IrqHandle)
	callbackTimer7IrqHandle();
  }

  //103 uS
  if (htim->Instance == htim14.Instance)
  {

  }
}

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
void HAL_SYSTICK_Callback(void){
  if(callbackSystickHandle)
    callbackSystickHandle();
}


