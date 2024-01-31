//#ifndef SRC_LCD_I2C_LCD_DISPLAY_H_
//#define SRC_LCD_I2C_LCD_DISPLAY_H_
//
//#include "lcd_i2c.h"
//
//#ifdef _USER_TEXT_LCD_NUM_ROW
//#undef _USER_TEXT_LCD_NUM_ROW
//#define _USER_TEXT_LCD_NUM_ROW	2
//#endif
//
//#define _STRING_BUFFER_SIZE	_USER_TEXT_LCD_NUM_COL+1
//
////So Screen cần hiển thị
//typedef enum{
//  _TabScreen0 =0,
//  _TabScreen1,
//  _TabScreen2,
//  //..
//  _TabScreenMax,
//}tabScreen_e;
//
//typedef void (*pShowScreen)(tabScreen_e idTab, char *arg);
//
//typedef struct {
//  char _strData[_USER_TEXT_LCD_NUM_ROW][_STRING_BUFFER_SIZE];
//  tabScreen_e tabManager;
//  pShowScreen showScreenTab[_TabScreenMax];
//  timer_virtual_t *_timer_update;
//}LcdDisplay_t;
//
//void lcd_display_init(LcdDisplay_t *display_tmp, timer_virtual_t *timerUpdate);
//void lcd_display_loop(LcdDisplay_t *display_tmp);
//
//#endif /* SRC_LCD_I2C_LCD_DISPLAY_H_ */
