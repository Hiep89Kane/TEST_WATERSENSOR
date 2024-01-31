#ifndef SRC_PUTCHAR_PUTCHAR_H_
#define SRC_PUTCHAR_PUTCHAR_H_

#define _INIT_USE_UART1
#define _INIT_USE_UART2
//#define _INIT_USE_UART3
#define _INIT_USE_UART4

#ifdef _INIT_USE_UART1
  int uart1_putc(char c);
  int uart1_puts(char *s);
  void PUTCHAR_Uart1TxCompletedHandle(void);
#endif

#ifdef _INIT_USE_UART2
  int uart2_putc(char c);
  int uart2_puts(char *s);
  void PUTCHAR_Uart2TxCompletedHandle(void);
#endif

#ifdef _INIT_USE_UART3
  int uart3_putc(char c);
  int uart3_puts(char *s);
  void PUTCHAR_Uart3TxCompletedHandle(void);
#endif

#ifdef _INIT_USE_UART4
  int uart4_putc(char c);
  int uart4_puts(char *s);
  void PUTCHAR_Uart4TxCompletedHandle(void);
#endif

//put in Uart1 transmit completed Irq callback
void PUTCHAR_Uart1TxCompletedHandle(void);
void PUTCHAR_Uart2TxCompletedHandle(void);
void PUTCHAR_Uart4TxCompletedHandle(void);

#endif /* SRC_PUTCHAR_PUTCHAR_H_ */
