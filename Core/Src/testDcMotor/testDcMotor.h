#ifndef SRC_TESTDCMOTOR_TESTDCMOTOR_H_
#define SRC_TESTDCMOTOR_TESTDCMOTOR_H_

#define _TIMEOUT_MOTOR		3000
#define _TIMEOUT_CHECK_MID	2000

typedef enum{
  _DIR_COAST,//0
  _DIR_RIGHT,//1 => Lái qua  Phai
  _DIR_LEFT,//2 => Lái qua  Trai
  _DIR_BRAKE,//3
  //...
  _DIR_MAX //4
}Drv8251DirCtrl_e;

typedef enum{
  _IN_SW_LEFT,
  _IN_SW_MID,
  _IN_SW_RIGHT,
  _IN_IR_LEFT,
  _IN_IR_RIGHT,
  //...
  _IN_MAX
}InputArr_e;

typedef enum{
  _POS_UNKNOWN,
  _POS_LEFT,
  _POS_MID,
  _POS_RIGHT,
  _POS_SWT_ERROR
}PositionMotor_t;

typedef union{
  struct{
    uint8_t RIGHT_SWT:1;//lsb
    uint8_t MID_SWT:1;
    uint8_t LEFT_SWT:1;
    uint8_t RIGHT_IR:1;
    uint8_t LEFT_IR:1;
  }Bit;
  uint8_t ByteSwt;
}ManageSwtStt;

typedef struct{
  ManageSwtStt		SWTS; 			//quản lí tất cả Input đầu vào
  Drv8251DirCtrl_e	motorState;		//trạng thái hoạt động của motor
  PositionMotor_t	atPosition,		//Vị trí motor đang đứng
			goPosition;		//Vị trí đang muốn đến
  timer_virtual_t 	_timeRunMotor;
}MotorTestWater_t;

extern MotorTestWater_t TWMOTOR;

void Drv8251_Control(Drv8251DirCtrl_e control);

void testMotorWaterInit();
void testMotorWaterLoop();

void MotorGotoPosition(MotorTestWater_t *mtor,PositionMotor_t gotoPositon,uint32_t timeOut_ms);
void MotorTestWaterSensorInit(MotorTestWater_t *mtor);
void MotorTestWaterSensorLoop(MotorTestWater_t *mtor);

void testMotorSystickIrq1ms(MotorTestWater_t *mtor);


#endif /* SRC_TESTDCMOTOR_TESTDCMOTOR_H_ */
