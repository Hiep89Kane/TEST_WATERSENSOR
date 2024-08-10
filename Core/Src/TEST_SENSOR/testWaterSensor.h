#ifndef SRC_TEST_SENSOR_TESTWATERSENSOR_H_
#define SRC_TEST_SENSOR_TESTWATERSENSOR_H_

#ifdef _INTERVAL_TICK  /*10 ms*/
#undef _INTERVAL_TICK
#define _INTERVAL_TICK 10
#endif

//redefine for text LCD 16x2
#ifdef _USER_TEXT_LCD_NUM_COL
#undef _USER_TEXT_LCD_NUM_COL
#define _USER_TEXT_LCD_NUM_COL	16
#endif

#ifdef _USER_TEXT_LCD_NUM_ROW
#undef _USER_TEXT_LCD_NUM_ROW
#define _USER_TEXT_LCD_NUM_ROW	2
#endif

#define _STRING_BUFFER_SIZE	_USER_TEXT_LCD_NUM_COL+1

typedef enum
{
  _TEST_NULL,
  _TEST_ERROR,
  _TEST_SUCCESS
}TestResultStt;

typedef enum{
 _LED1,
 _LED2,
 _LED_OK,
 _LED_ERROR,
 _RL_PAD,
 _BUZ,
 //..
 _MAX_OUTPUT
}CtrlName_t;

typedef enum {
  _DISPLAY_MAIN=0,
  _DISPLAY_PHANLOAISENSOR,
  _DISPLAY_PHOTOCELL,
  _DISPLAY_POWER,
  //...
  _DISPLAYMAX
}LcdDisplay_e;

typedef enum{
  _test_null,
  _test_start,
  _test_ledRedBlink,
  _test_ledCalib,
  _test_ledGreenOn,
  _test_ledGreenOff,
  _test_finished,
  _test_countSensor
}testSenState_t;

typedef enum{
  _PhotoCell_noInit,	//chưa khởi động , chưa học môi trường
  _PhotoCell_LedGreenOn,//sáng nhất
  _PhotoCell_uncovered, //sáng bình thường của môi trường
  _PhotoCell_covered,	//Sensor che lại
  _PhotoCell_other	//khác
}PhotoCell_Status;

typedef enum{
  _AS_QuaSang_ERROR, //<750
  _AS_QuaSang_OK, //750-1300
  _AS_HoiSang_OK, //1300-2000
  _AS_SangBt_OK,  //2000-2800
  _AS_HoiToi_OK,  //2800-3000
  _AS_ToiBt_OK,	  //3000-3400
  _AS_QuaToi_ERROR  //>3400
}AnhSangStt_t;

typedef enum{
  _ID_ADC_probes,					/*!< chanel 0 in DMA array result                          */
  _ID_ADC_ptcHsink,					/*!< chanel 1 in DMA array result                          */
  _ID_ADC_ptcBoiler,					/*!< chanel 2 in DMA array result                          */
  _ID_ADC_hallCurrent,					/*!< chanel 3 in DMA array result                          */

  _ID_ADC_TOTAL
}DMA_ADCposition_t;

typedef union{
    struct {
	    uint8_t 	f_phanLoaiSensor;
	    uint8_t	byte1;
	    uint8_t	byte2;
	    uint8_t 	byte3;
	    uint8_t	byte4;
	    uint8_t	byte5;
	    uint8_t	byte6;
	    uint8_t	byte7;
    }Byte_t;

    struct {
	    uint32_t Word0;
	    uint32_t Word1;
    }Word_t;

    uint64_t Dword;
}Epprom64_u;

typedef struct{
  uint8_t _ledRed,
	  _lineSignal,
	  _ledGreen,
	  _lineLogic;
}ErrorManager;

typedef struct{
  testSenState_t state;
  LcdDisplay_e Lcd_id;
  char LcdStr_row[_USER_TEXT_LCD_NUM_ROW][_STRING_BUFFER_SIZE];
  float current,
	voltage,
	power;
  uint16_t adcLightStart;
  AnhSangStt_t dkAnhSang;
  PhotoCell_Status lightStt;

  ErrorManager error;
  uint16_t PassNum,FailNum;
  TestResultStt	resultTesting;

}TestSSWater_t;

extern volatile uint16_t ADC_Arr[_ID_ADC_TOTAL];
extern Epprom64_u flashDataInfor;

void testWaterSensorInit();
void testWaterSensorLoop();
void testWaterSensor_1msIrqHandle();

PhotoCell_Status getPhotocellStatus(uint16_t adcLight,uint16_t adcLightInit);

#endif /* SRC_TEST_SENSOR_TESTWATERSENSOR_H_ */
