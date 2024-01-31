/*
#include "myHeader.h"

void ShowLCD_String(CLCD_I2C_Name *lcd_tmp, char *str, uint8_t col, uint8_t row);
void ShowLCD_String(CLCD_I2C_Name *lcd_tmp, char *str, uint8_t col, uint8_t row)
{
	char buffer[_USER_TEXT_LCD_NUM_COL];

	if (row >= _USER_TEXT_LCD_NUM_ROW)
		return;

	for (uint8_t i = 0; i <= _USER_TEXT_LCD_NUM_COL; i++)
	{
		if (i < strlen(str))
			buffer[i] = str[i];
		else
			buffer[i] = ' ';
	}
	buffer[_USER_TEXT_LCD_NUM_COL-col] = 0;

	CLCD_I2C_SetCursor(lcd_tmp, col, row);
	CLCD_I2C_WriteString(lcd_tmp, buffer);
}

void lcd_display_init(LcdDisplay_t *display_tmp, timer_virtual_t *timerUpdate)
{
  if(display_tmp->funcTab==0)return;
  display_tmp->_timer_update = timerUpdate;
  display_tmp->tab_id = _TAB_DEFAULT;

  //clear row data
  memset(display_tmp->_strData,' ',sizeof(display_tmp->_strData));
}

void lcd_display_loop(LcdDisplay_t *display_tmp);



void lcd_display_init(LcdDisplay_t *display_tmp,timer_virtual_t *timerUpdate){
  if(display_tmp->funcTab==0)return;
  display_tmp->_timer_update = timerUpdate;
  display_tmp->tab_id = _TAB_DEFAULT;

  //clear row data
  memset(display_tmp->_strData,' ',sizeof(display_tmp->_strData));
}


void lcd_display_update(LcdDisplay_t *display_tmp){
  static char str_cmp0[_STRING_BUFFER_SIZE],
	      str_cmp1[_STRING_BUFFER_SIZE];
  uint8_t result1, result2;

  if(!timer_expired(&_timer_updateLCD))
    return;
  timer_restart(&_timer_updateLCD);

  if(display_tmp->funcTab[display_tmp->tab_id])
    display_tmp->funcTab[display_tmp->tab_id]();

  //Nếu chuỗi không thay đổi thì return
  result1 = memcmp(TOOL.LcdStr_row[0], str_cmp0, _STRING_BUFFER_SIZE);
  result2 = memcmp(TOOL.LcdStr_row[1], str_cmp1, _STRING_BUFFER_SIZE);
  if(result1 == 0 && result2==0)return;

  //Cập nhật dữ liệu mới lên LCD
  //CLCD_I2C_Clear(&LCD1);
  ShowLCD_String(TOOL.LcdStr_row[0], 0, 0);
  ShowLCD_String(TOOL.LcdStr_row[1], 0, 1);

  memcpy(str_cmp0, TOOL.LcdStr_row[0], _STRING_BUFFER_SIZE);
  memcpy(str_cmp1, TOOL.LcdStr_row[1], _STRING_BUFFER_SIZE);
}


*/
