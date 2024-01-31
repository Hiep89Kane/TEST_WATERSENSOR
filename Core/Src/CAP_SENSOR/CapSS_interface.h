#ifndef INC_CAPSS_INTERFACE_H_
#define INC_CAPSS_INTERFACE_H_

#define RETRY_NUM_CHECKSTT 6 // 6*250ms= 1,5s
#define RETRY_NUM_CALIB 3    // 2*500ms= 1s

typedef enum
{
	_CAPSS_ID_WATER, // 0
	//_CAPSS_ID_DRAIN, // 1
	//..
	_CAPSS_ID_TOTAL // 2
} Sensor_index;

typedef enum
{
	_SENSOR_CLEAR,		// chua dieu khien
	_SENSOR_SENT_START, 	// bat dau tx
	_SENSOR_SENT_DONE,	// wait tx xong -> input
	_SENSOR_BUSY,		// read rx pulses
	_SENSOR_FAIL,		// retry n....0 -> return FAIL
	_SENSOR_SUCESS		// return SUCESS
} Sensor_State_t;

#define Max_Index 5

#define Stx_Index 0
#define Add_Index 1
#define Cmd_Index 2
#define Data_Index 3
#define Etx_Index 4

#define _SS_CALIB_BYTE 0x60 // byte 2
#define _SS_CHECKSTT_BYTE 0x6F

#define _CAL_PULSE_NUM 10
#define _CHECKSTT_PULSE_NUM 5

typedef struct
{
	Sensor_State_t state;
	__IO uint8_t pulseCnt;
	__IO CheckStatus connectStt;
	__IO LogicStatus logicStt;
	uint8_t command;
	uint8_t retry_connect;
	void (*_cb_calibResult)(CheckStatus True_false);
} CapSen_Struct_t;

/* Global variables ---------------------------------------------------------*/
extern CapSen_Struct_t CAPSENSOR[_CAPSS_ID_TOTAL];
/*********************************************************************/
void CapSS_TxSignal_SetOut(uint8_t CapSS_selected);
void CapSS_TxSignal_SetIn(uint8_t CapSS_selected);

void CapSS_Start(CapSen_Struct_t *Sensor_Tmp, uint8_t cmd);
void CapSS_Task(CapSen_Struct_t *Sensor_Tmp);
void CapSS_CheckPulse_Systick(uint8_t Pin_stt, CapSen_Struct_t *Sensor_Tmp);
void CapSS_Get_Result(CapSen_Struct_t *Sensor_Tmp2);

// In Timer
void CapSS_periodic_poll(CapSen_Struct_t *Sensor_Tmp);

#endif /* INC_CAPSS_INTERFACE_H_ */
