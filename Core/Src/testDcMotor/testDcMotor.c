#ifndef SRC_TESTDCMOTOR_TESTDCMOTOR_C_
#define SRC_TESTDCMOTOR_TESTDCMOTOR_C_

#include "myHeader.h"

MotorTestWater_t TWMOTOR;

void Drv8251_Control(Drv8251DirCtrl_e control)
{
  switch(control)
  {
    case _DIR_COAST:
      MOTOR_IN1_OFF;
      MOTOR_IN2_OFF;
      LED1_OFF;
      LED2_OFF;
      break;
    case _DIR_LEFT:
   // case _DIR_RIGHT:
      MOTOR_IN1_OFF;
      MOTOR_IN2_ON;
      LED1_OFF;
      LED2_ON;
      break;
    case _DIR_RIGHT:
    //case _DIR_LEFT:
      MOTOR_IN1_ON;
      MOTOR_IN2_OFF;
      LED1_ON;
      LED2_OFF;
      break;
    case _DIR_BRAKE:
      MOTOR_IN1_ON;
      MOTOR_IN2_ON;
      LED1_ON;
      LED2_ON;
      break;
    default:break;
  }
}

void testMotorWaterInit(){
  TWMOTOR.motorState = _DIR_LEFT;
  Drv8251_Control(TWMOTOR.motorState);
  timer_set(&TWMOTOR._timeRunMotor, 200);
};

uint8_t skipSwt=0;
void testMotorWaterLoop(){

  if(timer_expired(&TWMOTOR._timeRunMotor)){
      timer_stop(&TWMOTOR._timeRunMotor);
      Drv8251_Control(TWMOTOR.motorState);
  }
  if(TWMOTOR.SWTS.Bit.LEFT_SWT && TWMOTOR.SWTS.Bit.MID_SWT && TWMOTOR.SWTS.Bit.RIGHT_SWT)skipSwt=0;

  if(skipSwt==1)
    return;

  if(TWMOTOR.SWTS.Bit.LEFT_SWT==0 && TWMOTOR.SWTS.Bit.MID_SWT && TWMOTOR.SWTS.Bit.RIGHT_SWT){
      delay_ms(50);
      timer_set(&TWMOTOR._timeRunMotor, 1000);
      skipSwt=1;
      TWMOTOR.motorState = _DIR_RIGHT;
      Drv8251_Control(_DIR_BRAKE);
  }
  else if(TWMOTOR.SWTS.Bit.LEFT_SWT &&  TWMOTOR.SWTS.Bit.MID_SWT==0 && TWMOTOR.SWTS.Bit.RIGHT_SWT){
      delay_ms(50);
      skipSwt=1;
      timer_set(&TWMOTOR._timeRunMotor, 1000);
      Drv8251_Control(_DIR_BRAKE);
  }
  else if(TWMOTOR.SWTS.Bit.LEFT_SWT &&  TWMOTOR.SWTS.Bit.MID_SWT && TWMOTOR.SWTS.Bit.RIGHT_SWT==0){
      delay_ms(50);
      skipSwt=1;
      timer_set(&TWMOTOR._timeRunMotor, 1000);
      TWMOTOR.motorState = _DIR_LEFT;
      Drv8251_Control(_DIR_BRAKE);
  }
}

void testMotorSystickIrq1ms(MotorTestWater_t *mtor){
  mtor->SWTS.Bit.RIGHT_SWT= Systick_ReadInput_poll(_IN_SW_RIGHT,SWTRIGHT_PinStt,10,10);
  mtor->SWTS.Bit.MID_SWT  = Systick_ReadInput_poll(_IN_SW_MID,SWTMID_PinStt,10,10);
  mtor->SWTS.Bit.LEFT_SWT = Systick_ReadInput_poll(_IN_SW_LEFT,SWTLEFT_PinStt,10,10);

  mtor->SWTS.Bit.RIGHT_IR = IRRIGHT_PinStt;//Systick_ReadInput_poll(_IN_IR_LEFT,IRRIGHT_PinStt,2,2);
  mtor->SWTS.Bit.LEFT_IR = IRLEFT_PinStt;//Systick_ReadInput_poll(_IN_IR_RIGHT,IRLEFT_PinStt,2,2);

  //update Posistion
  if(mtor->SWTS.Bit.LEFT_SWT==0 && mtor->SWTS.Bit.MID_SWT && mtor->SWTS.Bit.RIGHT_SWT) mtor->atPosition = _POS_LEFT;
  else if(mtor->SWTS.Bit.LEFT_SWT && mtor->SWTS.Bit.MID_SWT==0 && mtor->SWTS.Bit.RIGHT_SWT) mtor->atPosition = _POS_MID;
  else if(mtor->SWTS.Bit.LEFT_SWT && mtor->SWTS.Bit.MID_SWT && mtor->SWTS.Bit.RIGHT_SWT==0) mtor->atPosition = _POS_RIGHT;
  else if(mtor->SWTS.Bit.LEFT_SWT && mtor->SWTS.Bit.MID_SWT && mtor->SWTS.Bit.RIGHT_SWT) mtor->atPosition = _POS_UNKNOWN;
  else mtor->atPosition = _POS_SWT_ERROR;
}

void MotorTestWaterSensorInit(MotorTestWater_t *mtor){
  mtor->motorState = _DIR_COAST;
  Drv8251_Control(mtor->motorState);
  timer_set(&mtor->_timeRunMotor, 200);
}

void MotorTestWaterSensorLoop(MotorTestWater_t *mtor){

  //Nếu hoạt động quá thời gian được set thì thả nổi lại
  if(timer_expired(&mtor->_timeRunMotor)){
      if(mtor->goPosition==_POS_MID && mtor->motorState == _DIR_LEFT){
	  mtor->motorState=_DIR_RIGHT;
	  Drv8251_Control(mtor->motorState);
	  timer_set(&mtor->_timeRunMotor, 3*_TIMEOUT_CHECK_MID);//thời gian tối quay ngược trở lại để tìm vị trí MID , gấp 3 lần giá trị cũ
      }
      else {
	  MotorGotoPosition(mtor,_POS_UNKNOWN,0);
	  timer_stop(&mtor->_timeRunMotor);
      }
  }

  //Nếu trước đó ko điều khiển
  if(mtor->goPosition==_POS_UNKNOWN)return;
  //Nếu trước đó có điều khiển thì đúng vị trí sẽ dừng lại
  if(mtor->atPosition == mtor->goPosition){
    mtor->goPosition = _POS_UNKNOWN;
    mtor->motorState = _DIR_BRAKE;
    timer_stop(&mtor->_timeRunMotor);
    Drv8251_Control(mtor->motorState);
  }
}

void MotorGotoPosition(MotorTestWater_t *mtor,PositionMotor_t gotoPositon,uint32_t timeOut){

  //Nếu các CTHT bị lỗi
  if(mtor->atPosition==_POS_SWT_ERROR) return;
  //Vị trí hiện tại và vị trí muốn đến trùng nhau
  if(mtor->atPosition == gotoPositon || mtor->atPosition==_POS_SWT_ERROR) return;

  //Set thời gian hoạt động tối đa
  if(timeOut)timer_set(&mtor->_timeRunMotor, timeOut);
  mtor->goPosition = gotoPositon;
  //các Trường hợp điều khiển
  switch(mtor->goPosition){
    //Muốn qua trái
    case _POS_LEFT:
      mtor->motorState = _DIR_LEFT;
      break;

    //Muốn qua phải
    case _POS_RIGHT:
      mtor->motorState = _DIR_RIGHT;
      break;

    //Muốn về ở giữa
    case _POS_MID:
      if(mtor->atPosition==_POS_LEFT){
	mtor->motorState = _DIR_RIGHT;
      }
      else if(mtor->atPosition==_POS_RIGHT){
	mtor->motorState = _DIR_LEFT;
      }
      else if(mtor->atPosition==_POS_UNKNOWN)
      {
	//nếu ko xác định được vị trí thì chạy qua trái trước
	mtor->motorState = _DIR_LEFT;
	timer_set(&mtor->_timeRunMotor, _TIMEOUT_CHECK_MID);//set thời gian tối thiều là 2s
      }
      break;

    //ko xảy ra các trường hợp khác , ko biết thì thả nổi mtor
    default:
      mtor->goPosition = _POS_UNKNOWN;
      mtor->motorState = _DIR_COAST;
      timer_stop(&mtor->_timeRunMotor);
      return;
  }
  Drv8251_Control(mtor->motorState);
}

#endif /* SRC_TESTDCMOTOR_TESTDCMOTOR_C_ */
