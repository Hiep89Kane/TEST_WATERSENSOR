#include "myHeader.h"
#include "putchar.h"

extern UART_HandleTypeDef huart1;

#ifdef _INIT_USE_UART1
volatile ITStatus Uart1_TxCplt = RESET ;

  int uart1_putc(char c){
    uint32_t start_stick = HAL_GetTick();

    HAL_UART_Transmit_IT(&huart1, (uint8_t *)&c, 1);
    while (Uart1_TxCplt != SET){
      if ((HAL_GetTick() - start_stick) > 100 /*ms*/)
	break;
    }
    Uart1_TxCplt = RESET;
    return c;
  }

  int uart1_puts(char *s){
    uint32_t start_stick = HAL_GetTick();

    HAL_UART_Transmit_IT(&huart1,(uint8_t *)s, strlen(s));
    while (Uart1_TxCplt != SET){
      if ((HAL_GetTick() - start_stick) > 100 /*ms*/)
	break;
    }
    Uart1_TxCplt = RESET;
    return strlen(s);
  }

  void PUTCHAR_Uart1TxCompletedHandle(void){
    Uart1_TxCplt=SET;
  }
#endif

#ifdef _INIT_USE_UART2

  volatile ITStatus Uart2_TxCplt = RESET ;

    int uart2_putc(char c){
      uint32_t start_stick = HAL_GetTick();

      HAL_UART_Transmit_IT(&huart2, (uint8_t *)&c, 1);
      while (Uart2_TxCplt != SET){
        if ((HAL_GetTick() - start_stick) > 100 /*ms*/)
  	break;
      }
      Uart2_TxCplt = RESET;
      return c;
    }

    int uart2_puts(char *s){
      uint32_t start_stick = HAL_GetTick();

      HAL_UART_Transmit_IT(&huart2,(uint8_t *)s, strlen(s));
      while (Uart2_TxCplt != SET){
        if ((HAL_GetTick() - start_stick) > 100 /*ms*/)
  	break;
      }
      Uart2_TxCplt = RESET;
      return strlen(s);
    }

    void PUTCHAR_Uart2TxCompletedHandle(void){
      Uart2_TxCplt=SET;
    }

#endif

#ifdef _INIT_USE_UART3
    volatile ITStatus Uart3_TxCplt = RESET ;

    int uart3_putc(char c){
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)&c, 1);
      while (Uart3_TxCplt != SET);
      Uart3_TxCplt = RESET;
      return c;
    }

    int uart3_puts(char *s){
      HAL_UART_Transmit_IT(&huart3,(uint8_t *)s, strlen(s));
      while (Uart3_TxCplt != SET);
      Uart3_TxCplt = RESET;
      return strlen(s);
    }

    void PUTCHAR_Uart3TxCompletedHandle(void){
      Uart3_TxCplt=SET;
    }
#endif

#ifdef _INIT_USE_UART4
    volatile ITStatus Uart4_TxCplt = RESET ;
    int uart4_putc(char c){
      HAL_UART_Transmit_IT(&huart4, (uint8_t *)&c, 1);
      while (Uart4_TxCplt != SET);
      Uart4_TxCplt = RESET;
      return c;
    }

    int uart4_puts(char *s){
      HAL_UART_Transmit_IT(&huart4,(uint8_t *)s, strlen(s));
      while (Uart4_TxCplt != SET);
      Uart4_TxCplt = RESET;
      return strlen(s);
    }

    void PUTCHAR_Uart4TxCompletedHandle(void){
      Uart4_TxCplt=SET;
    }
#endif






