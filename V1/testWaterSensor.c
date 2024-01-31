#include "myHeader.h"

#define D0_BOTEST_QUASANG_LOI		"Loi QuaSang"
#define D0_BOTEST_QUASANG_OK		"Qua Sang Ok"
#define D0_BOTEST_HOISANG_OK		"Hoi Sang Ok"
#define D0_BOTEST_SANGBT_OK		"Sang bt Ok "
#define D0_BOTEST_HOITOI_OK		"Hoi Toi Ok "
#define D0_BOTEST_TOIBT_OK		"Toi Bt     "
#define D0_BOTEST_QUATOI_LOI		"Loi Qua Toi"

//#define D0_SUTAP_LOI			"E1-Sut ap < 4V"
//#define D0_GHIM_CONNECTOR		" Ghim Connector"
//#define D0_QUADONG_LOI			"E2-Qua Dong>70mA"
//#define D0_CHECK_LED_RED		"  Check Led Do"
//#define D0_GHIM_PADDONG			" Ghim Pad dong"
//#define D0_LEDGREEN_LUONSANG_LOI	"E4-Loi LedXanh_1"
//#define D0_LED_RED_LOI			"E3-Loi Led Do"
//#define D0_LED_LOI_QUADONG		"E2-Qua Dong>25mA"
//#define D0_LED_RED_SANG_OK		"  1-Led Do Ok"
//#define D0_LED_RED_TAT_OK		"  0-Led Do Ok"
//#define D0_LED_RED_X_OK			"  X-Led Do Ok"
//#define D0_CALIB_OK			"    Calib Ok"
//#define D0_CALIB_LOI			"E8-Calib Fail"
//#define D0_LEDGREEN_SANG		"Sensor xanh On"
//#define D0_DAYLOGIC_LUON0_LOI		"E7-LoiDayTrang_0"
//#define D0_DAYLOGIC_LUON1_LOI		"E6-LoiDayTrang_1"
//#define D0_LEDGREEN_LUON0_LOI		"E5-Loi LedXanh_0"
//#define D0_LEDGREEN_LUON1_LOI		"E4-Loi LedXanh_1"
//#define D0_SENSOR_OK			"   Sensor OK"

#define D0_SUTAP_LOI			"E3 - Sut ap < 4V"
#define D0_GHIM_CONNECTOR		" Ghim Connector "
#define D0_QUADONG_LOI			"E4-Qua Dong>70mA"
#define D0_CHECK_LED_RED		"  Check Led Do  "
#define D0_GHIM_PADDONG			" Ghim Pad dong  "
#define D0_LEDGREEN_LUONSANG_LOI	"E6-Loi Led Xanh1"
#define D0_LED_RED_LOI			"E5-Loi Led Do   "
#define D0_LED_LOI_QUADONG		"E4-Qua Dong>25mA"
#define D0_LED_RED_SANG_OK		"  1-Led Do Ok"
#define D0_LED_RED_TAT_OK		"  0-Led Do Ok"
#define D0_LED_RED_X_OK			"  X-Led Do Ok"
#define D0_CALIB_OK			"    Calib Ok"
#define D0_CALIB_LOI			"E8-Calib ThatBai"
#define D0_LEDGREEN_SANG		"Sensor xanh On"
#define D0_DAYLOGIC_LUON0_LOI		"E7-Loi Logic_0"
#define D0_DAYLOGIC_LUON1_LOI		"E7-Loi Logic_1"
#define D0_LEDGREEN_LUON0_LOI		"E6-Loi LedXanh_0"
#define D0_LEDGREEN_LUON1_LOI		"E6-Loi LedXanh_1"
#define D0_SENSOR_OK			"   Sensor OK"

//càng sáng càng giam
#define PHOTOCELL_IS_NOSEN(x)		(x>=1000 && x<=2000)?1:0
#define PHOTOCELL_IS_HAVESEN(x)		(x>=2200)?1:0			//Tối
#define PHOTOCELL_IS_HAVESEN_GREENON(x)	(x>=200 && x<=500)?1:0

OUTPUT_t _ctrlOutput[_MAX_OUTPUT];
button_t _btnConfig;

volatile uint16_t ADC_Arr[_ID_ADC_TOTAL];
static Kalman_t Kalman_ADC[_ID_ADC_TOTAL];
TestSSWater_t TOOL;
timer_virtual_t _timeoutCheckState,
		_timeoutCheckLedRed,
		_timeoutCheckCalib,
		_timeoutCheckLedGreenOff,
		_timer_updateIna219,
		_timer_updateLCD;
uint8_t	f_readKalmanAdc;
char stringBuffer[13];
uint8_t f_checkLedXanh=0;

/*Function Declare*/
void updateLcd();
void updateIna219();
void updateKalmanADC();
void callback_calibGetResult(CheckStatus True_false);
void gotoFinished(ProcessStatus success_error);
void callback_btnConfigHandle(uint16_t ID, bt_eventFunc_t eventFunc, bt_typeArg_t agr);

PhotoCell_Status getBright(){
  uint16_t SaiSo_sang,SaiSo_toi;

  if(TOOL.adcLightStart < 400){
      TOOL.dkAnhSang=_AS_QuaSang_ERROR;
      sprintf(stringBuffer,D0_BOTEST_QUASANG_LOI);
      return _PhotoCell_other;
  }
  else if(_LIMIT(TOOL.adcLightStart,401,1300)){
      TOOL.dkAnhSang=_AS_QuaSang_OK;
      sprintf(stringBuffer,D0_BOTEST_QUASANG_OK);
      SaiSo_sang=400;
      SaiSo_toi=1500;
  }
  else if(_LIMIT(TOOL.adcLightStart,1301,2000)){
      TOOL.dkAnhSang=_AS_HoiSang_OK;
      sprintf(stringBuffer,D0_BOTEST_HOISANG_OK);
      SaiSo_sang=210;
      SaiSo_toi=1300;
  }
  else if(_LIMIT(TOOL.adcLightStart,2001,2800)){
      TOOL.dkAnhSang=_AS_SangBt_OK;
      sprintf(stringBuffer,D0_BOTEST_SANGBT_OK);
      SaiSo_sang=300;
      SaiSo_toi=700;
  }
  else if(_LIMIT(TOOL.adcLightStart,2801,3000)){
      TOOL.dkAnhSang=_AS_HoiToi_OK;
      sprintf(stringBuffer,D0_BOTEST_HOITOI_OK);
      SaiSo_sang=400;
      SaiSo_toi=600;
  }
  else if(_LIMIT(TOOL.adcLightStart,3001,3500)){
      TOOL.dkAnhSang=_AS_ToiBt_OK;
      sprintf(stringBuffer,D0_BOTEST_TOIBT_OK);
      SaiSo_sang=500;
      SaiSo_toi=200;
  }
  else if(TOOL.adcLightStart > 3500){
      TOOL.dkAnhSang=_AS_QuaToi_ERROR;
      sprintf(stringBuffer,D0_BOTEST_QUATOI_LOI);
      return _PhotoCell_other;
  }

  if(ADC_Arr[_ID_ADC_ptcHsink]==0)
    return _PhotoCell_noInit;
  else if(_LIMIT(ADC_Arr[_ID_ADC_ptcHsink],100,780))
      return _PhotoCell_LedGreenOn;
  else if(_LIMIT(ADC_Arr[_ID_ADC_ptcHsink],781,3800-SaiSo_toi))
    return _PhotoCell_uncovered;
  else if(_LIMIT(ADC_Arr[_ID_ADC_ptcHsink],3800-SaiSo_toi,4000))
    return _PhotoCell_covered;
  else
    return _PhotoCell_other;
}

/*Functions*/
void updateLcd(){
  static char str_cmp0[_STRING_BUFFER_SIZE],
	      str_cmp1[_STRING_BUFFER_SIZE];
  uint8_t result1, result2;

  if(!timer_expired(&_timer_updateLCD))
    return;
  timer_set(&_timer_updateLCD, 250);

  //Hien hien LCD theo mode
  if(TOOL.Lcd_id==_DISPLAY_MAIN)
  {
      sprintf(TOOL.LcdStr_row[1],"                ");
  }
  else if(TOOL.Lcd_id==_DISPLAY_PHOTOCELL)
  {
      sprintf(TOOL.LcdStr_row[1],"%s=%4u",stringBuffer,ADC_Arr[_ID_ADC_ptcHsink]);
  }
  else if(TOOL.Lcd_id==_DISPLAY_POWER)
  {
      sprintf(TOOL.LcdStr_row[1],"%4.01fV %5.01fmA",TOOL.voltage, TOOL.current);
  }


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

void updateIna219(){
  if(!timer_expired(&_timer_updateIna219))
    return;
  timer_restart(&_timer_updateIna219);

  TOOL.current = getCurrent_mA();
  TOOL.voltage = getvoltage_V();
  TOOL.power = getPower_mW();
}

void updateKalmanADC(){
//  if(f_readKalmanAdc){
//    //Read adc
//    for(uint8_t i=0; i<_ID_ADC_TOTAL; i++){
//	ADC_Arr[i] = (uint16_t) (km_process(&Kalman_ADC[i], (float) ADC_Arr[i]));
//    }
//    f_readKalmanAdc=0;
//  }
}

void callback_calibGetResult(CheckStatus True_false){
  if(True_false==0){
      OUTPUT_setBlink(&_ctrlOutput[_LED1],10,200,400,0);
  }
  else
  {
      OUTPUT_setBlink(&_ctrlOutput[_LED1],10,3000,3500,0);
  }
}

void gotoFinished(ProcessStatus success_error){
  if(success_error==_ERROR){
      OUTPUT_setBlink(&_ctrlOutput[_BUZ],1,100,200,1);
      TOOL.state=_test_finished;
  }else{
      OUTPUT_setBlink(&_ctrlOutput[_BUZ],1,1000,1200,0);
      TOOL.state=_test_finished;
  }
}

uint8_t f_changeDisplay;
void callback_btnConfigHandle(uint16_t ID, bt_eventFunc_t eventFunc, bt_typeArg_t agr){
  //if(ID!=1)return;
  switch(eventFunc){
    case _BUTTON_FUNC_EVENT:
      if(agr.event == BUTTON_ONECLICK){
	  NVIC_SystemReset();
      }
      break;

    case _BUTTON_FUNC_MULCLICK:

      break;

    case _BUTTON_FUNC_HOLD:

      if(agr.holdInterval_ms%1000==0){
	  OUTPUT_setBlink(&_ctrlOutput[_BUZ], 1, 100, 200,0);
      }

      if(agr.holdInterval_ms == 5000){
	  if(++TOOL.Lcd_id >=_DISPLAYMAX)
	    TOOL.Lcd_id=0;
      }

//      if(agr.holdInterval_ms >= 5000 && agr.holdInterval_ms < 5500){
//	  if(f_changeDisplay)
//	    return;
//	  if(++TOOL.Lcd_id >=_DISPLAYMAX)TOOL.Lcd_id=0;
//	  f_changeDisplay=1;
//      }
//      else
//	f_changeDisplay=0;

      break;

    default:break;
  }
}

void testWaterSensorInit(){

  /*Init DMA ADC */
  //Init DMA_ADC of MCU
  if(HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)
	  Error_Handler();

  if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_Arr, _ID_ADC_TOTAL) != HAL_OK)
	  Error_Handler();

  //Init Kalman Adc filter
  for(uint8_t i=0;i<_ID_ADC_TOTAL; i++){
      km_init(&Kalman_ADC[i], 0.01, 20, 4050);
  }
  //setCalibration_32V_1A();
  setCalibration_16V_400mA();
  /*Init i2c2 for LCD and Ina219 */
  HAL_I2C_Init(&_USER_DEFINE_I2C_LCD);
  CLCD_I2C_Init(&LCD1, &_USER_DEFINE_I2C_LCD, 0x4e, 20, 4);

  /*Init Timer7*/
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Base_Start_IT(&_UV_CAPSS_TIMER);

  CAPSENSOR[_CAPSS_ID_WATER]._cb_calibResult = &callback_calibGetResult;
  _btnConfig.cb_function = &callback_btnConfigHandle;

  /*Init Outputs Control*/
//  OUTPUT_configInit(&_ctrlOutput[_LED1], LED1_BaseCtrl, 0);
//  OUTPUT_configInit(&_ctrlOutput[_LED2], LED2_BaseCtrl, 0);
  OUTPUT_configInit(&_ctrlOutput[_RL_PAD], RLSOL_BaseCtrl, 0);
  //OUTPUT_configInit(&_ctrlOutput[_BUZ], BUZ_BaseCtrl, 0);

  OUTPUT_setBlink(&_ctrlOutput[_BUZ],1,200,400,0);

  //clear all error
  memset(&TOOL.error,1,sizeof(TOOL.error));
  timer_set(&_timer_updateIna219, 50);
  timer_set(&_timer_updateLCD, 2000);
  timer_set(&_timeoutCheckState, 20);
  ShowLCD_String("    BO TEST", 0, 0);
  ShowLCD_String("  WATER SENSOR", 0, 1);
  TOOL.state = _test_null;
  TOOL.adcLightStart=0;
  TOOL.Lcd_id=_DISPLAY_MAIN;
}

void testWaterSensor_1msIrqHandle(){
  static uint8_t tx10;

  /*1ms check poll*/
  if(f_readKalmanAdc==0)
    f_readKalmanAdc=1;

  CapSS_periodic_poll(&CAPSENSOR[0]);

  //Outputs
  for(uint8_t i=0; i<_MAX_OUTPUT; i++)
      OUTPUT_blinkHandle(&_ctrlOutput[i]);

  /*10ms check poll*/
  if(++tx10 >= 10){
     tx10 = 0;
     timer_periodic_poll();
     btn_progress_loop(&_btnConfig,BUTTON_PinStt);
  }
}

//void testWaterSensor_systickIrqHandle(){
//
//}

uint8_t ledRedTog=0;
float curLedRedOff,curLedRedOn;
void testWaterSensorTask();
void testWaterSensorTask(){

  if(!timer_expired(&_timeoutCheckState))
	return;
  if(TOOL.state!=_test_ledRedBlink)
    timer_restart(&_timeoutCheckState);

  //lay trang thai Anh sang
  TOOL.lightStt = getBright();

  //Hoc gia tri moi truong
  if(TOOL.adcLightStart==0){
    TOOL.adcLightStart = ADC_Arr[1];
    timer_set(&_timeoutCheckState, 20);
    return;
  }

  switch(TOOL.state){
    case _test_null:
      //Kiem tra dien ap
      if(TOOL.voltage < 4)
      {
        sprintf(TOOL.LcdStr_row[0],D0_SUTAP_LOI);
        TOOL.state=_test_null;
        return;
      }

      TOOL.current = getCurrent_mA();
      //Kiem tra dong dien
      if(TOOL.current <= 0.4){
	  sprintf(TOOL.LcdStr_row[0],D0_GHIM_CONNECTOR);
      }else if(TOOL.current > 0.4 && TOOL.current < 50){
	  TOOL.state=_test_start;
	  f_checkLedXanh=0;
	  delay_ms(500);
      }else{
	sprintf(TOOL.LcdStr_row[0],D0_QUADONG_LOI);
      }

      break;
    case _test_start:
      if(TOOL.lightStt == _PhotoCell_covered){
	  sprintf(TOOL.LcdStr_row[0],"  Check Led Do");
	  timer_set(&_timeoutCheckLedRed, 3000);
	  TOOL.state=_test_ledRedBlink;
	  return;
      }
      else if(TOOL.lightStt == _PhotoCell_LedGreenOn){
	  f_checkLedXanh=1;
//	  if(CAPSENSOR[0].logicStt==_HIGH){
//	    sprintf(TOOL.LcdStr_row[0],"Loi day trang=1");
//	    gotoFinished(_ERROR);
//	    return;
//	  }
	  sprintf(TOOL.LcdStr_row[0],D0_CHECK_LED_RED);
	  timer_set(&_timeoutCheckLedRed, 2500);
	  TOOL.state=_test_ledRedBlink;
	  return;
      }
      else
      {
	  sprintf(TOOL.LcdStr_row[0],D0_GHIM_PADDONG);
      }
      timer_stop(&_timeoutCheckLedRed);
      ledRedTog=0;
      break;

    case _test_ledRedBlink:

      if(timer_expired(&_timeoutCheckLedRed)){

	if(TOOL.lightStt == _PhotoCell_LedGreenOn || f_checkLedXanh==1)
	  sprintf(TOOL.LcdStr_row[0],D0_LEDGREEN_LUONSANG_LOI);
	else if(TOOL.current > 30/*mA*/){
	    sprintf(TOOL.LcdStr_row[0],D0_LED_LOI_QUADONG);
	}
	else
	  sprintf(TOOL.LcdStr_row[0],D0_LED_RED_LOI);

	gotoFinished(_ERROR);
	return;
      }

      //Không kiểm tra Led đỏ khi Led xanh sáng
      if(TOOL.lightStt == _PhotoCell_LedGreenOn)
	return;
      else f_checkLedXanh=0;

      TOOL.current = getCurrent_mA();

      if((ledRedTog%2==0) && _LIMIT(TOOL.current,0.8,6))
	{
	  ledRedTog++;
	  curLedRedOff = TOOL.current;
	}
      else if((ledRedTog%2==1) && _LIMIT(TOOL.current,10,20))
	{
	  ledRedTog++;
	  curLedRedOn =  TOOL.current;
	}

      //OK
      if(ledRedTog>2){
	  if(_LIMIT(curLedRedOff,0.8,1.5))//&&_LIMIT(curLedRedOn,9,15.5))
	    sprintf(TOOL.LcdStr_row[0],D0_LED_RED_SANG_OK);
	  else if(_LIMIT(curLedRedOff,4,6))//&&_LIMIT(curLedRedOn,15.6,19))
	    sprintf(TOOL.LcdStr_row[0],D0_LED_RED_TAT_OK);
	  else {
	    sprintf(TOOL.LcdStr_row[0],D0_LED_RED_X_OK);
	  }

	  CapSS_Start(&CAPSENSOR[_CAPSS_ID_WATER], _SS_CALIB_BYTE);
	  timer_set(&_timeoutCheckCalib, 1000);
	  timer_restart(&_timeoutCheckState);
	  TOOL.state=_test_ledCalib;
	  return;
      }
      break;

    case _test_ledCalib:
      if(timer_expired(&_timeoutCheckCalib)){
	  timer_stop(&_timeoutCheckCalib);
	  if(CAPSENSOR[_CAPSS_ID_WATER].connectStt==_PASS){
	      sprintf(TOOL.LcdStr_row[0],D0_CALIB_OK);
	      TOOL.state=_test_ledGreenOn;
	  }else if(CAPSENSOR[_CAPSS_ID_WATER].connectStt==_FAIL) {
	      sprintf(TOOL.LcdStr_row[0],D0_CALIB_LOI);
	      gotoFinished(_ERROR);
	  }
      }
      break;

    case _test_ledGreenOn:
      if(TOOL.lightStt == _PhotoCell_LedGreenOn){
	if(CAPSENSOR[0].logicStt == _LOW)
	{
	  sprintf(TOOL.LcdStr_row[0],D0_LEDGREEN_SANG);
	  TOOL.state=_test_ledGreenOff;
	  timer_set(&_timeoutCheckLedGreenOff,3300);
	  return;
	}else
	  sprintf(TOOL.LcdStr_row[0],D0_DAYLOGIC_LUON1_LOI);
      }else
	sprintf(TOOL.LcdStr_row[0],D0_LEDGREEN_LUON0_LOI);

      gotoFinished(_ERROR);
      break;

    case _test_ledGreenOff:
      if(TOOL.lightStt == _PhotoCell_covered){
	if(CAPSENSOR[0].logicStt){
	  sprintf(TOOL.LcdStr_row[0],D0_SENSOR_OK);
	  gotoFinished(_SUCCESS);
	  return;
	}else{
	  sprintf(TOOL.LcdStr_row[0],D0_DAYLOGIC_LUON0_LOI);
	  timer_stop(&_timeoutCheckLedGreenOff);
	  gotoFinished(_ERROR);
	  return;
	}
      }

      if(timer_expired(&_timeoutCheckLedGreenOff)){
	sprintf(TOOL.LcdStr_row[0],D0_LEDGREEN_LUON1_LOI);
	timer_stop(&_timeoutCheckLedGreenOff);
	gotoFinished(_ERROR);
	return;
      }

    case _test_finished:
      TOOL.current = getCurrent_mA();
      if(TOOL.current <= 0.4){
	  TOOL.state=_test_null;
	  OUTPUT_setOff(&_ctrlOutput[_BUZ],0);
	  timer_stop(&_timeoutCheckLedRed);
	  timer_stop(&_timeoutCheckCalib);
	  timer_stop(&_timeoutCheckLedGreenOff);
	  ledRedTog=0;
      }
      break;
  }
}

void testWaterSensorLoop(){
  updateLcd();
  updateIna219();
  updateKalmanADC();
  CapSS_Task(&CAPSENSOR[0]);

  testWaterSensorTask();
}


/*
 KET QUA DO SENSOR THUC TE

MCU = 1.2 mA
Led do ON + MCU = 12.2 mA
=> Led do ON = 10.8 đến 11mA

Mất led đỏ :
 MCU + Led xanh sáng = 7.8mA
=> Led xanh = 6.6 mA

Cả led đỏ +  Led xanh cùng sáng : 10.8 + 6.6 = 17.4

Khi Led nhấp nháy :

led do | Led xanh
00 : 1.2 => caib rồi | 00 : 5.1  => chua caib : 6
01 : 7.8       : photocell sang
10 : 10.8 =>caib rồi | 10 : 15.1 => chua caib : 16
11 : 17.4	: photocell sang

Độ sai số : +-1mA*/
